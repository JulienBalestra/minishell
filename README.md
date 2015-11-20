# Minishell


[![Build Status](https://travis-ci.org/JulienBalestra/minishell.svg?branch=master)](https://travis-ci.org/JulienBalestra/minishell)


Recode of a /bin/bash like

# How to launch


	./setup.sh
	./minishell


# Which features are done

* env binary as builtin based on Linux kernel (differ from Darwin: check the testing steps)
* setenv from csh builtin
* unsetenv from csh builtin
* exit
* PATH browsing
* $?
* $$
* $VAR
* ${VAR}

# How to test

The following command will install valgrind for leaks and errors utilities (and gdb).

	./setup.sh && ./run_test.sh