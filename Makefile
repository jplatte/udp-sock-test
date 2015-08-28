all: server client

server: server.c
client: client.c

CFLAGS=-D_DEFAULT_SOURCE -std=c99 -Wall -Wextra
