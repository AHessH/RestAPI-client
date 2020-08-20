#include "RestAPI.h"

int	main(void)
{
	request data;
	int as;
	int	ms;
	struct sockaddr_in serv;

	as = socket(AF_INET, SOCK_STREAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(1516);

	bind(as, (struct sockaddr *)&serv, sizeof(serv));
	listen(as, 5);
	while (1)
	{
		ms = accept(as, 0, 0);
		read(ms, &data, sizeof(request));
		close(ms);
		printf("id = %d\njsonrpc_ver = %s\nmethod = %d\npath = %s\n\n", data.id, data.jsonrpc_ver, data.method, data.path);
		printf("params:\n%s\n%s\n", data.params[0], data.params[1]);
	}
	close(as);
	return (0);
}