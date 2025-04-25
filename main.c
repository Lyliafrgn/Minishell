#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *rl;
    rl = readline("prompt > ");
    printf("%s\n", rl);
    return (0);
}




int	main(int ac, char **av, char **env)
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
}
