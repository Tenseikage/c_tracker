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



// Cellule contenant les données d'une allocation
// A terme, ce sera une liste contenant les données de gestion
// de
Cellule* create_cell(void* data,size_t size_type,int size,bool state){
    Cellule* new_cell = malloc(sizeof(Cellule));
    if (!new_cell){
        fprintf(stderr,"Erreur d'allocation de mémoire");
    }

    new_cell->data = data;
    new_cell->size = size * size_type;
    new_cell->boolean = state;
    new_cell->suiv = NULL;
    return new_cell;

}

void add_to_list(Cellule* new_cell){
        if (!new_cell) return;
        new_cell->suiv = table.list_ptrs;
        table.list_ptrs = new_cell;
}


void my_malloc(int size, size_t size_type){
    if (size <= 0){
        fprintf(stderr,"Erreur taille d'allocation nulle ou négative \n ");
        return;
    }
    void* ptr = malloc(size * size_type);
    if (!ptr){
        fprintf(stderr,"Erreur d'allocation de mémoire\n");
        return;
    } else {
        //Cellule* new_cell = create_cell(ptr,size_type,size,true);
        Liste temp = table.list_ptrs;
        if (!temp){
            Cellule* new_cell = create_cell(ptr,size_type,size,true);
            add_to_list(new_cell);
            //printf("oui1\n");
            table.nb_mallocs++;
            fprintf(stdout,"(%d) malloc(%ld)-> %p \n",table.nb_mallocs,size * size_type,ptr);
            table.mem_used += size * size_type;
            return;
        } else {
            while(temp){
                if ((temp->data == ptr) && (temp->boolean == false)){
                    temp->boolean = true;
                    temp->size = size * size_type;
                    table.mem_used += size * size_type;
                    return; // Adresse déja existante dans la table
                } 
                temp = temp->suiv;
            } 
            Cellule* new_cell = create_cell(ptr,size_type,size,true);
            add_to_list(new_cell);
            table.nb_mallocs++;
            fprintf(stdout,"(%d) malloc(%ld)-> %p\n",table.nb_mallocs, size * size_type, ptr);
            table.mem_used += size * size_type;
            return;
                
        }
       
    }
    return;
}

void my_free(void* ptr){
    if(!ptr) return;
    Liste temp = table.list_ptrs;
    while (temp){
        if ((temp->data == ptr) && (temp->boolean == true)){
            temp->boolean = false;
            free(ptr);
            table.nb_frees_succeed++;
            table.nb_frees++;
            table.mem_freed += temp->size;
            fprintf(stdout,"(%d) free(%p) \n",table.nb_frees,ptr);


        } else if ((temp->data == ptr) && (temp->boolean == false)){
            table.nb_frees_failed++;
             table.nb_frees++;
            fprintf(stdout,"(%d) free(%p)  - Erreur : adresse illégale -> ignoré\n",table.nb_frees,ptr);

        }
        temp = temp->suiv;
    }
    

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


void test_allocation_and_free() {
    // Initialize the memory tracking table

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
    
    show_track();
}

void clean_Table(){
    
}


int main(int argc, char const *argv[])
{
    test_allocation_and_free();
    return 0;
}



