/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:45:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/12 16:54:45 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execute_all(char *input, t_env *my_env)
{
    int     status;
    int     i;
    int     num_pipes;
    int     **pipe;
    char    **commands;
    pid_t	*pid;

    num_pipes = ft_count_pipes(input);
    pid = malloc(sizeof(pid_t) * (num_pipes + 1));
    if (!pid)
        return ;
    if (num_pipes == 0)
    {
        if (ft_is_built_command(input))
        {
            ft_execute_command(input, my_env);
            free(pid);
            return ;
        }
        pid[0] = fork();
	    if (pid[0] == -1)
		    ft_putstr_fd("Error with fork\n", 2);
	    if (pid[0] == 0)
            ft_execute_command(input, my_env);
        else
            waitpid(pid[0], &status, 0);
        free(pid);
        return ;
    }
    commands = ft_split_by_pipes(input);
    if (!commands)
        return ;
    pipe = ft_create_pipes(num_pipes);
    pid[0] = ft_create_f_process(commands[0], pipe[0], my_env);
    i = 1;
    while (i < num_pipes)
    {
        pid[i] = ft_create_m_process(commands[i], pipe[i - 1], pipe[i], my_env);
        i++;
    }
    pid[i] = ft_create_l_process(commands[i], pipe[i - 1], my_env);
    i = 0;
    while (i < num_pipes)
    {
        close(pipe[i][0]);
        close(pipe[i][1]);
        i++;
    }
    i = 0;
    while (i <= num_pipes)
    {
        waitpid(pid[i], &status, 0);
        i++;
    }
    ft_free_array(commands);
    free(pid);
}