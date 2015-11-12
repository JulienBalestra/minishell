import unittest
import os
from tools import *


class TestMinishell(unittest.TestCase):
	context = os.path.split(os.path.dirname(__file__))[0]
	minishell = "%s/minishell" % context
	testing_dir = "%s/tests/test_resources/" % context
	minishell_prompt = "minishell> "
	valgrind_binary = False
	dev_null = open(os.devnull, 'w')
	queue = QueueProcess

	@classmethod
	def setUpClass(cls):
		os.chdir(cls.testing_dir)
		if subprocess.call(["make", "re", "-C", cls.context, "-j"], stdout=cls.dev_null) == 0:
			pass
		elif subprocess.call(["make", "-C", cls.context], stdout=cls.dev_null) == 0:
			os.write(2, "FAILED TO MAKE WITH -j")
		else:
			raise RuntimeError("compilation failed in %s" % cls.context)

		try:
			if subprocess.call(["valgrind", "--version"]) == 0:
				cls.valgrind_binary = True
		except OSError:
			pass

	@classmethod
	def tearDownClass(cls):
		cls.dev_null.close()

	def execute_my_shell(self, command):
		"""
		Here my minishell
		:param command: list of command like ["/bin/ls", "-l"]
		:return:
		"""
		cmd_list = ["/bin/echo"] + command
		p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)

		p_minishell = subprocess.Popen(
			[self.minishell], stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		p_command.stdout.close()
		stdout, stderr = p_minishell.communicate()
		return stdout.replace(self.minishell_prompt, ""), stderr

	def execute_real_shell(self, command):
		"""
		Here the real shell
		:param command: list of command like ["/bin/ls", "-l"] 
		:return:
		"""
		cmd_list = ["/bin/echo"] + command
		p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
		p_real_shell = subprocess.Popen(
			["/bin/bash"], stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		p_command.stdout.close()
		stdout, stderr = p_real_shell.communicate()
		return stdout, stderr.replace("/bin/bash: line 1: ", "")  # because of bash piping

	def compare_returning_code(self, command):
		print subprocess.call(["/bin/echo"] + command + [self.minishell])

	def compare_shells(self, command):
		real_std = self.execute_real_shell(command)
		my_std = self.execute_my_shell(command)
		self.assertEqual(real_std, my_std)

	def valgrind(self, command):
		leaks = QueueProcess(valgrind_wrapper, self.minishell, command)
		leaks.start()

	def test_00_full_bin_ls(self):
		command = ["/bin/ls"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_01_full_bin_ls_opt(self):
		command = ["/bin/ls", "-l"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_02_full_bin_ls_opt(self):
		command = ["/bin/ls", "-l", "-a"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_03_full_bin_ls_opt(self):
		command = ["/bin/ls", "-l", "-a", "-rt"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_04_empty(self):
		command = [""]
		self.compare_shells(command)
		self.valgrind(command)

	def test_05_empty(self):
		command = [" "]
		self.compare_shells(command)
		self.valgrind(command)

	def test_06_empty(self):
		command = [" ", "  "]
		self.compare_shells(command)
		self.valgrind(command)

	def test_07_with_empty_bin_ls(self):
		command = [" ", "/bin/ls"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_08_with_empty_bin_ls(self):
		command = ["   ", "/bin/ls", "    "]
		self.compare_shells(command)
		self.valgrind(command)

	def test_09_with_empty_bin_ls(self):
		command = ["   ", "/bin/ls", "-l", "    "]
		self.compare_shells(command)
		self.valgrind(command)

	def test_10_bin_echo(self):
		command = ["/bin/echo", "toto"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_11_bin_echo(self):
		command = ["/bin/echo", "toto", "tata"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_12_bin_echo(self):
		command = ["   ", "/bin/echo", "  toto  "]
		self.compare_shells(command)
		self.valgrind(command)

	def test_13_bin_echo(self):
		command = ["/bin/echo"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_14_echo(self):
		command = ["echo"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_15_echo(self):
		command = ["echo", "one"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_16_echo(self):
		command = ["echo", "one", "two"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_17_ls(self):
		command = ["ls"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_18_ls(self):
		command = ["ls", "-l"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_19_ls(self):
		command = ["ls", "-la"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_20_ls(self):
		command = ["ls", "-la", "."]
		self.compare_shells(command)
		self.valgrind(command)

	def test_21_fake_command(self):
		command = ["a_very_large_fake_binary_name"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_22_fake_command(self):
		command = ["a_very_large_fake_binary_name", "-o", "/"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_23_env(self):
		command = ["env"]
		self.valgrind(command)

	def test_24_env(self):
		command = ["    env"]
		self.valgrind(command)

	def test_25_env(self):
		command = ["env    "]
		self.valgrind(command)

	def test_26_env(self):
		command = ["    env    "]
		self.valgrind(command)

	def test_27_unsetenv(self):
		command = ["unsetenv", "_"]
		self.valgrind(command)

	def test_28_unsetenv(self):
		command = ["unsetenv", "a_very_large_fake_env_name"]
		self.valgrind(command)

	def test_29_ret_last_command(self):
		command = ["echo", "$?"]
		self.assertEqual(('0\n', ''), self.execute_my_shell(command))
		self.valgrind(command)

	def test_30_ret_last_command(self):
		command = ["echo", "$?", "$?"]
		self.assertEqual(('0 0\n', ''), self.execute_my_shell(command))
		self.valgrind(command)

	def test_31_exit(self):
		command = ["exit"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_32_exit(self):
		command = ["exit", "1"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_33_exit(self):
		command = ["exit", "2"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_99_waiting_process(self):
		raising = []
		for p in self.queue.p:
			p.process.join()
			if p.process.exitcode != 0:
				raising.append(p.args)
		self.assertEqual([], raising)


if __name__ == "__main__":
	unittest.main()
