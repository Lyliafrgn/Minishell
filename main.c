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

	if (!data || ac != 1)
		return (-1);
	while (1)
	{
		signal(SIGINT, &ft_standard_handler);
		signal(SIGQUIT, SIG_IGN);
		data->line = readline(MINISPELL);
		if (!data->line)
			break ;
		ft_exitstatus_signal(data);
		if (data->line[0] != '\0')
			add_history(data->line);
		if (ft_lexer(data) == SUCCESS && ft_parser(data) == SUCCESS)
			ft_launch_exec(data);
		ft_wait_for_children(data);
		ft_reset_data(data);
	}
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
	return (s = data->exit_status, rl_clear_history(), ft_free_all(data), s);
}
