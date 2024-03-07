#include <stdio.h>
#include <string.h>

void AdaugaV(){ /*Functia pentru adaugare de venituri*/
    printf("Adauga Venit");
}

void AdaugaC(){ /*Functia pentru adaugare de cheltuieli*/
    printf("Adauga Cheltuieli");
}

void ArataComenzi(){ /*Functia pentru a afisa lista de comenzi*/
    printf("         MENIU         \n1. Adaugati venituri - 'AV'\n2. Adaugati cheltuieli - 'AC'\n");
}

int main(int argc, char *argv[]){
    if(argc == 1){
        ArataComenzi();
    }
    if(strcmp(argv[1], "/help") == 0){
        ArataComenzi();
    }
    if(strcmp(argv[1], "AV") == 0){
        AdaugaV();
    }
    if(strcmp(argv[1], "AC") == 0){
        AdaugaC();
    }
    if((strcmp(argv[1], "AC") != 0) && (strcmp(argv[1], "AV") != 0) && (strcmp(argv[1], "/help") != 0)){
        printf("Comanda nu se afla in lista. Foloseste comanda '/help' pentru a vedea lista de comenzi posibile.");
    }
    return 0;
}