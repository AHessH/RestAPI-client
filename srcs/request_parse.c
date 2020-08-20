#include "RestAPI_client.h"

static char *remove_chars(char *src, char *set)
{
	char *result;
	int size;
	int i;
	int j;
	int k;

	size = 0;
	i = 0;
	while (src[i])
	{
		j = 0;
		while (set[j] && set[j] != src[i])
			j++;
		if (j == strlen(set))
			size++;
		i++;
	}
	if (!(result = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	k = 0;
	while (src[i])
	{
		j = 0;
		while (set[j] && set[j] != src[i])
			j++;
		if (j == strlen(set))
			result[k++] = src[i];
		i++;
	}
	result[k] = 0;
	return (result);
}

static void	str_parse(char *str, request *data)
{
	char *tmp;
	int i;
	int k;
	int j;

	i = 0;
	if (!strncmp(str, "id", 2))
	{
		while (*str++ != ':')
			;
		data->id = atoi(str);
	}
	else if (!strncmp(str, "method", 6))
	{
		while (*str++ != ':')
			;
		if (!strncmp(str, "method1", strlen(str)))
			data->method = method1;
		else if (!strncmp(str, "method2", strlen(str)))
			data->method = method2;
		else if (!strncmp(str, "systemInfo", strlen(str)))
			data->method = systemInfo;
		else
		{
			printf("Error: Unknown method - %s\n", str);
			exit(EXIT_FAILURE);
		}
	}
	else if (!strncmp(str, "params", 6))
	{
		while (*str++ != ':')
			;
		if (!(tmp = remove_chars(str, "[]")))
		{
			printf("Error: Malloc error\n");
			exit (EXIT_FAILURE);
		}
		i = 0;
		k = 0;
		while (tmp[k])
		{
			j = 0;
			while (tmp[k] && tmp[k] != ',')
			{
				data->params[i][j] = tmp[k];
				k++;
				j++;
			}
			data->params[i][j] = 0;
			if (tmp[k] && tmp[k] == ',')
				k++;
			i++;
		}
		free(tmp);
	}
	else if (!strncmp(str, "jsonrpc", 7))
	{
		while (*str && *str++ != ':')
			;
		strcpy(data->jsonrpc_ver, str);
		data->jsonrpc_ver[strlen(str)] = 0;
	}
	else
	{
		printf("Error: Unknown data - %s\n", str);
		exit(EXIT_FAILURE);
	}
}

request	*request_parse(char *str)
{
	request *one_req;
	char *one_str_par;
	char **param;

	if (!(one_req = (request *)malloc(sizeof(request))))
		return (NULL);
	if (!(one_str_par = remove_chars(str, "{\"} ")))
	{
		printf("Error: Malloc error\n");
		exit (EXIT_FAILURE);
	}
	param = ft_split(one_str_par, ',');
	free(one_str_par);
	for (int i = 0; param[i] != NULL; i++)
	{
		str_parse(param[i], one_req);
		free(param[i]);
	}
	free(param);
	return (one_req);
}