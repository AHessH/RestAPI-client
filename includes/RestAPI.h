#ifndef REST_API_H
# define REST_API_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <arpa/inet.h>

typedef enum	e_meth
{
	systemInfo	=		0,
	method1		=		1,
	method2		=		2
}				t_methods;

typedef struct	s_request
{
	int			id;
	char		jsonrpc_ver[10];
	t_methods	method;
	char		params[10][100];
	char		path[100];
}				request;

#endif