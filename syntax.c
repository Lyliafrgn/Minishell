#include "minishell.h"

int syntax_check(t_token *token_lst)
{
    t_token *current;
    
    current = token_lst;
    while (current)
    {
        if (current->type == 2)
        {
            if (current->value[0] == '|')
            {
                if (!current->next || current == tkn_lst) // Pipe al inicio o sin comando después
                    return (ft_putstr_fd("Syntax error: invalid pipe\n", 2), 0);
            }
            else if (current->value[0] == '>' || current->value[0] == '<')
            {
                if (!current->next || !(current->next->type == WORD || current->next->type == QUOTED)) // Redirección sin archivo o token válido después
                    return (ft_putstr_fd("Syntax error: invalid redirection\n", 2), 0);
            }
        }
        current = current->next;
    }
    return (1); // Sintaxis válida
}
