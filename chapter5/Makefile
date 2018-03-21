.PHONY:all
all:op_server op_client

op_server:op_server.c operate.c
	gcc -g -o $@ $^

op_client:op_client.c operate.c
	gcc -g -o $@ $^


.PHONY:clean
clean:
	rm op_server op_client
