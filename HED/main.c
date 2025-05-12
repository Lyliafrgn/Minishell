#include <stdio.h>
//#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>


int main(void)
{
    char *rl;
    while (1)
	{
		rl =  readline("minishell> ");
		if (!rl)
			break;
		if (*rl)
		{
			add_history(rl);
		}
		printf("%s\n", rl);
		free(rl);
	}
    return (0);
}
/*int	main(void)
{
	t_data	*data;

	//init(&data); // initialise env, exit_code, etc.
	while (1)
	{
		data->line = readline(MINIMSG);
		if (!data->line)
		{	//free_all(&data, "exit", [exit code])
			break ;
		}
		if (data->line[0])
			add_history(data->line);
		ft_tokenizer(data);//checks syntaxe & tokenize 
		//parsing(&data);         // → data.cmd rempli
		//exec(&data);       // → exécute data.cmd
		//clean(&data);     // libère tout
		free(data->line);
	}
	rl_clear_history();
	//free_all(checker avec V les allocations faites)
	return (0);
}*/

/*int	main(void)
{
	t_data	data;

	init_data(&data);      // initialise env, exit_code, etc.
	lexer(&data);          // → data.token rempli
	parser(&data);         // → data.cmd rempli
	exec_all(&data);       // → exécute data.cmd
	clean_data(&data);     // libère tout
}*/

/*int	main(int ac, char **av, char **env)
{
	t_data *const	data = ft_create_data(ac, av, env);
	int				s;

	while (1)
	{
		data->line = readline("prompt >");
		if (!data->line)
			break ;
		if (data->line[0] != '\0')
			add_history(data->line);
		if (ft_lexer(data) == SUCCESS && ft_parser(data) == SUCCESS)
			launch_exec(data);
	}
	return (s = data->exit_status, rl_clear_history(), ft_free_all(data), s);
}*/
