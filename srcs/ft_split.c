#include "RestAPI_client.h"

static char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char				*substr;
	unsigned int		i;
	size_t				str_len;

	if (!str)
		return (0);
	i = 0;
	str_len = (size_t)strlen(str);
	if (start > str_len || !len)
		return (strdup(""));
	while (i < len && str[i + start])
		i++;
	if (!(substr = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = -1;
	while (++i < len && str[i + start])
		substr[i] = str[start + i];
	substr[i] = 0;
	return (substr);
}

static int		ft_str_count(char const *s, char c)
{
	int		count;
	int		except;

	count = 0;
	except = 0;
	while (1)
	{
		while (*s == c && *s)
			s++;
		if (!(*s))
			return (count);
		count++;
		while ((*s != c || except) && *s)
		{
			if (*s == '[')
				except = 1;
			else if (*s == ']')
				except = 0;
			s++;
		}
	}
	return (count);
}

static char		**ft_split_clear(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static int		word_len(const char *s, char c)
{
	int		len;
	int		except;

	except = 0;
	len = 0;
	while (*s)
	{
		if (*s == '[')
			except = 1;
		else if (*s == ']')
			except = 0;
		if (!except && *s == c)
			break ;
		s++;
		len++;
	}
	return (len);
}

char			**ft_split(char const *s, char c)
{
	int		tab_count;
	size_t	i;
	char	**tab;

	if (!s)
		return (0);
	tab_count = ft_str_count(s, c);
	if (!(tab = (char**)malloc(sizeof(s) * (tab_count + 1))))
		return (0);
	i = 0;
	while (tab_count)
	{
		while (*s && *s == c)
			s++;
		if (!(tab[i++] = ft_substr(s, 0, word_len(s, c))))
			return (ft_split_clear(tab));
		s += word_len(s, c);
		tab_count--;
	}
	tab[i] = 0;
	return (tab);
}
