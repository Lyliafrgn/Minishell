void	add_redir_type(t_token *cur)
{
	while (cur)
	{
		if (cur->type == T_APPEND || cur->type == T_REDIROUT )
		{
            cur->next->type = OUT_FILE;
        }
		if (cur->type == T_HEREDOC || cur->type == T_REDIRIN)
			cur->next->type = IN_FILE;
		cur = cur->next;
	}
}

int process_redirections(t_command *cmd, t_redir *redir)
{
    int i;

    i = 0;
    while (redir->operator[i])
    {
        if (ft_strncmp(redir->operator[i], ">>", 3) == 0)
        {
            if (process_append_fd(cmd, redir->file[i]) == -1)
                return -1;
        }
        else if (ft_strncmp(redir->operator[i], "<<", 3) == 0)
        {
            cmd->fd_in = ft_atoi(redir->file[i]);
        }
        else if (ft_strncmp(redir->operator[i], "<", 2) == 0)
        {
            if (process_input_fd(cmd, redir->file[i]) == -1)
                return -1;
        }
        else if (ft_strncmp(redir->operator[i], ">", 2) == 0)
        {
            if (process_output_fd(cmd, redir->file[i]) == -1)
                return -1;
        }
        i++;
    }
    return 0;
}



Lorsqu'un symbole de redirection est détecté, 
tu vas directement ajouter un token de type T_REDIRIN,
 T_REDIROUT, etc., suivi d'un autre token pour
le fichier associé.

// Fonction de lexing qui détecte les redirections et les fichiers associés
t_token *lexer(char *input) {
    t_token *tokens = NULL;  // Liste des tokens
    t_token *last_token = NULL;
    char *ptr = input;
    
    while (*ptr) {
        // Ignorer les espaces
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }
        
        // Si on rencontre une redirection d'entrée
        if (*ptr == '<') {
            t_token *redir_token = create_token("<", T_REDIRIN);
            if (!tokens) {
                tokens = redir_token;
            } else {
                last_token->next = redir_token;
                redir_token->prev = last_token;
            }
            last_token = redir_token;
            ptr++;
            
            // Si on trouve un fichier après le symbole '<'
            while (isspace(*ptr)) ptr++;  // Ignorer les espaces
            if (*ptr && !isspace(*ptr)) {
                char *file_start = ptr;
                while (*ptr && !isspace(*ptr)) ptr++;  // Récupérer le fichier
                char *file_name = strndup(file_start, ptr - file_start);
                t_token *file_token = create_token(file_name, T_WORD);
                last_token->next = file_token;
                file_token->prev = last_token;
                last_token = file_token;
                free(file_name);
            }
        }
        // Si on rencontre une redirection de sortie
        else if (*ptr == '>') {
            t_token *redir_token = create_token(">", T_REDIROUT);
            if (!tokens) {
                tokens = redir_token;
            } else {
                last_token->next = redir_token;
                redir_token->prev = last_token;
            }
            last_token = redir_token;
            ptr++;
            
            // Si on trouve un fichier après le symbole '>'
            while (isspace(*ptr)) ptr++;  // Ignorer les espaces
            if (*ptr && !isspace(*ptr)) {
                char *file_start = ptr;
                while (*ptr && !isspace(*ptr)) ptr++;  // Récupérer le fichier
                char *file_name = strndup(file_start, ptr - file_start);
                t_token *file_token = create_token(file_name, T_WORD);
                last_token->next = file_token;
                file_token->prev = last_token;
                last_token = file_token;
                free(file_name);
            }
        }
        // Si tu as d'autres symboles de redirection à gérer, tu peux ajouter ici (par exemple, '>>' pour append, '<<' pour here-doc)
        else {
            // Si ce n'est ni une redirection ni un espace, c'est un mot normal (par exemple, une commande ou un argument)
            char *word_start = ptr;
            while (*ptr && !isspace(*ptr) && *ptr != '<' && *ptr != '>' && *ptr != '|') ptr++;  // Récupérer le mot
            char *word = strndup(word_start, ptr - word_start);
            t_token *word_token = create_token(word, T_WORD);
            if (!tokens) {
                tokens = word_token;
            } else {
                last_token->next = word_token;
                word_token->prev = last_token;
            }
            last_token = word_token;
            free(word);
        }
    }

    return tokens;
}