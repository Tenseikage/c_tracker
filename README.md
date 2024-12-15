# Traceur d'allocation de mémoire
Auteur : Christophe TARATIBU

<p style="font-size: 18px;">
Dans le but de simplifier la visualisation de l'utilisation de la mémoire dans un projet quelconque codé dans le langage C, un traceur minimal à été crée pour répondre à ce besoin. Voici des étapes pour utiliser le traceur.
</p>

## I. Installation

<p style="font-size: 18px;">
Dans le dossier contenant le code du traceur, un makefile vous permettera d'installer le traceur sur votre machine. Veillez à exécuter la commande ```make``` pour créer la librairie partagée:
</p>

```
~/dir/c_tracker  make (dir : dossier ou se trouver le dossier c_tracker -> l'ouvrir dans le terminal)

```
<p style="font-size: 18px;">
La commande à faire pour l'installation:
</p>

```
~/dir/c_tracker  make install (dir : dossier ou se trouver le dossier c_tracker -> l'ouvrir dans le terminal)

```
<p style="font-size: 18px;">
Ainsi le traceur se trouvera dans usr/lib et le header dans usr/include.
Si vous souhaitez désinstaller le traceur :
</p>

```
~/dir/c_tracker  make uninstall (dir : dossier ou se trouver le dossier c_tracker -> l'ouvrir dans le terminal)

```
<p style="font-size: 18px;">
Les fichiers relatifs aux traceur seront supprimés sans problème.
</p>

## II. Compilation

<p style="font-size: 18px;">
Afin de pouvoir utiliser pleinement le traceur voici les directives de compilation à utiliser:
</p>

```
// Dossier où sont situés la librairie partagée et le header avec les directives de liaison du traceur au projet
// Extrait d'un makefile qui utilise le traceur
TRACKPATH := ./usr/
LFLAGS := -Wl,-rpath,$(TRACKPATH)lib -L$(TRACKPATH)lib -ltrack

```
<p style="font-size: 18px;">
La variable LDFLAGS doit être ajoutée dans la directive de compilation qui crée l'exécutable final qui du projet.
</p>

```
// $(OBJS) =  fichiers .o générés dans le projet (par le makefile).
// Ajout de la variable LFLAGS dans la directive de compilation

TARGET := executable

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) $(IPATH) -o $(TARGET) 
```
Ceci garantit la bonne compilation du projet avec l'intégration du code du traceur

## III. Exécution

<p style="font-size: 18px;">
En ce qui concerne l'exécution du logiciel, le header du traceur memtrack_05.h doit être inclus dans tout fichier source contenant les fonctions d'allocation et libération suivantes : (mallloc,calloc, realloc, free). Le traceur lui récupère le nombre de fois, que les fonctions sont utilisées, le quantité de mémoire utilisée et libérée avec gestion d'erreur (double free, free illégal) et enfin le ratio mémoire utilisé/libéré. Tout cela est affiché à la fin de l'exécution du programme/ projet qui utilise le traceur.

Voici un extrait de l'utilisation du traceur sur un fichier de test
</p>

```
-------------------
in file<src/track_04.c> function <main> line <3> - (call#1) - malloc(1) -> 0x5a284cb83300
in file<src/track_04.c> function <main> line <4> - (call#2) - malloc(1) -> 0x5a284cb833c0
in file<src/track_04.c> function <main> line <5> - (call#1) - calloc(1) -> 0x5a284cb83480
in file<src/track_04.c> function <main> line <6> - (call#1) - realloc(1) -> 0x5a284cb83300
in file<src/track_04.c> function <main> line <7> - (call#1) - free(0x5a284cb83300)
in file<src/track_04.c> function <main> line <9> - (call#1) - free(0x5a284cb833c1) - Erreur : adresse non trouvée
in file<src/track_04.c> function <main> line <10> - (call#2) - free(0x5a284cb83480)
-------------------
BILAN FINAL 
total mémoire allouée  : 4 octets
total mémoire libérée  : 3 octets
Ratio mémoire libérée/mémoire allouée : 75%
<malloc> : 2 appel(s) 
<calloc> : 1 appel(s) 
<realloc> : 1 appel(s) 
<free> : 2 appel(s) correct(s) 
       : 1 appel(s) incorrect(s) 
-------------------
```

## IV. Tests

<p style="font-size: 18px;">
Pour les tests du traceur, un dossier tests se trouve dans le dossier du traceur. Dedans 4 tests simples s'y trouvent.
Voici la suite de commande à faire pour les exécuter :

</p>

```
~/dir/c_tracker/test  make (dir : dossier ou se trouver le dossier c_tracker -> l'ouvrir dans le terminal)
~/dir/c_tracker/test ./testX (avec X compris entre 1 et 4)

```

<p style="font-size: 20px;">
Merci d'utiliser ce traceur :)!!!
</p>










