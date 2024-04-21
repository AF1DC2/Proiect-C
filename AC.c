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

void red(){ /*Seteaza culoarea output-ului in rosu*/
    printf("\033[1;31m");
}

void green(){ /*Seteaza culoarea output-ului in verde*/
    printf("\033[1;32m");
}

void reset (){ /*Reseteaza culoarea output-ului la cea default*/
    printf("\033[0m");
}

int verifica_lista_argumente(char argv[]){ /*Verifica daca argumentul introdus este o optiune din meniu*/
    char lista_argumente[][12]={"AC", "AV", "-help", "AFV", "AFC", "AU", "APD", "APC", "CDC", "CDD"};
    for(int i = 0; i < 10; ++i){
        if(strcmp(lista_argumente[i], argv) == 0){
            return 1;
        }
    }
    return 0;
}

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

int Log(){ /*Functia pentru acces la optiunile din meniu*/
    FILE *a, *u;
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
        a = fopen("A-Credentials.txt", "r");
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
        u = fopen("U-Credentials.txt", "r");
        while(!feof(u)){
            fgets(Vnume, 30, u);
            fgets(Vparola, 20, u);
            strcpy(Vnume + strlen(Vnume) -1, "\0");
            strcpy(Vparola + strlen(Vparola) - 1, "\0");
            decrypt(Vparola);
            if((strcmp(Vnume, nume) == 0) && (strcmp(Vparola, parola) == 0)){
                system("cls");
                return 1;
            }
        }
        system("cls");
        red();
        printf("Numele utilizatorului sau parola sunt gresite!\n");
        reset();
        fclose(a);
        fclose(u);
    }while(1);
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
            red();
            printf("Nivelul de acces introdus nu exista!\n");
            reset();
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
    green();
    printf("\nContul a fost adaugat cu succes!\n");
    reset();
    fclose(a);
    fclose(u);
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
            red();
            printf("Documentul introdus nu exista!\n");
            reset();
        }
    }while(vin == NULL);
    v = fopen("Venituri.txt", "a");
    while(!feof(vin)){
        fscanf(vin, "%d", &citire.suma);
        fgets(linie, 80, vin);
        printf("%s.\n", linie);
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
    system("cls");
    green();
    printf("Datele au fost introduse cu succes!\n");
    reset();
    fclose(vin);
    fclose(v);
}

void AdaugaC(){ /*Functia pentru adaugare de cheltuieli*/
    FILE *cin, *c;
    Venit citire;
    char nume_doc[20];
    char linie[80], *i;
    do{
        printf("Introduceti numele documentului de unde se vor prelua datele: ");
        scanf("%s", nume_doc);
        cin = fopen(nume_doc, "r");
        if(cin == NULL){
            system("cls");
            red();
            printf("Documentul introdus nu exista!\n");
            reset();
        }
    }while(cin == NULL);
    cin = fopen(nume_doc, "r");
    c = fopen("Cheltuieli.txt", "a");
    while(!feof(cin)){
        fscanf(cin, "%d", &citire.suma);
        fgets(linie, 80, cin);
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
    system("cls");
    green();
    printf("Datele au fost introduse cu succes!\n");
    reset();
    fclose(cin);
    fclose(c);
}

void AfiseazaV(){ /*Functia pentru afisarea veniturilor*/
    FILE *v;
    char linie[80];
    v = fopen("Venituri.txt", "r");
    if(v == NULL){
        red();
        printf("Nu exista venituri!");
        reset();
    }
    else{
        while(!feof(v)){
            fgets(linie, 80, v);
            if(!feof(v)){
                printf("%s", linie);
            }
        }
    }
    fclose(v);
}

void AfiseazaC(){ /*Functia pentru afisarea cheltuielilor*/
    FILE *c;
    char linie[80];
    c = fopen("Cheltuieli.txt", "r");
    if(c == NULL){
        red();
        printf("Nu exista cheltuieli!");
        reset();
    }
    else{
        while(!feof(c)){
            fgets(linie, 80, c);
            if(!feof(c)){
                printf("%s", linie);
            }
        }
    }
    fclose(c);
}

int data_corecta(char *data){ /*Functia pentru a determina corectitudinea argumentului data*/
    int k = 0;
    char *copie;
    copie = malloc(strlen(data)*sizeof(char)+1);
    strcpy(copie, data);
    char *p;
    p = strtok(copie, ".");
    while(p != NULL){
        k++;
        if(k == 1 && strlen(p) != 2){
            return 1;
        }
        if(k == 2 && strlen(p) != 2){
            return 1;
        }
        if(k == 3 && strlen(p) != 4){
            return 1;
        }
        p = strtok(NULL, ".");
    }
    if(k != 3){
        return 1;
    }
    free(p);
    free(copie);
    return 0;
}

void AfisarePD(int argc, char *argv[]){ /*Functia de afisare a intrarilor dintr o anumita data*/
    if(argc != 4){
        red();
        printf("Nu ati introdus numarul potrivit de argumente pentru optiunea selectata!\
              \nFolositi -help pentru ajutor.");
        reset();
    }
    else{
        if((strcmp(argv[2], "C") != 0) && (strcmp(argv[2], "V") != 0) && (strcmp(argv[2], "A") != 0)){
            red();
            printf("Tipul selectat pentru iesiri nu exista!\
                  \nFolositi -help pentru ajutor.");
            reset();
        }
        else{
            if(data_corecta(argv[3])){
                red();
                printf("Formatul datei nu este corect!\
                     \nFolositi -help pentru ajutor.");
                reset();
            }
            else{
                char linie[100];
                if(strcmp(argv[2], "C") == 0){
                    int k = 0;
                    FILE *c;
                    c = fopen("Cheltuieli.txt", "r");
                    while(!feof(c)){
                        fgets(linie, 100, c);
                        if(!feof(c)){
                            if(strstr(linie, argv[3]) != NULL){
                                k++;
                                printf("%s", linie);
                            }
                        }
                    }
                    if(k == 0){
                        printf("Nu exista cheltuieli inregistrate in %s", argv[3]);
                    }
                    fclose(c);
                }
                if(strcmp(argv[2], "V") == 0){
                    int k = 0;
                    FILE *v;
                    v = fopen("Venituri.txt", "r");
                    while(!feof(v)){
                        fgets(linie, 100, v);
                        if(!feof(v)){
                            if(strstr(linie, argv[3]) != NULL){
                                k++;
                                printf("%s", linie);
                            }
                        }
                    }
                    if(k == 0){
                        printf("Nu exista venituri inregistrate in %s", argv[3]);
                    }
                    fclose(v);
                }
                if(strcmp(argv[2], "A") == 0){
                    int k = 0;
                    FILE *c, *v;
                    c = fopen("Cheltuieli.txt", "r");
                    v = fopen("Venituri.txt", "r");
                    while(!feof(v)){
                        fgets(linie, 100, v);
                        if(!feof(v)){
                            if(strstr(linie, argv[3]) != NULL){
                                k++;
                                printf("+%s", linie);
                            }
                        }
                    }
                    while(!feof(c)){
                        fgets(linie, 100, c);
                        if(!feof(c)){
                            if(strstr(linie, argv[3]) != NULL){
                                k++;
                                printf("-%s", linie);
                            }
                        }
                    }
                    if(k == 0){
                        printf("Nu exista venituri sau cheltuieli inregistrate in %s", argv[3]);
                    }
                    fclose(c);
                    fclose(v);
                }
            }
        }
    }
}

void AfisarePC(int argc, char *argv[]){ /*Functia de afisare a intrarilor dintr o anumita categorie*/
    if(argc != 3){
        red();
        printf("Nu ati introdus numarul potrivit de argumente pentru optiunea selectata!\
              \nFolositi -help pentru ajutor.");
        reset();
    }
    else{
        if((strcmp(argv[2], "C") != 0) && (strcmp(argv[2], "V") != 0) && (strcmp(argv[2], "A") != 0)){
            red();
            printf("Tipul selectat pentru iesiri nu exista!\
                  \nFolositi -help pentru ajutor.");
            reset();
        }
        else{
            char linie[100];
            char categorie[30];
            printf("Introduceti categoria pe care o cautati: ");
            getchar();
            fgets(categorie, 30, stdin);
            strcpy(categorie+strlen(categorie)-1, "\0");
            if(strcmp(argv[2], "C") == 0){
                int k = 0;
                FILE *c;
                c = fopen("Cheltuieli.txt", "r");
                while(!feof(c)){
                    fgets(linie, 100, c);
                    if(!feof(c)){
                        if(strstr(linie, categorie) != NULL){
                            k++;
                            printf("%s", linie);
                        }
                    }
                }
                if(k == 0){
                    printf("Nu exista cheltuieli inregistrate sub categoria '%s'", categorie);
                }
                fclose(c);
            }
            if(strcmp(argv[2], "V") == 0){
                int k = 0;
                FILE *v;
                v = fopen("Venituri.txt", "r");
                while(!feof(v)){
                    fgets(linie, 100, v);
                    if(!feof(v)){
                        if(strstr(linie, categorie) != NULL){
                            k++;
                            printf("%s", linie);
                        }
                    }
                }
                if(k == 0){
                    printf("Nu exista venituri inregistrate sub categoria '%s'", categorie);
                }
                fclose(v);
            }
            if(strcmp(argv[2], "A") == 0){
                int k = 0;
                FILE *c, *v;
                c = fopen("Cheltuieli.txt", "r");
                v = fopen("Venituri.txt", "r");
                while(!feof(v)){
                    fgets(linie, 100, v);
                    if(!feof(v)){
                        if(strstr(linie, categorie) != NULL){
                            k++;
                            printf("+%s", linie);
                        }
                    }
                }
                while(!feof(c)){
                    fgets(linie, 100, c);
                    if(!feof(c)){
                        if(strstr(linie, categorie) != NULL){
                            k++;
                            printf("-%s", linie);
                        }
                    }
                }
                if(k == 0){
                    printf("Nu exista venituri sau cheltuieli inregistrate sub categoria %s", categorie);
                }
                fclose(c);
                fclose(v);
            }
        }
    }
}


void CreareDD(int argc, char *argv[]){ /*Functia de creare a unui document nou cu intrarile dintr o anumita data*/
    if(argc != 4){
        red();
        printf("Nu ati introdus numarul potrivit de argumente pentru optiunea selectata!\
              \nFolositi -help pentru ajutor.");
        reset();
    }
    else{
        if((strcmp(argv[2], "C") != 0) && (strcmp(argv[2], "V") != 0) && (strcmp(argv[2], "A") != 0)){
            red();
            printf("Tipul selectat pentru iesiri nu exista!\
                  \nFolositi -help pentru ajutor.");
            reset();
        }
        else{
            if(data_corecta(argv[3])){
                red();
                printf("Formatul datei nu este corect!\
                     \nFolositi -help pentru ajutor.");
                reset();
            }
            else{
                FILE *out;
                char nume_doc[34];
                char linie[100];
                printf("Introduceti numele documentului generat(fara extensie si spatii): ");
                getchar();
                fgets(nume_doc, 30, stdin);
                strcpy(nume_doc+strlen(nume_doc)-1, ".txt\0");
                out = fopen(nume_doc, "w");
                if(strcmp(argv[2], "C") == 0){
                    int k = 0;
                    FILE *c;
                    c = fopen("Cheltuieli.txt", "r");
                    while(!feof(c)){
                        fgets(linie, 100, c);
                        if(!feof(c)){
                            if(strstr(linie, argv[3]) != NULL){
                                k++;
                                fprintf(out, "%s", linie);
                            }
                        }
                    }
                    if(k == 0){
                        printf("Nu exista cheltuieli inregistrate in %s\n", argv[3]);
                        red();
                        printf("Documentul este gol!");
                        reset();
                    }
                    else{
                        green();
                        printf("Documentul a fost creat cu succes!");
                        reset();
                    }
                    fclose(c);
                }
                if(strcmp(argv[2], "V") == 0){
                    int k = 0;
                    FILE *v;
                    v = fopen("Venituri.txt", "r");
                    while(!feof(v)){
                        fgets(linie, 100, v);
                        if(!feof(v)){
                            if(strstr(linie, argv[3]) != NULL){
                                k++;
                                fprintf(out, "%s", linie);
                            }
                        }
                    }
                    if(k == 0){
                        printf("Nu exista venituri inregistrate in %s\n", argv[3]);
                        red();
                        printf("Documentul este gol!");
                        reset();
                    }
                    else{
                        green();
                        printf("Documentul a fost creat cu succes!");
                        reset();
                    }
                    fclose(v);
                }
                if(strcmp(argv[2], "A") == 0){
                    int k = 0;
                    FILE *c, *v;
                    c = fopen("Cheltuieli.txt", "r");
                    v = fopen("Venituri.txt", "r");
                    while(!feof(v)){
                        fgets(linie, 100, v);
                        if(!feof(v)){
                            if(strstr(linie, argv[3]) != NULL){
                                k++;
                                fprintf(out, "+%s", linie);
                            }
                        }
                    }
                    while(!feof(c)){
                        fgets(linie, 100, c);
                        if(!feof(c)){
                            if(strstr(linie, argv[3]) != NULL){
                                k++;
                                fprintf(out, "-%s", linie);
                            }
                        }
                    }
                    if(k == 0){
                        printf("Nu exista venituri sau cheltuieli inregistrate in %s\n", argv[3]);
                        red();
                        printf("Documentul este gol!");
                        reset();
                    }
                    else{
                        green();
                        printf("Documentul a fost creat cu succes!");
                        reset();
                    }
                    fclose(c);
                    fclose(v);
                }
                fclose(out);
            }
        }
    }
}

void CreareDC(int argc, char *argv[]){ /*Functia de creare a ununi document nou cu intrarile dintr o anumita categorie*/
    if(argc != 3){
        red();
        printf("Nu ati introdus numarul potrivit de argumente pentru optiunea selectata!\
              \nFolositi -help pentru ajutor.");
        reset();
    }
    else{
        if((strcmp(argv[2], "C") != 0) && (strcmp(argv[2], "V") != 0) && (strcmp(argv[2], "A") != 0)){
            red();
            printf("Tipul selectat pentru iesiri nu exista!\
                  \nFolositi -help pentru ajutor.");
            reset();
        }
        else{
            FILE *out;
            char nume_doc[34];
            char linie[100];
            char categorie[30];
            printf("Introduceti numele documentului generat(fara extensie si spatii): ");
            getchar();
            fgets(nume_doc, 30, stdin);
            strcpy(nume_doc+strlen(nume_doc)-1, ".txt\0");
            out = fopen(nume_doc, "w");
            printf("Introduceti categoria pe care o cautati: ");
            fgets(categorie, 30, stdin);
            strcpy(categorie+strlen(categorie)-1, "\0");
            if(strcmp(argv[2], "C") == 0){
                int k = 0;
                FILE *c;
                c = fopen("Cheltuieli.txt", "r");
                while(!feof(c)){
                    fgets(linie, 100, c);
                    if(!feof(c)){
                        if(strstr(linie, categorie) != NULL){
                            k++;
                            fprintf(out, "%s", linie);
                        }
                    }
                }
                if(k == 0){
                    printf("Nu exista cheltuieli inregistrate sub categoria %s\n", categorie);
                    red();
                    printf("Documentul este gol!");
                    reset();
                }
                else{
                    green();
                    printf("Documentul a fost creat cu succes!");
                    reset();
                }
                fclose(c);
            }
            if(strcmp(argv[2], "V") == 0){
                int k = 0;
                FILE *v;
                v = fopen("Venituri.txt", "r");
                while(!feof(v)){
                    fgets(linie, 100, v);
                    if(!feof(v)){
                        if(strstr(linie, argv[3]) != NULL){
                            k++;
                            fprintf(out, "%s", linie);
                        }
                    }
                }
                if(k == 0){
                    printf("Nu exista venituri inregistrate sub categoria %s\n", categorie);
                    red();
                    printf("Documentul este gol!");
                    reset();
                }
                else{
                    green();
                    printf("Documentul a fost creat cu succes!");
                    reset();
                }
                fclose(v);
            }
            if(strcmp(argv[2], "A") == 0){
                int k = 0;
                FILE *c, *v;
                c = fopen("Cheltuieli.txt", "r");
                v = fopen("Venituri.txt", "r");
                while(!feof(v)){
                    fgets(linie, 100, v);
                    if(!feof(v)){
                        if(strstr(linie, categorie) != NULL){
                            k++;
                            fprintf(out, "+%s", linie);
                        }
                    }
                }
                while(!feof(c)){
                    fgets(linie, 100, c);
                    if(!feof(c)){
                        if(strstr(linie, categorie) != NULL){
                            k++;
                            fprintf(out, "-%s", linie);
                        }
                    }
                }
                if(k == 0){
                    printf("Nu exista venituri sau cheltuieli inregistrate sub categoria %s\n", categorie);
                    red();
                    printf("Documentul este gol!");
                    reset();
                }
                else{
                    green();
                    printf("Documentul a fost creat cu succes!");
                    reset();
                }
                fclose(c);
                fclose(v);
            }
            fclose(out);
        }
    }
}

void ArataComenzi(){ /*Functia pentru a afisa lista de comenzi*/
    printf("1. Afiseaza venituri - 'AFV'\
          \n2. Afiseaza cheltuieli - 'AFC'\
          \n3. Afisare preferentiala dupa data - 'APD', Tip iesiri(C-cheltuieli / V-venituri / A-ambele), Data(format - zi.luna.an)\
          \n4. Afisare preferentiala dupa categorie - 'APC', Tip iesiri(C-cheltuieli / V-venituri / A-ambele)\
          \n5. Adaugati venituri - 'AV'                                                                                                \033[1;31m | \033[0m\
          \n6. Adaugati cheltuieli - 'AC'                                                                                               |\
          \n7. Creare document iesiri dupa data- 'CDD', Tip iesiri(C-cheltuieli / V-venituri / A-ambele), Data(format - zi.luna.an)     |\033[1;31m (Admin only) \033[0m\
          \n8. Creare document iesiri dupa categorie- 'CDC', Tip iesiri(C-cheltuieli / V-venituri / A-ambele)                           |\
          \n9. Adauga utilizator - 'AU'                                                                                                 |");
}

int main(int argc, char *argv[]){
    if(argc == 1){
        ArataComenzi();
    }
    else{
        if(!verifica_lista_argumente(argv[1])){
            red();
            printf("Comanda nu se afla in lista. Foloseste comanda '-help' pentru a vedea lista de comenzi posibile.");
            reset();
        }
        else{
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
                        red();
                        printf("Nu aveti acces la aceasta optiune. Contactati un admin!");
                        reset();
                    }
                }
                if(strcmp(argv[1], "AC") == 0){
                    if(Nivel_acces == 2){
                        AdaugaC();
                    }
                    else{
                        red();
                        printf("Nu aveti acces la aceasta optiune. Contactati un admin!");
                        reset();
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
                        red();
                        printf("Nu aveti acces la aceasta optiune. Contactati un admin!");
                        reset();
                    }
                }
                if(strcmp(argv[1], "APD") == 0){
                    AfisarePD(argc, argv);
                }
                if(strcmp(argv[1], "APC") == 0){
                    AfisarePC(argc, argv);
                }
                if(strcmp(argv[1], "CDD") == 0){
                    if(Nivel_acces == 2){
                        CreareDD(argc, argv);
                    }
                    else{
                        red();
                        printf("Nu aveti acces la aceasta optiune. Contactati un admin!");
                        reset();
                    }
                }
                if(strcmp(argv[1], "CDC") == 0){
                    if(Nivel_acces == 2){
                        CreareDC(argc, argv);
                    }
                    else{
                        red();
                        printf("Nu aveti acces la aceasta optiune. Contactati un admin!");
                        reset();
                    }
                }
            }
        }
    }
    return 0;
}
