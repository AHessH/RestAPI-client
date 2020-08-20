#include "RestAPI_client.h"

static t_addrinfo	*take_addrinfo(char *data)
{
	t_addrinfo *info;
	char *start;
	char *tmp;

	start = data;
	tmp = NULL;
	if (!(info = (t_addrinfo *)malloc(sizeof(t_addrinfo))))
		return (NULL);
	tmp = data;
	while (*data != ':')
		data++;
	*data = 0;
	info->domain_name = strdup(tmp);
	tmp = ++data;
	while (isdigit(*data))
		data++;
	*data = 0;
	data++;
	info->port = strdup(tmp);
	info->path = strdup(data);
	return (info);
}

static void	check_params(int argc, char **argv)
{
	if (argc < 4)
	{
		printf("\nError: Too many argumets\n");
		exit(EXIT_FAILURE);
	}	
	if (strncmp(argv[1], "POST", 4))
	{
		printf("\nError: Unknown parameter %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if (strncmp(argv[2], "http://", 7))
	{
		printf("\nError: Not find URL\n");
		exit(EXIT_FAILURE);
	}
	if (strncmp(argv[3], "-d", 2))
	{
		printf("\nError: Unknown parameter %s\n", argv[3]);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	char *params;
	char *address;
	int i;
	int	sock_fd;
	request *message;
	t_addrinfo *info;
	
	check_params(argc, argv);
	address = ft_strtrim(argv[2], "http://");
	info = take_addrinfo(address);
	free(address);
	sock_fd = estable_connect(info->domain_name, info->port);
	if (!(message = request_parse(argv[4])))
	{
		printf("\nError: malloc error!\n");
		exit(EXIT_FAILURE);
	}
	strcpy(message->path, info->path);
	message->path[strlen(info->path)] = 0;

	write(sock_fd, message, sizeof(request));
	
	free(message);
	free(info->domain_name);
	free(info->path);
	free(info->port);
	free(info);
	return (0);
}