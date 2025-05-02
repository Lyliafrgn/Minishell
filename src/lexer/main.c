#include <stdio.h>
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main(void)
{
	t_data	*data;

	while (1)
	{
		data->line = readline(MINIMSG);
		if (!data->line)
		{	
			break ;
		}
		if (data->line[0])
			add_history(data->line);
		ft_tokenizer(data);//checks syntaxe & tokenize 
		free(line);
	}
	rl_clear_history();
	return (0);
}