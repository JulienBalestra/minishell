import unittest
import subprocess
import os


class TestMinishell(unittest.TestCase):
    context = os.path.split(os.path.dirname(__file__))[0]
    minishell = "%s/ft_minishell" % context
    testing_dir = "%s/tests/test_resources/" % context
    minishell_prompt = "minishell> "

    @classmethod
    def setUpClass(cls):
        os.chdir(cls.testing_dir)
        # check if the project is well compiled
        assert os.path.isfile(cls.minishell) is True

    def execute_my_shell(self, command):
        cmd_list = ["/bin/echo"] + command
        p_command = subprocess.Popen(cmd_list,
                                     stdout=subprocess.PIPE)
        p_minishell = subprocess.Popen([self.minishell],  # here my minishell
                                       stdin=p_command.stdout,
                                       stdout=subprocess.PIPE)
        p_command.stdout.close()
        stdout, stderr = p_minishell.communicate()
        return stdout.replace(self.minishell_prompt, ""), stderr

    def execute_real_shell(self, command):
        cmd_list = ["/bin/echo"] + command
        p_command = subprocess.Popen(cmd_list,
                                     stdout=subprocess.PIPE)
        p_real_shell = subprocess.Popen(["/bin/bash"],  # here the real shell
                                        stdin=p_command.stdout,
                                        stdout=subprocess.PIPE)
        p_command.stdout.close()
        stdout, stderr = p_real_shell.communicate()
        return stdout, stderr

    def test_00_full_bin_ls(self):
        command = ["/bin/ls"]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_01_full_bin_ls_opt(self):
        command = ["/bin/ls", "-l"]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_02_full_bin_ls_opt(self):
        command = ["/bin/ls", "-l", "-a"]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_03_full_bin_ls_opt(self):
        command = ["/bin/ls", "-l", "-a", "-rt"]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_04_empty(self):
        command = [""]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_05_empty(self):
        command = [" "]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_06_empty(self):
        command = [" ", "  "]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_07_with_empty_bin_ls(self):
        command = [" ", "/bin/ls"]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_08_with_empty_bin_ls(self):
        command = ["   ", "/bin/ls", "    "]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_09_with_empty_bin_ls(self):
        command = ["   ", "/bin/ls", "-l", "    "]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_10_bin_echo(self):
        command = ["/bin/echo", "toto"]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_11_bin_echo(self):
        command = ["/bin/echo", "toto", "tata"]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_12_bin_echo(self):
        command = ["   ", "/bin/echo", "  toto  "]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_13_bin_echo(self):
        command = ["/bin/echo"]
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)


if __name__ == "__main__":
    unittest.main()