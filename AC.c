#include <stdio.h>
#include <string.h>
#include <Windows.h>

typedef struct Venit{
    int suma;
    char moneda[5];
    char sursa[31];
    char data[12];
    char categorie[31];
}Venit;

typedef struct Cheltuiala{
    int suma;
    char moneda[5];
    char destinatar[31];
    char data[12];
    char categorie[31];
}Cheltuiala;

void AdaugaV(){ /*Functia pentru adaugare de venituri*/
    FILE *vin, *v;
    Venit citire;
    char nume_doc[20];
    char linie[80], *i;
    printf("Introduceti numele documentului de unde se vor prelua datele: ");
    scanf("%s", nume_doc);
    vin = fopen(nume_doc, "r");
    v = fopen("Venituri.txt", "a");
    while(!feof(vin)){
        fscanf(vin, "%d", &citire.suma);
        fgets(linie, 80, vin);
        strcpy(linie+strlen(linie)-1, "\0");
        i = strtok(linie, ",");
        strcpy(citire.moneda, i);
        i = strtok(NULL, ",");
        strcpy(citire.sursa, i);
        i = strtok(NULL, ",");
        strcpy(citire.data, i);
        i = strtok(NULL, ",");
        strcpy(citire.categorie, i);
        fprintf(v, "%d%s,%s,%s,%s\n", citire.suma, citire.moneda, citire.sursa, citire.data, citire.categorie);
    }
    fclose(vin);
    fclose(v);
}

void AdaugaC(){ /*Functia pentru adaugare de cheltuieli*/
    FILE *cin, *c;
    Venit citire;
    char nume_doc[20];
    char linie[80], *i;
    printf("Introduceti numele documentului de unde se vor prelua datele: ");
    scanf("%s", nume_doc);
    cin = fopen(nume_doc, "r");
    c = fopen("Venituri.txt", "a");
    while(!feof(cin)){
        fscanf(cin, "%d", &citire.suma);
        fgets(linie, 80, cin);
        strcpy(linie+strlen(linie)-1, "\0");
        i = strtok(linie, ",");
        strcpy(citire.moneda, i);
        i = strtok(NULL, ",");
        strcpy(citire.sursa, i);
        i = strtok(NULL, ",");
        strcpy(citire.data, i);
        i = strtok(NULL, ",");
        strcpy(citire.categorie, i);
        fprintf(c, "%d%s,%s,%s,%s\n", citire.suma, citire.moneda, citire.sursa, citire.data, citire.categorie);
    }
    fclose(cin);
    fclose(c);
}

void AfiseazaV(){ /*Functia pentru afisarea veniturilor*/
    FILE *v;
    char linie[80];
    v = fopen("Venituri.txt", "r");
    while(!feof(v)){
        fgets(linie, 80, v);
        if(!feof(v)){
            printf("%s", linie);
        }
    }
}

void AfiseazaC(){ /*Functia pentru afisarea cheltuielilor*/
    FILE *c;
    char linie[80];
    c = fopen("Venituri.txt", "r");
    while(!feof(c)){
        fgets(linie, 80, c);
        if(!feof(c)){
            printf("%s", linie);
        }
    }
}

void ArataComenzi(){ /*Functia pentru a afisa lista de comenzi*/
    printf("1. Adaugati venituri - 'AV' (Admin only)\n2. Adaugati cheltuieli - 'AC'(Admin only)\n3. Afiseaza venituri - 'AFV'\n4. Afiseaza cheltuieli - 'AFC'");
}

int este_admin(){ /*Functia pentru a determina daca utilizatorul are dreptul de a folosi optiunea aleasa*/
    return 1;
}

int main(int argc, char *argv[]){
    if(argc == 1){
        ArataComenzi();
    }
    else{
        if(strcmp(argv[1], "-help") == 0){
            ArataComenzi();
        }
        if(strcmp(argv[1], "AV") == 0){
            if(este_admin()){
                AdaugaV();
            }
        }
        if(strcmp(argv[1], "AC") == 0){
            if(este_admin()){
                AdaugaC();
            }
        }
        if(strcmp(argv[1], "AFV") == 0){
            AfiseazaV();
        }
        if(strcmp(argv[1], "AFC") == 0){
            AfiseazaC();
        }
        if((strcmp(argv[1], "AC") != 0) && (strcmp(argv[1], "AV") != 0) && (strcmp(argv[1], "-help") != 0) && (strcmp(argv[1], "AFV") != 0) && (strcmp(argv[1], "AFC") != 0)){
            printf("Comanda nu se afla in lista. Foloseste comanda '-help' pentru a vedea lista de comenzi posibile.");
        }
    }
    return 0;
}
