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

    def test_00_ls(self):
        p1 = subprocess.Popen(["/bin/echo", "/bin/ls"],
                              stdout=subprocess.PIPE
                              )

        p2 = subprocess.Popen([self.minishell], stdin=p1.stdout,
                              stdout=subprocess.PIPE)

        p1.stdout.close()  # Allow p1 to receive a SIGPIPE if p2 exits.
        stdout, stderr = p2.communicate()

        real_cmd = subprocess.check_output(["/bin/ls"])

        my_cmd = stdout.replace(self.minishell_prompt, "")
        self.assertEqual(real_cmd, my_cmd)

if __name__ == "__main__":
    unittest.main()