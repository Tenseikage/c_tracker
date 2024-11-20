#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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



void show_track(void){
    //Liste temp = table.list_ptrs;
    //int nb_malloc = 0, nb_free = 0;
    double ratio;
    fprintf(stdout,"-------------------\n");
    fprintf(stdout, "BILAN FINAL \n");
    fprintf(stdout,"total mémoire allouée  : %d octets\n",table.mem_used);
    fprintf(stdout,"total mémoire libérée  : %d octets\n",table.mem_freed);
    if (table.mem_used > 0) {
        ratio = ((double)table.mem_freed / table.mem_used) * 100;
        fprintf(stdout, "Ratio mémoire libérée/mémoire allouée : %d%%\n", (int)ratio);
    } else {
        fprintf(stdout, "Ratio mémoire libérée/mémoire allouée : N/A (aucune mémoire allouée)\n");
    }
    fprintf(stdout, "<malloc> : %d appel \n",table.nb_mallocs);
    fprintf(stdout, "<free> : %d appel correct \n       : %d appel incorrect \n",table.nb_frees_succeed,table.nb_frees_failed);
    fprintf(stdout,"-------------------\n");

}

void end_track(void){
    show_track();
    clean_Table();
}

void initialize_tracing() {
    if (!flag) {
        flag = true;
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

void *my_malloc(size_t size_type) {
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
        fprintf(stdout, "(%d) malloc(%ld) -> %p\n", table.nb_mallocs,size_type, ptr);
        table.mem_used += size_type;
        return ptr;
    }
}

void my_free(void* ptr) {
    if (!flag) {
      initialize_tracing();
    }
    if (!ptr) return;
    Liste temp = table.list_ptrs;
    while (temp) {
        if (temp->data == ptr) {
            if (temp->boolean == true) {
                temp->boolean = false;
                free(ptr);
                table.nb_frees_succeed++;
                table.mem_freed += temp->size;
                fprintf(stdout, "(%d) free(%p)\n", table.nb_frees_succeed, ptr);
            } else {
                table.nb_frees_failed++;
                fprintf(stdout, "(%d) free(%p) - Erreur : adresse déjà libérée\n", table.nb_frees_failed, ptr);
            }
            table.nb_frees++;
            return;
        }
        temp = temp->suiv;
    }

    // Si le pointeur n'a pas été trouvé dans la liste
    table.nb_frees_failed++;
    table.nb_frees++;
    fprintf(stdout, "(%d) free(%p) - Erreur : adresse non trouvée\n", table.nb_frees_failed, ptr);
}

Table_register change_data(void){
    // Met a jour les données de la table
    Liste temp = table.list_ptrs;
    while (temp != NULL) {
        if (temp->boolean == true) {
           table.nb_mallocs++;
        }
        temp = temp->suiv;
    }
    return table;
}   






/*if(flag){
        atexit(end_track);
    }*/

/*void test_allocation_and_free() {
    // Initialize the memory tracking table
    table = create_data_mem();

    // Test 1: Allocate memory and check the tracking
    my_malloc(10, sizeof(int));
    my_malloc(20, sizeof(char));
    my_malloc(5, sizeof(double));
    //show_track();

    // Test 2: Free some of the allocated memory and check the tracking
    void* ptr1 = table.list_ptrs->data;
    void* ptr2 = table.list_ptrs->suiv->data;
    my_free(ptr1);
    my_free(ptr2);
    //show_track();

    // Test 3: Attempt to free already freed memory
    my_free(ptr1);
    
    
}

int main(int argc, char const *argv[]) {
    test_allocation_and_free();
    return 0;
}*/



