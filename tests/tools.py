import subprocess
from multiprocessing import Process, cpu_count


def valgrind_wrapper(program, command):
	"""
	Valgrind wrapper for unittesting in Python for minishell
	:param program: the binary to test
	:param command: the command to run into the minishell like ["ls", "-l"]
	:return: False if no issue was found else return the summary of issues by raising
	"""
	valgrind = ["valgrind"]
	cmd_list = ["/bin/echo"] + command

	p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
	p_minishell = subprocess.Popen(
		valgrind + [program], stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	p_command.stdout.close()
	stdout, stderr = p_minishell.communicate()

	summary = [leak.split("==    ")[1] for leak in stderr.split("\n") if "lost:" in leak]
	if len(summary) > 0 and "definitely lost: 0 bytes in 0 blocks" not in summary:
		raise AssertionError("%s" % summary)

	summary = stderr.split("\n")[-2].split("== ")[1]
	if "ERROR SUMMARY: 0 errors from 0 contexts" not in summary:
		raise AssertionError("%s" % summary)
	return False


class QueueProcess:
	p = []
	size = cpu_count() * 6

	def __init__(self, function, *args):
		self.args = args
		self.function = function
		self.process = Process(target=self.function, args=self.args)

	def start(self):
		self.manage_size()
		self.process.start()
		self.p.append(self)

	def manage_size(self):
		state = []
		for p in self.p:
			if p.process.is_alive():
				state.append(p.process)
		if len(state) > self.size:
			state[0].join()
