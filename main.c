#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main(void)
{
    char *rl;
    while ((rl =  readline("minishell> ")) != NULL)
	{
		if (*rl)
		{
			add_history(rl);
		}
		printf("%s\n", rl);
		free(rl);
	}
    return (0);
}
int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ft_lexer(line);
		free(line);
	}
	return (s = data->exit_status, rl_clear_history());
}



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
