# Nom de l'exécutable
EXEC = main

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -std=c17

# Fichiers sources
SRCS = track_03.c mtrack_03.c

# Règle par défaut
all: $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(EXEC)

.PHONY: all clean