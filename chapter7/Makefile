
.PHONY:all
all:file_server file_clent

file_server:file_server.c
	gcc $^ -o $@

file_clent:file_clent.c
	gcc $^ -o $@


.PHONY:clean
clean:
	rm file_clent file_server
