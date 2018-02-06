
shell_basic: basic_commands_impl.c helpers.c history.c splitter.c
	gcc -o shell_basic basic_commands_impl.c helpers.c history.c splitter.c
