#define  _DEFAULT_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include <unistd.h>
#include <pwd.h>
#include <linux/limits.h>
#include <bits/local_lim.h>
#define RED "\x1B[31m"
#define RESET "\x1B[0m"

// Liste chainée (symbolise les blocs mémoire)

typedef struct cell{
    void* data; //  Contient adresse de la cellule
    size_t size; // taille cellule 
    bool boolean; // état cellule
    struct cell *suiv;
} Cellule, *Liste;

typedef struct table {
    Liste list_ptrs; // Cellule contenant les pointeurs alloués
    int nb_mallocs; // nombre de mallocs faits
    int nb_frees_succeed;
    int nb_frees_failed;
    int mem_used;
    int mem_freed;
    int nb_frees;

} Table_register;

static Table_register table;
bool flag = false;

void clean_Table(void) {
    //Nettoyage table
    Liste temp = table.list_ptrs;
    while (temp != NULL) {
        Liste to_free = temp;
        if(to_free->boolean){
            free(to_free->data);
        }
        temp = temp->suiv;
    }
    table.list_ptrs = NULL;
    table.nb_mallocs = 0;
    table.mem_freed = 0;
    table.mem_used = 0;
    table.nb_frees = 0;
    table.nb_frees_failed = 0;
    table.nb_frees_succeed = 0;
}

void show_begin_track(void){
    fprintf(stderr,"– (libmtrack) activation automatique > stderr – \n");
    fprintf(stderr,"-------------------\n");
    time_t date_now = time(NULL);
    struct tm *local = localtime(&date_now);
    fprintf(stderr,"DATE : %02d/%02d/%04d %02d:%02d:%02d\n",
           local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
           local->tm_hour, local->tm_min, local->tm_sec);
    // Obtenir le nom de l'utilisateur
    struct passwd *pw = getpwuid(getuid());
    const char *user = pw->pw_name;

    // Obtenir le nom de l'hôte
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, sizeof(hostname));

    // Obtenir le répertoire de travail
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    fprintf(stderr,"USER : %s\n", user);
    fprintf(stderr,"HOST : %s\n", hostname);
    fprintf(stderr,"DIR : %s\n", cwd);
    fprintf(stderr,"-------------------\n");

}



void show_track(void){
    double ratio;
    fprintf(stderr,"-------------------\n");
    fprintf(stderr, "BILAN FINAL \n");
    fprintf(stderr,"total mémoire allouée  : %d octets\n",table.mem_used);
    fprintf(stderr,"total mémoire libérée  : %d octets\n",table.mem_freed);
    if (table.mem_used > 0) {
        ratio = ((double)table.mem_freed / table.mem_used) * 100;
        fprintf(stderr, "Ratio mémoire libérée/mémoire allouée : %d%%\n", (int)ratio);
    } else {
        fprintf(stderr, RED"Ratio mémoire libérée/mémoire allouée : N/A (aucune mémoire allouée)" RESET "\n");
    }
    fprintf(stderr, "<malloc> : %d appel \n",table.nb_mallocs);
    fprintf(stderr, RED "<free> : %d appel correct \n       : %d appel incorrect " RESET "\n",table.nb_frees_succeed,table.nb_frees_failed);
    fprintf(stderr,"-------------------\n");

}

void end_track(void){
    show_track();
    clean_Table();
}

void initialize_tracing() {
    if (!flag) {
        flag = true;
        show_begin_track();
        if (atexit(end_track) != 0) {
            fprintf(stderr, "Erreur lors de l'enregistrement de end_track avec atexit\n");
            exit(EXIT_FAILURE);
        }
    }
}

// Cellule contenant les données d'une allocation
// A terme, ce sera une liste contenant les données de gestion
// de
Cellule* create_cell(void* data,size_t size_type,bool state){
    Cellule* new_cell = malloc(sizeof(Cellule));
    if (!new_cell){
        fprintf(stderr,"Erreur d'allocation de mémoire");
    }

    new_cell->data = data;
    new_cell->size = size_type;
    new_cell->boolean = state;
    new_cell->suiv = NULL;
    return new_cell;

}

void add_to_list(Cellule* new_cell){
        if (!new_cell) return;
        new_cell->suiv = table.list_ptrs;
        table.list_ptrs = new_cell;
}

Table_register create_data_mem(void){
    //Table_register new_table;
    table.list_ptrs = NULL;
    table.nb_mallocs = 0;
    table.mem_freed = 0;
    table.mem_used = 0;
    table.nb_frees = 0;
    table.nb_frees_failed = 0;
    table.nb_frees_succeed = 0;
    return table;

}

void *my_malloc(const char* file,const char* func, int line,size_t size_type) {
    if (!flag) {
      initialize_tracing();
    }
    if (size_type <= 0) {
        fprintf(stderr, "Erreur taille d'allocation nulle ou négative\n");
        return NULL;
    }
    void* ptr = malloc(size_type);
    if (!ptr) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        return NULL;
    } else {
        Cellule* new_cell = create_cell(ptr, size_type,true);
        add_to_list(new_cell);
        table.nb_mallocs++;
        fprintf(stderr, "in file<%s> function <%s> line <%d> - (call#%d) - malloc(%ld) -> %p\n",file,func,line,table.nb_mallocs,size_type, ptr);
        table.mem_used += size_type;
        return ptr;
    }
}

void my_free(const char* file,const char* func, int line,void* ptr) {
    if (!flag) {
      initialize_tracing();
    }
    if (!ptr) return;
    Liste temp = table.list_ptrs;
    while (temp) {
        if (temp->data == ptr) {
            if (temp->boolean == true) {
                temp->boolean = false;
                table.nb_frees_succeed++;
                table.mem_freed += temp->size;
                fprintf(stderr, "in file<%s> function <%s> line <%d> - (call#%d) - free(%p)\n", file,func,line,table.nb_frees_succeed, ptr);
                free(ptr);
            } else {
                table.nb_frees_failed++;
                fprintf(stderr, RED "in file<%s> function <%s> line <%d> - (call#%d) - free(%p) - Erreur : adresse déjà libérée" RESET "\n",file,func,line,table.nb_frees_failed, ptr);
            }
            table.nb_frees++;
            return;
        }
        temp = temp->suiv;
    }

    // Si le pointeur n'a pas été trouvé dans la liste
    table.nb_frees_failed++;
    table.nb_frees++;
    fprintf(stderr, RED "in file<%s> function <%s> line <%d> - (call#%d) - free(%p) - Erreur : adresse non trouvée" RESET "\n",file,func,line,table.nb_frees_failed, ptr);
}


