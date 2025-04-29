#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

12

/*int	main(void)
{
	t_data	data;

	init_data(&data);      // initialise env, exit_code, etc.
	lexer(&data);          // → data.token rempli
	parser(&data);         // → data.cmd rempli
	exec_all(&data);       // → exécute data.cmd
	clean_data(&data);     // libère tout
}*/