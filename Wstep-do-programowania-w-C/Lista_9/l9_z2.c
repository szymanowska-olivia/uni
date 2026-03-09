/*Mamy otwarty i pełny klub oraz kolejkę przed klubem. Jeśli w klubie jest jeszcze miejsce, kolejne pełnoletnie osoby z kolejki są wpuszczane. Jeśli ktoś nie jest pełnoletni i byłaby jego kolej na wejście do klubu, opuszcza kolejkę. W czasie (na wejściu) następują kolejne zdarzenia:

+ <imię> <wiek> - do kolejki przychodzi osoba o imieniu <imię> i wieku <wiek>,
- <imię> - osoba o imieniu <imię> opuszcza kolejkę,
O X - X osób opuszcza klub,
F <imię> <wiek> <imię_kolegi> - do kolejki przychodzi osoba o imieniu <imię> i wieku <wiek>, która koleguje się z <imię_kolegi>, więc osoba o imieniu <imię_kolegi> wpuści ją przed siebie (załóż, że kolega zawsze jest w kolejce),
Z - klub się zamyka.
Każda osoba ma unikatowe imię składające się z dużych i małych liter oraz cyfr. Długość imienia nie przekracza 1000 znaków. Wiek osób jest liczbą nie większą od 40.

Możesz założyć, że na wejściu pojawi się nie więcej niż 10100 linii.

Wszystkie znaki na wejściu są z ASCII.

Zadanie: Wypisz imiona w kolejności w jakiej zostały wpuszczone do klubu

Wejście
Wejście składa się z linii postaci opisanej wyżej. Ostatnia linia wejścia zawiera pojedynczą literę Z.

Wyjście
Wyjście powinno składać się z tylu linii, ile osób wpuszczono do klubu przed zamknięciem. Każda linia wyjścia zawiera imię osoby.

Uwaga: To zadanie ma limit pamięci 5 MB.
Przykłady:
A
Wejście

+ Adam 20
+ Ola 23
+ Max 19
F Ala 24 Ola
+ Kamil 17
+ Iga 20
O 3
- Max
F Piotr 18 Kamil
O 2
+ Igor 30
Z

Wyjście:

Adam
Ala
Ola
Piotr
Iga

Wyjaśnienie:
Na początku w kolejce są Adam, Ola i Max. Potem za Adamem pojawia się Ala, a na końcu kolejki Kamil i Iga. Adam, Ala i Ola wchodzą do klubu, Max opuszcza kolejkę, a przed Kamilem pojawia się Piotr. Piotr i Iga wchodzą do klubu (Kamil ma urodziny jutro i stoi w kolejce bez szans na wejście. Gdy jest pierwszy, opuszcza kolejkę). Do kolejki dołącza Igor, ale klub się zamyka.

B
Wejście:

+ A 19
+ B 17
F c 20 B
- B
O 1
Z

Wyjście:

A

C
Wejście:

Z

Wyjście:



D
Wejście:

O 3
+ Adam 20
+ Bob 17
+ Cara 19
Z

Wyjście:

Adam
Cara*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Element {
    char nazwa[101]; 
    int wiek;
    struct Element* następny;
};

struct Element* klub = NULL;

void dodajElement(struct Element** head, const char* nazwa, int wiek) {
    if (wiek > 40) return;

    struct Element* nowy = (struct Element*)malloc(sizeof(struct Element));
    if (!nowy) return;

    strncpy(nowy->nazwa, nazwa, 100);
    nowy->nazwa[100] = '\0';  
    nowy->wiek = wiek;
    nowy->następny = NULL;

    if (*head == NULL) {
        *head = nowy;
    } else {
        struct Element* tmp = *head;
        while (tmp->następny != NULL) {
            tmp = tmp->następny;
        }
        tmp->następny = nowy;
    }
}

void dodajDoKlubu(struct Element** head, const char* nazwa, int wiek) {
    struct Element* nowy = (struct Element*)malloc(sizeof(struct Element));
    if (!nowy) return;

    strncpy(nowy->nazwa, nazwa, 100);
    nowy->nazwa[100] = '\0';
    nowy->wiek = wiek;
    nowy->następny = NULL;

    if (*head == NULL) {
        *head = nowy;
    } else {
        struct Element* tmp = *head;
        while (tmp->następny != NULL) {
            tmp = tmp->następny;
        }
        tmp->następny = nowy;
    }
}

void wpuść(struct Element** head, int* licznik) {
    struct Element* tmp = *head;
    struct Element* prev = NULL;

    while (tmp != NULL && *licznik > 0) {
        if (tmp->wiek >= 18) {
            dodajDoKlubu(&klub, tmp->nazwa, tmp->wiek);

            struct Element* toDelete = tmp;
            if (prev == NULL) {
                *head = tmp->następny;
                tmp = *head;
            } else {
                prev->następny = tmp->następny;
                tmp = prev->następny;
            }
            free(toDelete);
            (*licznik)--;
        } else {
            prev = tmp;
            tmp = tmp->następny;
        }
    }
}

void usuńElement(struct Element** head, const char* nazwa) {
    struct Element* tmp = *head;
    struct Element* prev = NULL;

    while (tmp != NULL) {
        if (strcmp(tmp->nazwa, nazwa) == 0) {
            if (prev == NULL) {
                *head = tmp->następny;
            } else {
                prev->następny = tmp->następny;
            }
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->następny;
    }
}

void dodajPrzed(struct Element** head, const char* nazwa, int wiek, const char* cel) {
    if (wiek > 40) return;

    struct Element* nowy = (struct Element*)malloc(sizeof(struct Element));
    if (!nowy) return;

    strncpy(nowy->nazwa, nazwa, 100);
    nowy->nazwa[100] = '\0';
    nowy->wiek = wiek;

    struct Element* tmp = *head;
    struct Element* prev = NULL;

    while (tmp != NULL) {
        if (strcmp(tmp->nazwa, cel) == 0) {
            nowy->następny = tmp;
            if (prev == NULL) {
                *head = nowy;
            } else {
                prev->następny = nowy;
            }
            return;
        }
        prev = tmp;
        tmp = tmp->następny;
    }
    free(nowy);
}

void wypiszListę(struct Element* head) {
    struct Element* tmp = head;
    while (tmp != NULL) {
        printf("%s\n", tmp->nazwa);
        tmp = tmp->następny;
    }
}

void zwolnijListę(struct Element* head) {
    struct Element* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->następny;
        free(tmp);
    }
}

int main() {
    struct Element* kolejka = NULL;
    char cmd[1024];
    char nazwa[101], cel[101];
    int wiek, licznik = 0;

    while (scanf("%1023s", cmd) != EOF) {
        if (cmd[0] == '+') {
            scanf("%s %d", nazwa, &wiek);
            dodajElement(&kolejka, nazwa, wiek);
        } else if (cmd[0] == '-') {
            scanf("%s", nazwa);
            usuńElement(&kolejka, nazwa);
        } else if (cmd[0] == 'O') {
            scanf("%d", &licznik);
            wpuść(&kolejka, &licznik);
        } else if (cmd[0] == 'F') {
            scanf("%s %d %s", nazwa, &wiek, cel);
            dodajPrzed(&kolejka, nazwa, wiek, cel);
        } else if (cmd[0] == 'Z') {
            break;
        }
    }

    wypiszListę(klub);

    zwolnijListę(kolejka);
    zwolnijListę(klub);

    return 0;
}
