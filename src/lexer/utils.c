
char	*ft_strndup(char *str, int n)
{
	char	*copy;
    int     i;

	i = 0;
	while (str[i])
		i++;
    if (i == 0)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (copy == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] && i < n)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}