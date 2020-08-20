#include "RestAPI_client.h"

static char		ft_valid_check(char const *set, char c)
{
	int		i;
	int		valid_char;

	i = 0;
	valid_char = 1;
	while (set[i])
		if (set[i++] == c)
			valid_char = 0;
	return (valid_char);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		i;
	int		first;
	char	*new_str;

	first = 0;
	if (!s1)
		return (0);
	end = strlen(s1);
	while (!ft_valid_check(set, s1[first]))
		first++;
	while (--end > first && !ft_valid_check(set, s1[end]))
		;
	if (!(new_str = (char *)malloc(sizeof(char) * (end - first + 2))))
		return (0);
	i = 0;
	while (first <= end)
		new_str[i++] = s1[first++];
	new_str[i] = 0;
	return (new_str);
}
