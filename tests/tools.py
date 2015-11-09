import subprocess
from multiprocessing import Process


def valgrind_wrapper(program, leaks, command):
	"""
	Valgrind wrapper for unittesting in Python for minishell
	:param program: the binary to test
	:param leaks: True or False -> override errors mode if True
	:param command: the command to run into the minishell like ["ls", "-l"]
	:return: False if no issue was found else return the summary of issues
	"""
	valgrind = "valgrind"
	if leaks is True:
		vg_cmd = [valgrind, "--tool=memcheck", "--leak-check=full"]
	else:
		vg_cmd = [valgrind, "--track-origins=yes"]

	cmd_list = ["/bin/echo"] + command
	p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
	p_minishell = subprocess.Popen(vg_cmd + [program], stdin=p_command.stdout, stdout=subprocess.PIPE,
								   stderr=subprocess.PIPE)
	p_command.stdout.close()
	stdout, stderr = p_minishell.communicate()

	if leaks is True:
		summary = [leak.split("==    ")[1] for leak in stderr.split("\n") if "lost:" in leak]
		if len(summary) > 0 and "definitely lost: 0 bytes in 0 blocks" not in summary:
			raise AssertionError("%s" % summary)
	else:
		summary = stderr.split("\n")[-2].split("== ")[1]
		if "ERROR SUMMARY: 0 errors from 0 contexts" not in summary:
			raise AssertionError("%s" % summary)

	return False


class QueueProcess(object):
	process_queue = {}

	def __init__(self, function, *args):
		self.function = function
		self.process = Process(target=self.function, args=args)

	def run(self):
		self.process.start()
