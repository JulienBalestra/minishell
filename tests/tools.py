import subprocess


def valgrind_wrapper(program, leaks=False, errors=False, command=None):
	"""
	Valgrind wrapper for unittesting in Python for minishell
	:param program: the binary to test
	:param leaks: True or False -> override errors mode if True
	:param errors: True or False -> useless if leaks is True
	:param command: the command to run into the minishell like ["ls", "-l"]
	:return: False if no issue was found else return the summary of issues
	"""
	valgrind = "valgrind"
	if leaks is True:
		vg_cmd = [valgrind, "--tool=memcheck", "--leak-check=full"]
	elif errors is True:
		vg_cmd = [valgrind, "--track-origins=yes"]
	else:
		raise RuntimeError("Choose leaks or errors mode")

	cmd_list = ["/bin/echo"] + command
	p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)

	p_minishell = subprocess.Popen(vg_cmd + [program], stdin=p_command.stdout, stdout=subprocess.PIPE,
								   stderr=subprocess.PIPE)
	p_command.stdout.close()
	stdout, stderr = p_minishell.communicate()

	if leaks is True:
		summary = [leak.split("==    ")[1] for leak in stderr.split("\n") if "lost:" in leak]
		if len(summary) > 0 and "definitely lost: 0 bytes in 0 blocks" not in summary[0]:
			return summary
	elif errors is True:
		summary = stderr.split("\n")[-2].split("== ")[1]
		if "ERROR SUMMARY: 0 errors from 0 contexts" not in summary:
			return summary
	return False
