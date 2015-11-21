import subprocess
from multiprocessing import Process, cpu_count
import os


def valgrind_wrapper(program, command, full_leaks=False):
	"""
	Valgrind wrapper for unittesting in Python for minishell
	:param program: the binary to test
	:param command: the command to run into the minishell like ["ls", "-l"]
	:return: False if no issue was found else return the summary of issues by raising
	"""
	valgrind = ["valgrind"]
	if full_leaks is True:
		valgrind = ["valgrind", "--leak-check=full"]
	cmd_list = ["/bin/echo"] + command

	p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
	p_minishell = subprocess.Popen(
		valgrind + [program], stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	p_command.stdout.close()
	stdout, stderr = p_minishell.communicate()

	summary = [leak.split("==    ")[1] for leak in stderr.split("\n") if "lost:" in leak]
	if len(summary) > 0 and "definitely lost: 0 bytes in 0 blocks" not in summary:
		if full_leaks is False:
			valgrind_wrapper(program, command, True)
			return False
		os.write(2, "\n\n%s\n" % str(command))
		os.write(2, "%s\n" % stderr)
		raise AssertionError("%s" % summary)

	summary = stderr.split("\n")[-2].split("== ")[1]
	if "ERROR SUMMARY: 0 errors from 0 contexts" not in summary:
		os.write(2, "\n\n%s\n" % str(command))
		os.write(2, "%s\n" % stderr)
		raise AssertionError("%s" % summary)
	return False


class QueueProcess:
	p = []
	cores = cpu_count() + 1
	join_number = (cores / 2) + 1

	def __init__(self, function, tail, *args):
		self.args = args
		self.function = function
		self.tail = tail
		self.process = Process(target=self.function, args=self.args)

	def start(self):
		self.manage_queue()
		self.process.start()
		if self.tail is True:
			self.process.join()
			if self.process.exitcode != 0:
				raise AssertionError
		self.p.append(self)

	def manage_queue(self):
		state = [p for p in self.p if p.process.is_alive()]
		if len(state) > self.cores:
			for i in range(0, self.join_number):
				state[i].process.join()
