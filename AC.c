#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Venit{
    int suma;
    char moneda[5];
    char sursa[31];
    char data[12];
    char categorie[31];
}Venit;

void crypt(char *a){ /*Functia pentru a aplica cifrul lui cezar pe o parola*/
    for(int i = 0; i < strlen(a); ++i){
        a[i] = a[i] + 1;
    }
}

void decrypt(char *a){ /*Functia pentru a decripta o parola din memorie*/
    for(int i = 0; i < strlen(a); ++i){
        a[i] = a[i] - 1;
    }
}

void AdaugaV(){ /*Functia pentru adaugare de venituri*/
    FILE *vin, *v;
    Venit citire;
    char nume_doc[20];
    char linie[80], *i;
    do{
        printf("Introduceti numele documentului de unde se vor prelua datele: ");
        scanf("%s", nume_doc);
        vin = fopen(nume_doc, "r");
        if(vin == NULL){
            system("cls");
            printf("Documentul introdus nu exista!\n");
        }
    }while(vin == NULL);
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
    c = fopen("Cheltuieli.txt", "a");
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
    fclose(v);
}

void AfiseazaC(){ /*Functia pentru afisarea cheltuielilor*/
    FILE *c;
    char linie[80];
    c = fopen("Cheltuieli.txt", "r");
    while(!feof(c)){
        fgets(linie, 80, c);
        if(!feof(c)){
            printf("%s", linie);
        }
    }
    fclose(c);
}

void ArataComenzi(){ /*Functia pentru a afisa lista de comenzi*/
    printf("1. Adaugati venituri - 'AV' (Admin only)\n2. Adaugati cheltuieli - 'AC' (Admin only)\n3. Afiseaza venituri - 'AFV'\n4. Afiseaza cheltuieli - 'AFC'\n5. Adauga utilizator - 'AU' (Admin only)");
}

void AddAccount(){ /*Functia pentru a adauga un nou utilizator*/
    FILE *a, *u;
    a = fopen("A-Credentials.txt", "a");
    u = fopen("U-Credentials.txt", "a");
    char nume[30];
    char parola[20];
    char Nivel_acces;
    int ok = 0;
    do{
        getchar();
        printf("Introduceti nivelul de acces al contului(a - admin sau u - utilizator): ");
        scanf("%c", &Nivel_acces);
        if(Nivel_acces == 'a' || Nivel_acces == 'u'){
            ok = 1;
        }
        else{
            system("cls");
            printf("Nivelul de acces introdus nu exista!\n");
        }
    }while(ok == 0);
    if(Nivel_acces == 'a'){
        printf("Introduceti numele de utilizator: ");
        scanf("%s", &nume);
        printf("Introduceti o parola: ");
        int i = 0; 
        char ch;
        while((ch = getch()) != '\r'){
            if(ch == 127 || ch == 8){
                if(i != 0){
                    i--;
                    printf("\b \b");
                }
            }
            else{
                parola[i++] = ch;
                printf("*");
            }
        }
        parola[i] = '\0';
        crypt(parola);
        fprintf(a, "%s\n%s\n", nume, parola);
    }
    if(Nivel_acces == 'u'){
        printf("Introduceti numele de utilizator: ");
        scanf("%s", &nume);
        printf("Introduceti o parola: ");
        int i = 0; 
        char ch;
        while((ch = getch()) != '\r'){
            if(ch == 127 || ch == 8){
                if(i != 0){
                    i--;
                    printf("\b \b");
                }
            }
            else{
                parola[i++] = ch;
                printf("*");
            }
        }
        parola[i] = '\0';
        crypt(parola);
        fprintf(u, "%s\n%s\n", nume, parola);
    }
    printf("\nContul a fost adaugat cu succes!\n");
    fclose(a);
    fclose(u);
}

int Log(){ /*Functia pentru acces la optiunile din meniu*/
    FILE *a, *u;
    a = fopen("A-Credentials.txt", "r");
    u = fopen("U-Credentials.txt", "r");
    char nume[30];
    char parola[20];
    char Vnume[30];
    char Vparola[20];
    do{
        printf("Introduceti numele utilizatorului: ");
        scanf("%s", &nume);
        printf("Introduceti parola: ");
        int i = 0; 
        char ch;
        while((ch = getch()) != '\r'){
            if(ch == 127 || ch == 8){
                if(i != 0){
                    i--;
                    printf("\b \b");
                }
            }
            else{
                parola[i++] = ch;
                printf("*");
            }
        }
        parola[i] = '\0';
        while(!feof(a)){
            fgets(Vnume, 30, a);
            fgets(Vparola, 20, a);
            strcpy(Vnume + strlen(Vnume) -1, "\0");
            strcpy(Vparola + strlen(Vparola) - 1, "\0");
            decrypt(Vparola);
            if((strcmp(Vnume, nume) == 0) && (strcmp(Vparola, parola) == 0)){
                system("cls");
                return 2;
            }
        }
        while(!feof(u)){
            fgets(Vnume, 30, u);
            fgets(Vparola, 20, u);
            strcpy(Vnume + strlen(Vnume) -1, "\0");
            strcpy(Vparola + strlen(Vparola) - 1, "\0");
            if((strcmp(Vnume, nume) == 0) && (strcmp(Vparola, parola) == 0)){
                system("cls");
                return 1;
            }
        }
        system("cls");
        printf("Numele utilizatorului sau parola sunt gresite!\n");
    }while(1);
}


int main(int argc, char *argv[]){
    if(argc == 1){
        ArataComenzi();
    }
    else{
        if((strcmp(argv[1], "AC") != 0) && (strcmp(argv[1], "AV") != 0) && (strcmp(argv[1], "-help") != 0) && (strcmp(argv[1], "AFV") != 0) && (strcmp(argv[1], "AFC") != 0) && (strcmp(argv[1], "AU") != 0)){
            printf("Comanda nu se afla in lista. Foloseste comanda '-help' pentru a vedea lista de comenzi posibile.");
        }
        if(strcmp(argv[1], "-help") == 0){
            ArataComenzi();
        }
        else{
            int Nivel_acces = Log();
            if(strcmp(argv[1], "AV") == 0){
                if(Nivel_acces == 2){
                    AdaugaV();
                }
                else{
                    printf("Nu aveti acces la aceasta optiune. Contactati un admin!");
                }
            }
            if(strcmp(argv[1], "AC") == 0){
                if(Nivel_acces == 2){
                    AdaugaC();
                }
                else{
                    printf("Nu aveti acces la aceasta optiune. Contactati un admin!");
                }
            }
            if(strcmp(argv[1], "AFV") == 0){
                AfiseazaV();
            }
            if(strcmp(argv[1], "AFC") == 0){
                AfiseazaC();
            }
            if(strcmp(argv[1], "AU") == 0){
                if(Nivel_acces == 2){
                    AddAccount();
                }
                else{
                    printf("Nu aveti acces la aceasta optiune. Contactati un admin!");
                }
            }
        }
    }
    return 0;
}
