

static int	ft_get_next_step(char *str, char *new_str)
{
	char	*grab;
	int		res;

	if (!str || *str == '\0')
		return (0);
	if ((*str == DOUBLE_QUOTES || *str == SINGLE_QUOTE) && (str + 1))
		return (ft_strchr(str + 1, *str) - str + 1);
	if (*str == '$')
	{
		grab = ft_grab_var_name(str);
		res = ft_strlen(grab) + 1;
		free(grab);
		return (res);
	}
	return (ft_strlen(new_str));
}

static char	*ft_grab_next_str(t_data *data, char *str)
{
	char	*grab;
	char	*res;

	grab = NULL;
	res = NULL;
	if (str && ft_isquote(*str) && (str + 1))
	{
		res = ft_grab_next_quotes(data, str);
		if (!res)
			return (ft_strdup("\0"));
	}
	else if (str && *str == '$' && (str + 1))
	{
		grab = ft_grab_var_name(str);
		res = ft_get_expand(data, grab, str);
		free(grab);
	}
	else
		res = ft_grab_str(str, " \t\n\r\v\f$\'\"");
	return (res);
}


static int	ft_count_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SQUOTE || str[i] == DQUOTE)
			count++;
		i++;
	}
	return (count);
}

char	*ft_remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		quotes;

	i = 0;
	quotes = ft_count_quotes(str);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - quotes + 1));
	if (!new_str)
		return (NULL);
	while (str && *str)
	{
		if (*str != SQUOTE && *str != DQUOTE)
		{
			new_str[i] = *str;
			i++;
		}
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_grab_str(char *str, char *limset)
{
	char	*grab;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && ft_strchr(limset, str[i]) == NULL)
		i++;
	if (i == 0)
		return (NULL);
	grab = ft_substr(str, 0, i);
	return (grab);
}

char	*ft_grab_var_name(char *str)
{
	int		i;
	char	*var_name;

	if (!str || *str != '$')
		return (NULL);
	str++;
	if (str && *str == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(*str))
		return (ft_substr(str, 0, 1));
	i = 0;
	while (str[i] && ft_is_in_var(str[i]))
		i++;
	if (i == 0)
		return (NULL);
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

char	*ft_get_expand(t_data *data, char *var_name, char *str)
{
	char	*var_content;

	if (var_name == NULL)
	{
		if (ft_is_in_var(*(str + 1)) == NO && ft_isquote(*(str + 1)) == NO)
			return (ft_strdup("$"));
		return (NULL);
	}
	if (*var_name == '?')
		return (ft_itoa(data->exit_status));
	var_content = ft_getenv(data->env_list, var_name);
	if (!var_content)
		return (NULL);
	return (var_content);
}



static char	*ft_get_next_str_in_double_quotes(t_data *data, char *str)
{
	char	*var_name;
	char	*new_str;
	char	*toadd;
	char	*tmp;

	new_str = NULL;
	toadd = NULL;
	while (str != NULL && *str != '\0')
	{
		if (str && *str == '$')
		{
			var_name = ft_grab_var_name(str);
			toadd = ft_get_expand(data, var_name, str);
			str += ft_strlen(var_name) + 1;
			free(var_name);
		}
		else
		{
			toadd = ft_grab_str(str, "$\"");
			str += ft_strlen(toadd);
		}
		tmp = ft_super_strjoin(new_str, toadd);
		new_str = tmp;
	}
	return (new_str);
}

char	*ft_grab_next_quotes(t_data *data, char *str)
{
	char	*grab;
	char	*res;

	grab = NULL;
	res = NULL;
	if (str && *str == SINGLE_QUOTE && (str + 1))
		res = ft_grab_str(str + 1, "\'");
	else if (str && *str == DOUBLE_QUOTES && (str + 1))
	{
		grab = ft_grab_str(str + 1, "\"");
		res = ft_get_next_str_in_double_quotes(data, grab);
		free(grab);
	}
	else
		return (NULL);
	return (res);
}
