import unittest
import time
import os
from tools import *


class TestMinishell(unittest.TestCase):
	context = os.path.split(os.path.dirname(__file__))[0]
	minishell = "%s/minishell" % context
	testing_dir = "%s/tests/test_resources/" % context
	minishell_prompt = "minishell> "
	compiled, valgrind_binary = False, False
	dev_null = open(os.devnull, 'w')
	queue = QueueProcess

	@classmethod
	def setUpClass(cls):
		os.chdir(cls.testing_dir)
		# check if the project is well compiled
		if os.path.isfile(cls.minishell) is False:
			if subprocess.call(["make", "-C", cls.context, "-j"], stdout=cls.dev_null) == 0:
				pass
			elif subprocess.call(["make", "-C", cls.context], stdout=cls.dev_null) == 0:
				os.write(2, "FAILED TO MAKE WITH -j")
			else:
				raise RuntimeError("compilation failed in %s" % cls.context)
		else:
			cls.compiled = True
		try:
			if subprocess.call(["valgrind", "--version"]) == 0:
				cls.valgrind_binary = True
		except OSError:
			pass

	@classmethod
	def tearDownClass(cls):
		if cls.compiled is False:
			assert subprocess.call(["make", "fclean", "-C", cls.context], stdout=cls.dev_null) == 0
		if cls.valgrind_binary is False:
			raise AssertionError("which valgrind")
		cls.dev_null.close()
		for i in range(1, 600):
			if cls.queue.q.unfinished_tasks != 0:
				time.sleep(0.1)
			else:
				os.write(2, "<%s> %s did %d cycle%s of 0.1s" % (
					cls.tearDownClass.__name__, cls.queue.__name__, i, "s" if i > 1 else ""))
				break
		assert cls.queue.q.qsize() == 46
		assert cls.queue.q.unfinished_tasks == 0

	def execute_my_shell(self, command):
		"""
		Here my minishell
		:param command: list of command like ["/bin/ls", "-l"]
		:return:
		"""
		cmd_list = ["/bin/echo"] + command
		p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)

		p_minishell = subprocess.Popen([self.minishell], stdin=p_command.stdout, stdout=subprocess.PIPE,
									   stderr=subprocess.PIPE)
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
		p_real_shell = subprocess.Popen(["/bin/bash"], stdin=p_command.stdout, stdout=subprocess.PIPE,
										stderr=subprocess.PIPE)
		p_command.stdout.close()
		stdout, stderr = p_real_shell.communicate()
		return stdout, stderr.replace("/bin/bash: line 1: ", "")  # because of bash piping

	def compare_shells(self, command):
		real_std = self.execute_real_shell(command)
		my_std = self.execute_my_shell(command)
		self.assertEqual(real_std, my_std)

	def valgrind(self, command):
		leaks = QueueProcess(valgrind_wrapper, self.minishell, True, command)
		errors = QueueProcess(valgrind_wrapper, self.minishell, False, command)
		leaks.start(), errors.start()

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


if __name__ == "__main__":
	unittest.main()
