CC ?= gcc

CFLAGS = -Wall -Wextra -g

COBJS ?= client.o
SOBJS ?= serveur.o
ROBJS ?= repertoire.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client
REPERTOIRE = repertoire

all: $(SERVER) $(CLIENT) $(REPERTOIRE)

$(SERVER): $(SOBJS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(COBJS)

$(REPERTOIRE): $(ROBJS)
	$(CC) $(CFLAGS) -o $(REPERTOIRE) $(ROBJS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f $(SERVER) $(CLIENT) $(REPERTOIRE) *.o

