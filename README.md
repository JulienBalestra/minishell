# Minishell


[![Build Status](https://travis-ci.org/JulienBalestra/minishell.svg?branch=master)](https://travis-ci.org/JulienBalestra/minishell)


Recode of a /bin/bash like

# How to launch


	./setup.sh
	./minishell


# Which features are done

* env binary as builtin
* setenv from csh builtin
* unsetenv from csh builtin
* exit
* $PATH browsing
* $?
* $$

# How to test


	./setup.sh && ./run_test.sh