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

    def execute_my_shell(self, command):
        cmd_list = ["/bin/echo"] + command
        p_command = subprocess.Popen(cmd_list,
                                     stdout=subprocess.PIPE)
        p_minishell = subprocess.Popen([self.minishell],
                                       stdin=p_command.stdout,
                                       stdout=subprocess.PIPE)
        p_command.stdout.close()
        stdout, stderr = p_minishell.communicate()
        return stdout.replace(self.minishell_prompt, ""), stderr

    def execute_real_shell(self, command):
        cmd_list = ["/bin/echo"] + command
        p_command = subprocess.Popen(cmd_list,
                                     stdout=subprocess.PIPE)
        p_real_shell = subprocess.Popen(["/bin/bash"],
                                        stdin=p_command.stdout,
                                        stdout=subprocess.PIPE)
        p_command.stdout.close()
        stdout, stderr = p_real_shell.communicate()
        return stdout, stderr

    def test_00_full_bin_ls(self):
        command = ["/bin/ls"]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)

    def test_01_full_bin_ls_opt(self):
        command = ["/bin/ls", "-l"]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)

    def test_02_full_bin_ls_opt(self):
        command = ["/bin/ls", "-l", "-a"]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)

    def test_03_full_bin_ls_opt(self):
        command = ["/bin/ls", "-l", "-a", "-rt"]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)

    def test_04_empty(self):
        command = [""]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)

    def test_05_empty(self):
        command = [" "]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)

    def test_06_empty(self):
        command = [" ", "  "]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)

    def test_07_with_empty_bin_ls(self):
        command = [" ", "/bin/ls"]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)

    def test_08_with_empty_bin_ls(self):
        command = ["   ", "/bin/ls", "    "]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)

    def test_09_with_empty_bin_ls(self):
        command = ["   ", "/bin/ls", "-l", "    "]
        real_stdout = self.execute_real_shell(command)[0]
        my_stdout = self.execute_my_shell(command)[0]
        self.assertEqual(real_stdout, my_stdout)


if __name__ == "__main__":
    unittest.main()