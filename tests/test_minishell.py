import unittest
import os
from tools import *
import sys


class TestMinishell(unittest.TestCase):
	context = os.path.split(os.path.dirname(__file__))[0]
	minishell = "%s/minishell" % context
	testing_dir = "%s/tests/test_resources/" % context
	dotdot = "%sdotdot" % testing_dir
	valgrind_binary = False
	dev_null = open(os.devnull, 'w')
	queue = QueueProcess
	linux = True if "linux" in sys.platform else False
	tail = True if "TRUE" in "%s" % os.getenv("VG_TAIL") else False

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
			os.write(2, "VALGRIND NOT AVAILABLE")
		os.chmod("%s/norights" % cls.testing_dir, 000)

	@classmethod
	def tearDownClass(cls):
		cls.dev_null.close()
		os.chmod("%s/norights" % cls.testing_dir, 0755)

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
		return stdout, stderr

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
		if self.valgrind_binary is True:
			leaks = QueueProcess(valgrind_wrapper, self.tail, self.minishell, command)
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

	def test_201_ls(self):
		command = ["\tls", " -la", " \t ."]
		self.compare_shells(command)
		self.valgrind(command)

	def test_202_ls(self):
		command = ["\t  ls", " -la    ", " \t ."]
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

	def test_301_ret_last_command(self):
		command = ["echo", "$?", "$?", "\t$?  "]
		self.assertEqual(('0 0 0\n', ''), self.execute_my_shell(command))
		self.valgrind(command)

	def test_31_exit(self):
		command = ["exit"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_310_exit(self):
		command = ["exit", "0t"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_311_exit(self):
		command = ["exit", "1t"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_312_exit(self):
		command = ["exit", "1", "0"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_313_exit(self):
		command = ["exit", "titi", "0"]
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

	def test_34_echo_pid(self):
		command = ["echo", "$$"]
		stdout, stderr = self.execute_my_shell(command)
		int(stdout.replace("\n", ""))  # not needed the replace
		self.assertEqual("", stderr)
		self.valgrind(command)

	def test_35_kill_pid(self):
		command = ["kill", "$$"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("", stderr)
		self.valgrind(command)

	def test_36_setenv(self):
		command = ["setenv", "toto", "tata"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("", stderr)
		self.valgrind(command)

	def test_361_setenv(self):
		command = ["setenv"]
		self.assertEqual(self.execute_my_shell(command), self.execute_my_shell(["env"]))
		self.valgrind(command)

	def test_37_setenv(self):
		command = ["setenv", "_", "my_shell"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("", stderr)
		self.valgrind(command)

	def test_38_setenv(self):
		command = ["setenv", "_", "my_shell", "too_many"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("setenv: too many arguments\n", stderr)
		self.valgrind(command)

	def test_39_getenv(self):
		command = ["getenv", "LC_ALL"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("C\n", stdout)
		self.assertEqual("", stderr)
		self.valgrind(command)

	def test_40_getenv(self):
		command = ["getenv"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("", stderr)
		self.valgrind(command)

	def test_41_getenv(self):
		command = ["getenv", "_", "my_shell", "too_many"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("getenv: too many arguments\n", stderr)
		self.valgrind(command)

	def test_42_cd(self):
		command = ["cd"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("", stderr)
		self.valgrind(command)

	def test_43_cd(self):
		command = ["cd", "~"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("", stderr)
		self.valgrind(command)

	def test_44_cd_oldpwd(self):
		command = ["cd", "-"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("cd: OLDPWD not set\n", stderr)
		self.valgrind(command)

	def test_45_cd_tmp(self):
		command = ["cd", "/bin"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("", stderr)
		self.valgrind(command)

	def test_46_cd_tmp(self):
		command = ["cd", "/notherethisdirectory"]
		stdout, stderr = self.execute_my_shell(command)
		self.assertEqual("", stdout)
		self.assertEqual("cd: /notherethisdirectory: No such file or directory\n", stderr)
		self.valgrind(command)

	def test_47_cd_oldpwd(self):
		command = ["cd", "/", ";", "cd", "/bin", ";", "cd", "-"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_48_cd_oldpwd(self):
		command = ["cd", "/", ";", "cd", "/bin", ";", "cd", "-", ";", "cd", "-", "cd", "-"]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_49_cd_slashs(self):
		command = ["cd", "///"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_50_cd_slashs(self):
		command = ["cd", "/", ";", "cd", "///bin/", ";", "cd", "-"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_51_cd_slashs(self):
		command = ["cd", "%s" % self.testing_dir.replace("/", "//"), ";",
				   "cd", "///bin/", ";", "cd", "-"]
		self.assertEqual("%s\n" % self.testing_dir[:-1], self.execute_my_shell(command)[0])
		self.valgrind(command)

	def test_52_cd_slashs(self):
		command = ["cd", "%s" % self.testing_dir.replace("/", "//////"), ";",
				   "cd", "///bin/", ";", "cd", "-"]
		self.assertEqual("%s\n" % self.testing_dir[:-1], self.execute_my_shell(command)[0])
		self.valgrind(command)

	def test_53_cd_slashs(self):
		command = ["cd", "%s/" % self.testing_dir, ";", "cd", "///bin/", ";", "cd", "-"]
		self.assertEqual("%s\n" % self.testing_dir[:-1], self.execute_my_shell(command)[0])
		self.valgrind(command)

	def test_54_cd_slashs(self):
		command = ["cd", "/bin//", ";", "pwd"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_55_cd_slashs(self):
		command = ["  cd   /bin//  ; echo $PWD"]
		self.assertEqual(("/bin\n", ""), self.execute_my_shell(command))
		self.valgrind(command)

	def test_55_cd_slashs_b(self):
		command = ["  cd ", "/bin//", " ;", " echo $PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_56_cd_no_exec(self):
		command = ["  ", "/bin//"]
		if self.linux:
			self.compare_shells(command)
		else:
			real = self.execute_real_shell(command)
			my = self.execute_my_shell(command)
			self.assertEqual((real[0], real[1].replace(": is a directory", ": Is a directory")), my)
		self.valgrind(command)

	def test_100_cd_home(self):
		command = ["unsetenv HOME ; cd ~ ; echo $HOME ;"]
		self.assertEqual(('\n', 'cd: HOME not set\n'), self.execute_my_shell(command))
		self.valgrind(command)

	def test_101_cd_home(self):
		command = ["cd", "~/..", ";", "pwd ;"]
		self.compare_shells(command)
		if self.linux:
			self.assertEqual(('/home\n', ''), self.execute_my_shell(command))
		self.compare_shells(command)
		self.valgrind(command)

	def test_102_cd_home(self):
		command = ["cd", "~/../", ";", "pwd ;"]
		if self.linux:
			self.assertEqual(('/home\n', ''), self.execute_my_shell(command))
		self.compare_shells(command)
		self.valgrind(command)

	def test_103_cd_home(self):
		command = ["cd", "~/..////", ";", "pwd ;"]
		self.compare_shells(command)
		if self.linux:
			self.assertEqual(('/home\n', ''), self.execute_my_shell(command))
		self.compare_shells(command)
		self.valgrind(command)

	def test_104_cd_home(self):
		command = ["cd", "~/..////", ";", "pwd ;"]
		self.compare_shells(command)
		if self.linux:
			self.assertEqual(('/home\n', ''), self.execute_my_shell(command))
		self.compare_shells(command)
		self.valgrind(command)

	def test_105_cd_home(self):
		command = ["cd", "~~"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_110_cd_symb(self):
		command = ["cd", "dotdot", ";", "ls"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_111_cd_symb(self):
		command = ["cd", "%s" % self.dotdot, ";", "cd", "..", ";", "cd", "-"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_112_cd_symb(self):
		command = ["cd", "%s" % self.dotdot, ";", "ls", ";", "cd", "..", ";", "cd", "-"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_113_cd_symb(self):
		command = ["cd", "%s" % self.dotdot, ";", "cd", "dotdot", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_114_cd_symb(self):
		command = ["cd", "%s" % self.dotdot, ";", "cd", "dotdot", ";", "echo", "$PWD", "cd", "-", ";", "cd", "-"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_115_cd_symb(self):
		command = ["cd", "%s" % self.dotdot, ";", "cd", "dotdot", ";", "echo", "$PWD", ";", "cd", "-", ";", "cd", "-"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_116_cd_symb(self):
		command = ["cd", "%s" % self.dotdot, ";", "ls", ";", "cd", "..", ";", "cd", "-", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_117_cd_symb(self):
		command = ["cd", "%s" % self.dotdot, ";", "ls", ";", "cd", "./../", ";", "cd", "-", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_118_cd_symb(self):
		command = ["cd", "%s" % self.dotdot, ";", "ls", ";", "cd", "..", ";", "cd", "dotdot", ";", "echo", "$PWD"]
		# self.compare_shells(command) TODO
		self.valgrind(command)

	def test_119_cd_symb(self):
		command = ["cd", "%s" % self.testing_dir, ";", "ls", ";",
				   "cd", "./dotdot", ";", "cd", "dotdot", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_120_cd_symb(self):
		command = ["cd", "-P", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_121_cd_symb(self):
		command = ["cd", "-L", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_122_cd_symb(self):
		command = ["cd", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_123_cd_opts(self):
		command = ["cd", ";", "cd", "%s" % self.testing_dir, ";",
				   "echo", "$PWD", ";", "cd", "-P", "-", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_124_cd_opts(self):
		command = ["cd", ";", "cd", "%s" % self.testing_dir, ";",
				   "echo", "$PWD", ";", "cd", "-L", "-", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_125_cd_opts(self):
		command = ["cd", ";", "cd", "%s" % self.testing_dir, ";",
				   "echo", "$PWD", ";", "cd", "-L", "dotdot", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_126_cd_opts(self):
		command = ["cd", ";", "cd", "%s" % self.testing_dir, ";",
				   "echo", "$PWD", ";", "cd", "-P", "dotdot", ";", "echo", "$PWD"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_127_cd_opts(self):
		command = ["cd", "-Q", ";", "echo", "$?"]
		my = self.execute_my_shell(command)
		self.assertEqual(('2\n', 'cd: -Q: invalid option\ncd: usage: cd [-L OR -P] [dir]\n'), my)
		self.valgrind(command)

	def test_128_cd_opts(self):
		command = ["cd", "-P", "-L", ";", "echo", "$?"]
		my = self.execute_my_shell(command)
		self.assertEqual(('1\n', 'cd: usage: cd [-L OR -P] [dir]\n'), my)
		self.valgrind(command)

	def test_129_cd_opts(self):
		command = ["cd", "-L", "-P", ";", "echo", "$?"]
		my = self.execute_my_shell(command)
		self.assertEqual(('1\n', 'cd: usage: cd [-L OR -P] [dir]\n'), my)
		self.valgrind(command)

	def test_130_cd_opts(self):
		command = ["cd", "-L", "%s" % self.testing_dir, ";", "echo", "$?", ";",
				   "cd", "-L", "%s/dotdot" % self.testing_dir, ";", "cd", "-L", "-", ";"]
		my = self.execute_my_shell(command)
		self.assertEqual(("0\n%s\n" % self.testing_dir[:-1], ""), my)
		self.valgrind(command)

	def test_131_cd_opts(self):
		command = ["cd", "-P", "%s" % self.testing_dir, ";", "echo", "$?", ";",
				   "cd", "-P", "%s/dotdot" % self.testing_dir, ";", "cd", "-P", "-", ";"]
		my = self.execute_my_shell(command)
		self.assertEqual(("0\n%s\n" % self.testing_dir[:-1], ""), my)
		self.valgrind(command)

	def test_132_cd_chdir(self):
		command = ["setenv", "CHDIR", "%s" % self.testing_dir, ";",
				   "echo", "$CHDIR", ";", "cd", "/tmp", ";", "cd", "dotdot", ";", "ls"]
		my = self.execute_my_shell(command)
		self.assertEqual(("%s\ndotdot\nfile00\nfile01\nnorights\n" % self.testing_dir, ""), my)
		self.valgrind(command)

	def test_133_cd_chdir(self):
		command = ["setenv", "CHDIR", "/:%s" % self.testing_dir, ";",
				   "echo", "$CHDIR", ";", "cd", "/tmp", ";", "cd", "dotdot", ";", "ls"]
		my = self.execute_my_shell(command)
		self.assertEqual(("/:%s\ndotdot\nfile00\nfile01\nnorights\n" % self.testing_dir, ""), my)
		self.valgrind(command)

	def test_134_cd_permission(self):
		command = ["cd", "%snorights" % self.testing_dir]
		self.compare_shells(command)
		self.valgrind(command)

	def test_60_env_only(self):
		command = ["env"]
		self.valgrind(command)

	def test_61_env_only(self):
		command = ["    env"]
		self.valgrind(command)

	def test_62_env_only(self):
		command = ["env    "]
		self.valgrind(command)

	def test_63_env_only(self):
		command = ["    env    "]
		self.valgrind(command)

	def test_64_env_no_end_line(self):
		command = ["env", "-0"]
		no_endline = self.execute_my_shell(command)[0].split("\n")
		with_endline = self.execute_my_shell(["env"])[0].split("\n")
		self.assertGreater(len(with_endline), len(no_endline))
		self.valgrind(command)

	def test_65_env_no_end_line(self):
		command = ["env", "--null"]
		self.assertEqual(self.execute_my_shell(command), self.execute_my_shell(["env", "-0"]))
		self.valgrind(command)

	def test_66_env_unset(self):
		command = ["env", "-u"]
		self.assertEqual(('', "env: option requires an argument -- 'u'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_67_env_unset(self):
		command = ["env", "-i", "-u"]
		self.assertEqual(('', "env: option requires an argument -- 'u'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_68_env_unset(self):
		command = ["env", "-i", "-0", "-u"]
		self.assertEqual(('', "env: option requires an argument -- 'u'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_69_env_unset(self):
		command = ["env", "-i", "-0", "-u", "VAR"]
		if self.linux is True:
			self.compare_shells(command)
		self.assertEqual(('', ""), self.execute_my_shell(command))
		self.valgrind(command)

	def test_70_env_unset(self):
		command = ["env", "-i", "-0", "-u", "VAR", "-u", "OTHER_VAR"]
		if self.linux is True:
			self.compare_shells(command)
		self.assertEqual(('', ""), self.execute_my_shell(command))
		self.valgrind(command)

	def test_71_env_unset(self):
		command = ["env", "-i", "-u", "VAR", "-u", "OTHER_VAR"]
		if self.linux is True:
			self.compare_shells(command)
		self.valgrind(command)

	def test_72_env_unset_set(self):
		command = ["env", "-i", "-u", "VAR", "-u", "OTHER_VAR", "NEW=VALUE"]
		if self.linux is True:
			self.compare_shells(command)
		self.assertEqual(('NEW=VALUE\n', ""), self.execute_my_shell(command))
		self.valgrind(command)

	def test_73_env_unset_set(self):
		command = ["env", "-i", "-u", "VAR", "-u", "OTHER_VAR", "NEW=VALUE", "NEW_NEW=NEW_VALUE"]
		if self.linux is True:
			self.compare_shells(command)
		self.assertEqual(('NEW=VALUE\nNEW_NEW=NEW_VALUE\n', ""), self.execute_my_shell(command))
		self.valgrind(command)

	def test_74_env_unset_set_null(self):
		command = ["env", "-i", "-0", "-u", "VAR", "-u", "OTHER_VAR", "NEW=VALUE", "NEW_NEW=NEW_VALUE"]
		if self.linux is True:
			self.compare_shells(command)
		self.assertEqual(('NEW=VALUE\x00NEW_NEW=NEW_VALUE\x00', ""), self.execute_my_shell(command))
		self.valgrind(command)

	def test_75_env_unset_set_null(self):
		command = ["env", "-i", "-u", "VAR", "-u", "OTHER_VAR", "-0", "NEW=VALUE", "NEW_NEW=NEW_VALUE"]
		if self.linux is True:
			self.compare_shells(command)
		self.assertEqual(('NEW=VALUE\x00NEW_NEW=NEW_VALUE\x00', ""), self.execute_my_shell(command))
		self.valgrind(command)

	def test_76_env_unset_set_null(self):
		command = ["env", "-u", "VAR", "-u", "OTHER_VAR", "-0", "-i", "NEW=VALUE", "NEW_NEW=NEW_VALUE"]
		if self.linux is True:
			self.compare_shells(command)
		self.assertEqual(('NEW=VALUE\x00NEW_NEW=NEW_VALUE\x00', ""), self.execute_my_shell(command))
		self.valgrind(command)

	def test_77_env_unset_set_null(self):
		command = ["env", "-u", "VAR", "-i", "-u", "OTHER_VAR", "-0", "NEW=VALUE", "NEW_NEW=NEW_VALUE"]
		if self.linux is True:
			self.compare_shells(command)
		self.assertEqual(('NEW=VALUE\x00NEW_NEW=NEW_VALUE\x00', ""), self.execute_my_shell(command))
		self.valgrind(command)

	def test_78_env_set_ignore(self):
		command = ["env", "-i", "NEW=VALUE"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_79_env_set_ignore(self):
		command = ["env", "-i", "NEW=VALUE", "NEW_NEW=NEW_VALUE"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_80_run_env(self):
		command = ["env", "-i", "PATH=", "ls"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_81_run_env(self):
		command = ["env", "-i", "PATH=/bin", "ls"]
		self.compare_shells(command)
		self.assertEqual(('dotdot\nfile00\nfile01\nnorights\n', ''), self.execute_my_shell(command))
		self.valgrind(command)

	def test_82_run_env(self):
		command = ["env", "-i", "PATH=/bin", "ls", "-l"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_83_run_env(self):
		command = ["env", "-i", "PATH=/bin", "VAR=VALUE", "ls", "-l"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_84_run_env(self):
		command = ["env", "-i", "PATH=/bin", "VAR=VALUE", "NEW=", "ls", "-l"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_85_ignore_env_no_dup(self):
		command = ["env", "-i", "VAR=VALUE", "VAR=VALUE"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_86_ignore_env_no_dup(self):
		command = ["env", "-i", "VAR=VALUE", "VAR=VALUE", "NEW="]
		self.compare_shells(command)
		self.valgrind(command)

	def test_87_ignore_env_no_dup(self):
		command = ["env", "-i", "VAR=VALUE", "VAR=VALUE", "NEW=", "NEW=OK"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_88_ignore_env_no_dup(self):
		command = ["env", "-i", "NEW=", "NEW=OK", "NEW=", "NEW=OK"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_89_ignore_env_no_dup(self):
		command = ["env", "-i", "NEW=", "NEW=OK", "NEW=", "NEW=OK", "PATH=/bin", "ls"]
		self.compare_shells(command)
		self.assertEqual(('dotdot\nfile00\nfile01\nnorights\n', ''), self.execute_my_shell(command))
		self.valgrind(command)

	def test_90_env(self):
		command = ["env", "ls"]
		self.compare_shells(command)
		self.assertEqual(('dotdot\nfile00\nfile01\nnorights\n', ''), self.execute_my_shell(command))
		self.valgrind(command)

	def test_91_env(self):
		command = ["env", "PATH=", "ls"]
		self.assertEqual(('', 'env: ls: No such file or directory\n'), self.execute_my_shell(command))
		self.compare_shells(command)
		self.valgrind(command)

	def test_92_env(self):
		command = ["env", "PATH=", "ls"]
		self.assertEqual(('', 'env: ls: No such file or directory\n'), self.execute_my_shell(command))
		self.compare_shells(command)
		self.valgrind(command)

	def test_93_env(self):
		command = ["env", "PATH=", "PATH=/bin", "ls"]
		self.assertEqual(('dotdot\nfile00\nfile01\nnorights\n', ''), self.execute_my_shell(command))
		self.compare_shells(command)
		self.valgrind(command)

	def test_94_unsetenv(self):
		command = ["env", "-u", "PATH", "ls"]
		self.assertEqual(('', 'env: ls: No such file or directory\n'), self.execute_my_shell(command))
		self.valgrind(command)

	def test_95_unsetenv(self):
		command = ["env", "-u", "PATH", "-u", "LC_ALL", "ls"]
		self.assertEqual(('', 'env: ls: No such file or directory\n'), self.execute_my_shell(command))
		self.valgrind(command)

	def test_96_unsetenv(self):
		command = ["env", "-u", "PATH", "-u", "LC_ALL", "/bin/ls"]
		self.assertEqual(('dotdot\nfile00\nfile01\nnorights\n', ''), self.execute_my_shell(command))
		self.valgrind(command)

	def test_97_unsetenv(self):
		command = ["env", "-u", "PATH", "-u", "LC_ALL", "PATH=/bin", "/bin/ls"]
		self.assertEqual(('dotdot\nfile00\nfile01\nnorights\n', ''), self.execute_my_shell(command))
		self.valgrind(command)

	def test_98_unsetenv_display(self):
		command = ["env", "-u", "PATH", "-u", "LC_ALL", "PATH=a_very_special_string"]
		my_std = self.execute_my_shell(command)[0].split("\n")
		self.assertIn("PATH=a_very_special_string", my_std)
		self.assertNotIn("LC_ALL", my_std)
		self.valgrind(command)

	def test_99_unsetenv_display(self):
		command = ["env", "-u", "PATH", "-u", "LC_ALL", "PATH=", "PATH=a_very_special_string"]
		my_std = self.execute_my_shell(command)[0].split("\n")
		self.assertIn("PATH=a_very_special_string", my_std)
		self.assertNotIn("LC_ALL", my_std)
		self.valgrind(command)

	def test_100_use_variable(self):
		command = ["echo", "$PATH"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_101_use_variable(self):
		command = ["echo", "${PATH}"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_102_use_variable(self):
		command = ["echo", "${PATH}", "$PATH"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_103_use_variable(self):
		command = ["echo", "${NO_REALLY_INSIDE_ENV}"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_104_use_variable(self):
		command = ["echo", "$NO_REALLY_INSIDE_ENV"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_105_use_variable(self):
		command = ["echo", "$NO_REALLY_INSIDE_ENV", "$PATH"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_106_use_variable(self):
		command = ["echo", "$NO_REALLY_INSIDE_ENV", "$PATH", "$NO_REALLY_INSIDE_ENV"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_107_use_variable(self):
		command = ["echo", "$NO_REALLY_INSIDE_ENV", "$PATH", "$NO_REALLY_INSIDE_ENV", "${PATH}"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_108_no_variable(self):
		command = ["echo", "$"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_109_variable(self):
		command = ["echo", "$", "$NO_REALLY_INSIDE_ENV", "$PATH", "$NO_REALLY_INSIDE_ENV", "${PATH}"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_110_multi_run(self):
		command = ["echo", "toto", ";", "echo", "tata"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_111_multi_run(self):
		command = ["echo", "toto", ";", "echo", "tata", ";", "ls"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_112_multi_run(self):
		command = ["echo", "toto", ";"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_113_multi_run(self):
		command = ["echo", "toto", ";", "echo", "titi", ";"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_114_multi_run(self):
		command = ["env", "PATH=/tmp", "ls", ";", "echo", "titi", ";"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_115_multi_run(self):
		command = ["env", "PATH=/tmp", "ls", ";", "echo", "titi", ";", "exit"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_116_multi_run(self):
		command = ["env", "PATH=/tmp", "ls", ";", "echo", "titi", ";", "exit", ";"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_117_multi_run(self):
		command = ["env", "PATH=/tmp", "ls", ";", ";", "echo", "titi", ";", "exit", ";"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_118_multi_run(self):
		command = [";", "ls"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_119_multi_run(self):
		command = ["ls", ";", "ls", ";", ";"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_120_multi_run(self):
		command = ["ls", ";", "ls", ";;"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_121_multi_run(self):
		command = ["ls", ";", "ls", " ; ;  "]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_122_multi_run(self):
		command = ["    ls    ", "   ;    ", "ls", " ; ;  "]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_123_multi_run(self):
		command = ["exit", "env", "PATH=/tmp", "ls", ";", "echo", "titi", ";", "exit", ";"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_124_solo(self):
		command = [";"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_125_solo(self):
		command = [";;"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_126_solo(self):
		command = [";;;"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_127_solo(self):
		command = [";", ";"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_128_solo(self):
		command = [";", ";", ";"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_129_solo(self):
		command = ["   ; "]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_130_solo(self):
		command = ["   ;   ;"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_131_solo(self):
		command = [" \t  ; ", ";"]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_132_solo(self):
		command = ["   ; ; "]
		self.assertEqual(('', "syntax error near unexpected token `;'\n"), self.execute_my_shell(command))
		self.valgrind(command)

	def test_Z999Z_waiting_process(self):
		raising = []
		for p in self.queue.p:
			p.process.join()
			if p.process.exitcode != 0:
				raising.append(p.args)
		self.assertEqual([], raising)


if __name__ == "__main__":
	unittest.main()
