#include "../../minishell.h"

int	ft_is_in_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

char	*ft_super_strjoin(char *new_str, char *toadd)
{
	int		new_str_len;
	int		toadd_len;
	int		new_len;
	char	*join;

	if (new_str == NULL && toadd == NULL)
		return (NULL);
	new_str_len = ft_strlen(new_str);
	toadd_len = ft_strlen(toadd);
	new_len = new_str_len + toadd_len;
	join = malloc(sizeof(char) * (new_len + 1));
	if (!join)
		return (NULL);
	if (new_str != NULL)
		ft_strlcpy(join, new_str, new_str_len + 1);
	if (toadd)
		ft_strlcpy(join + new_str_len, toadd, toadd_len + 1);
	join[new_len] = '\0';
	if (new_str != NULL)
		free(new_str);
	if (toadd != NULL)
		free(toadd);
	return (join);
}