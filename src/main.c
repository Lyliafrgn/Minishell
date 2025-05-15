#define RED     "\033[31m"   // Code couleur ANSI pour le rouge
#define RESET   "\033[0m" 
#include <stdio.h>
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

/*static void print_tokens(char *line, t_token *tkn_lst)
{
    t_token *curr_tkn = tkn_lst;

    printf("\n=== Input Line ===\n");
    printf("%s\n", line);
    printf("=== Tokens ===\n");

    while (curr_tkn)
    {
        printf("Token value: *%s*\n", curr_tkn->content);
         printf("  - Type: %u\n", curr_tkn->type);
        curr_tkn = curr_tkn->next;
    }

    printf("===================\n");
}*/

int	main(void)
{
	t_data	*data;
	//int	r_code;

	//r_code = 4;
	data = malloc(sizeof(t_data));
	while (1)
	{
		data->line = readline(MINIMSG);
		if (!data->line)
		{
			break;
		}
		if (data->line[0])
			add_history(data->line);
		//r_code = 
		ft_tokenizer(data);
		//print_tokens(data->line, data->tkn_lst); // VERIFICATION (Debug)
		//printf(RED"return code %d\n"RESET, r_code);
	}
	rl_clear_history();
	return (0);
}