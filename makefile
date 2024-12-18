CC := gcc
CFLAGS := -std=c17 -fPIC
SRC := ./src
BUILD := ./build
SHARE := -shared
LIB := libtrack.so
PREFIX := /usr/lib
LIBS := ./lib
PREFIX_INC := /usr/include
INCLUDE := ./inc

#Création de la librairie partagée 
all: $(LIBS)/$(LIB)

$(BUILD)/mtrack.o: $(SRC)/memtrack_05.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBS)/$(LIB): $(BUILD)/mtrack.o
	$(CC) $(SHARE) $< -o $@

#755 : Lecture, écriture et exécution pour l'utilisateur (le reste peut lire et exécuter)
#644 : Lecture et écriture pour l'utilisateur (le reste peut uniquement lire)
#La librairie se situe dans usr/lib et le header dans usr/include

#installation
install: $(LIBS)/$(LIB)
	sudo install -d $(PREFIX)
	sudo install -m 755 $(LIBS)/$(LIB) $(PREFIX)
	sudo install -m 644 $(INCLUDE)/memtrack_05.h $(PREFIX_INC)
	sudo ldconfig

#Désinstallation
uninstall:
	sudo rm -f $(PREFIX)/$(LIB)
	sudo rm -f $(PREFIX_INC)/memtrack_05.h
	sudo ldconfig

clean:
	rm -f $(BUILD)/mtrack.o $(LIBS)/$(LIB)
