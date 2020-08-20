SRC =	srcs/establ_connect.c \
		srcs/ft_split.c \
		srcs/ft_strtrim.c \
		srcs/request_parse.c

client:
	gcc -I includes $(SRC) client.c -o client

server:
	gcc -I includes server.c -o server

run:
	./client POST http://localhost:1516/api/json/v2 -d '{"id":0, "jsonrpc":"2.0","method":"systemInfo","params":["Hello","","world"]}'
