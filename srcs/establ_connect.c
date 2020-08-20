#include "RestAPI_client.h"

int		estable_connect(char *domain_name, char *port)
{
	int sock_fd;
	struct sockaddr_in serv;
	struct hostent *ip;

	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("\nError: Could not create socket");
		exit(EXIT_FAILURE);
	}
	ip = gethostbyname(domain_name);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(atoi(port));
	bcopy(ip->h_addr, &serv.sin_addr, ip->h_length);
	if (connect(sock_fd, (struct sockaddr *)&serv, sizeof(serv)) == -1)
	{
		perror("\nError: Unable to connect to server");
		exit (EXIT_FAILURE);
	}
	return (sock_fd);
}