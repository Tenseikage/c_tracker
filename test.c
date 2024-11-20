#include<stdio.h>
#include<stdlib.h>


int main(int argc, char const *argv[])
{
    char*  mot = "é";
    //char lettre = 'é';
    //char msg[0] = {'é'};
    fprintf(stdout,"%s \n",mot);
    //fprintf(stdout,"%c \n",lettre); Erreur: char overflow
    
    return 0;
}
