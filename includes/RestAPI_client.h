#ifndef REST_API_CLIENT_H
# define REST_API_CLIENT_H

#include "RestAPI.h"

typedef struct	s_addrinfo
{
	char 		*domain_name;
	char 		*port;
	char 		*path;
}				t_addrinfo;

char			**ft_split(char const *s, char c);
request			*request_parse(char *params);
char			*ft_strtrim(char const *s1, char const *set);
int				estable_connect(char *domain_name, char *port);


#endif