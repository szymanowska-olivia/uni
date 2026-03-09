/*Napisz program, który na podstawie wyników wyborów w poszczególnych okręgach odtworzy podział mandatów zgodnie z ordynacją wyborczą do Sejmu RP.

Program powinien ze standardowego wejścia czytać dane takie, jak w załączonych plikach. W pierwszym wierszu znajdują się "nagłówki kolumn", czyli kolejno słowa "okreg", "mandatow" (które właściwie można zignorować, są tu dla czytelności) oraz (skrótowe) nazwy komitetów wyborczych. Każdy z pozostałych wierszy zawiera informacje o wynikach wyborów w danym okręgu wyborczym i zawiera kolejno nazwę tego okręgu (w przygotowanych plikach są one liczbowe, ale nie zakładaj, że tak będzie zawsze, zresztą w tym zadaniu je też można zignorować), liczbę mandatów sejmowych do podziału w tym okręgu, oraz liczby głosów oddanych w tym okręgu na kolejne komitety wymienione w nagłówku. Brak głosów może być podany zarówno jako zero, jak i pusty napis; inne pola nie mogą być puste. Sąsiednie pola oddzielone są średnikami, a wejście należy czytać do końca (czyli najlepiej testować program przekierowując na nie któryś z plików, tj. wykonując ./a.out <wyniki2019.csv).

W pierwszym kroku procedury podziału mandatów należy dla każdego komitetu określić, czy w skali całego kraju przekroczył próg wyborczy 5% wszystkich oddanych głosów – pozostałe komitety są ignorowane w dalszych rozważaniach. Następnie w każdym okręgu rozważa się zbiór tzw. ilorazów – wyników dzielenia liczb głosów oddanych na poszczególne komitety przez kolejne liczby naturalne (od 1). n mandatów przypadających na dany okręg dostają te komitety, których ilorazy są wśród n największych. Ewentualne remisy rozstrzygane są na korzyść komitetu, który dostał w danym okręgu więcej głosów (załóż, że dalszych remisów nie będzie). Tę część zrealizuj sortując przy użyciu qsort z stdlib.h (z odpowiednim komparatorem) tablicę rekordów zawierających wszystkie potrzebne informacje (np. iloraz i całkowitą liczbę głosów) oraz indeks komitetu, któremu odpowiada ten iloraz. Liczby mandatów uzyskane przez poszczególne komitety we wszystkich okręgach program ma wysumować i czytelnie wydrukować (pomijając komitety, które nie uzyskały mandatów).

Program powinien kończyć wykonanie drukując informację o błędzie, kiedy dane okażą się niepoprawne, np. gdy jest za mało kolumn (musi być co najmniej jeden komitet), gdy w dalszych wierszach jest inna liczba kolumn (tj. średników) niż w wierszu nagłówkowym, lub gdy nazwy komitetów powtarzają się.

Dodatkowo zaimplementuj obsługę następujących opcji wywołania:

--minority, po której następuje nazwa komitetu – oznacza to, że dany komitet reprezentuje mniejszość etniczną i nie obowiązuje go próg wyborczy (przykładowo, żeby odtworzyć faktyczne rezultaty wyborów w 2019 roku, będzie należało użyć opcji --minority MN);
--alliance, po której następuje ciąg nazw komitetów oddzielonych średnikami, i która ma dwa efekty:
wymienione komitety traktowane są w obliczeniach (oraz końcowych wynikach) jako jeden, a liczby otrzymanych przez nie głosów sumują się;
komitet taki obowiązuje wyższy próg wyborczy 8% (i dlatego może być sensowne użycie tej opcji dla pojedynczego komitetu, np. odtworzenie faktycznych rezultatów wyborów w 2015 roku wymagałoby użycia opcji --alliance ZL);
--sainte-lague (bezargumentowa), z którą ilorazy otrzymuje się dzieląc przez kolejne liczby nieparzyste (a nie wszystkie naturalne).
Również dla dowolnych bezsensownych (zestawów) opcji wywołania program powinien kończyć wykonanie drukując informacje o błędzie, np. gdy opcja --sainte-lague powtarza się (pozostałe mogą występować wielokrotnie), lub w argumentach pozostałych opcji pojawiają się komitety powtórzone bądź nieistniejące.

Przemyśl organizację kodu, w tym podział na funkcje i ew. wydzielenie modułu/-ów.

Ze względu na specjalne znaczenie średnika w terminalu argument opcji --alliance będzie należało np. podawać w cudzysłowie (który będzie przetwarzany przez terminal i "zniknie" przed pojawieniem się napisu w programie), np. --alliance "KWIN;BS".

Pliki załączone są w dwóch wersjach z różnymi standardami końca linii – wybierz właściwy dla Twojego systemu operacyjnego. Możliwe, że wkradły się w nie jakieś błędy formatowania – jeśli na nie natrafisz, daj znać wykładowcy.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COMMITTEES 50
#define MAX_REGIONS 100
#define MAX_NAME_LEN 100

// Struktury danych do przechowywania informacji o komitetach i okręgach
typedef struct {
    char name[MAX_NAME_LEN];
    int total_mandates;
    int is_minority;
    int is_alliance;
    double threshold;
} Committee;

typedef struct {
    char region_name[MAX_NAME_LEN];
    int mandates;
    long long votes[MAX_COMMITTEES];
    int allocated_mandates[MAX_COMMITTEES];
} Region;

// Globalne zmienne
Committee committees[MAX_COMMITTEES];
Region regions[MAX_REGIONS];
int num_committees = 0;
int num_regions = 0;
int sainte_lague = 0;

double national_threshold = 0.05;

// Funkcje pomocnicze
void error_exit(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

int find_committee(const char *name) {
    for (int i = 0; i < num_committees; i++) {
        if (strcmp(committees[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

char *allocate_string(const char *str) {
    size_t len = strlen(str) + 1; // +1 dla znaku null
    char *copy = malloc(len);
    if (!copy) {
        error_exit("Memory allocation error.");
    }
    memcpy(copy, str, len);
    return copy;
}

void trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

void parse_options(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--sainte-lague") == 0) {
            if (sainte_lague) {
                error_exit("Option --sainte-lague specified multiple times.");
            }
            sainte_lague = 1;
        } else if (strcmp(argv[i], "--minority") == 0) {
            if (i + 1 >= argc) {
                error_exit("Option --minority requires an argument.");
            }
            int idx = find_committee(argv[++i]);
            if (idx == -1) {
                error_exit("Invalid committee name in --minority.");
            }
            committees[idx].is_minority = 1;
        } else if (strcmp(argv[i], "--alliance") == 0) {
            if (i + 1 >= argc) {
                error_exit("Option --alliance requires an argument.");
            }
            char *alliance_arg = allocate_string(argv[++i]);
            if (!alliance_arg) {
                error_exit("Memory allocation error.");
            }
            char *token = strtok(alliance_arg, ";");
            int found_any = 0;
            while (token != NULL) {
                trim_whitespace(token);
                int idx = find_committee(token);
                if (idx == -1) {
                    fprintf(stderr, "Debug: Invalid committee name '%s' in --alliance.\n", token);
                    free(alliance_arg);
                    error_exit("Invalid committee name in --alliance.");
                }
                committees[idx].is_alliance = 1;
                committees[idx].threshold = 0.08;
                found_any = 1;
                token = strtok(NULL, ";");
            }
            free(alliance_arg);
            if (!found_any) {
                error_exit("No valid committee names in --alliance.");
            }
        } else {
            error_exit("Unknown option.");
        }
    }
}

void parse_input() {
    char line[1024];
    if (!fgets(line, sizeof(line), stdin)) {
        error_exit("Failed to read header line.");
    }

    char *token = strtok(line, ";");
    if (!token || strcmp(token, "okreg") != 0) {
        error_exit("Invalid header format.");
    }
    
    token = strtok(NULL, ";"); // "mandatow"
    if (!token || strcmp(token, "mandatow") != 0) {
        error_exit("Invalid header format.");
    }

    // Parsowanie nazw komitetów
    while ((token = strtok(NULL, ";")) != NULL) {
        trim_whitespace(token);
        if (find_committee(token) != -1) {
            error_exit("Duplicate committee name in header.");
        }
        strcpy(committees[num_committees++].name, token);
    }

    // Parsowanie danych z regionów
    while (fgets(line, sizeof(line), stdin)) {
        token = strtok(line, ";");
        if (!token) {
            error_exit("Invalid region data.");
        }
        strcpy(regions[num_regions].region_name, token);

        token = strtok(NULL, ";");
        if (!token) {
            error_exit("Invalid region data.");
        }
        regions[num_regions].mandates = atoi(token);

        for (int i = 0; i < num_committees; i++) {
            token = strtok(NULL, ";");
            if (!token || *token == '\n' || *token == '\0') {
                regions[num_regions].votes[i] = 0;
            } else {
                regions[num_regions].votes[i] = atoll(token);
            }
            regions[num_regions].allocated_mandates[i] = 0;
        }

        num_regions++;
    }
}

void calculate_results() {
    long long total_votes = 0;
    for (int i = 0; i < num_regions; i++) {
        for (int j = 0; j < num_committees; j++) {
            total_votes += regions[i].votes[j];
        }
    }

    for (int i = 0; i < num_committees; i++) {
        if (!committees[i].is_minority && !committees[i].is_alliance) {
            committees[i].threshold = national_threshold;
        }
    }

    // Wykluczenie komitetów poniżej progu wyborczego
    for (int i = 0; i < num_committees; i++) {
        long long committee_votes = 0;
        for (int j = 0; j < num_regions; j++) {
            committee_votes += regions[j].votes[i];
        }
        if ((double)committee_votes / total_votes < committees[i].threshold) {
            committees[i].total_mandates = 0;
        }
    }

    // Podział mandatów w okręgach
    for (int i = 0; i < num_regions; i++) {
        int mandates_left = regions[i].mandates;
        double quotients[MAX_COMMITTEES] = {0};

        while (mandates_left > 0) {
            int max_index = -1;
            double max_value = -1.0;

            for (int j = 0; j < num_committees; j++) {
                if (regions[i].votes[j] == 0) {
                    continue;
                }

                int divisor = sainte_lague ? (2 * regions[i].allocated_mandates[j] + 1) : (regions[i].allocated_mandates[j] + 1);
                quotients[j] = (double)regions[i].votes[j] / divisor;

                if (quotients[j] > max_value) {
                    max_value = quotients[j];
                    max_index = j;
                }
            }

            if (max_index != -1) {
                regions[i].allocated_mandates[max_index]++;
                mandates_left--;
            }
        }

        for (int j = 0; j < num_committees; j++) {
            committees[j].total_mandates += regions[i].allocated_mandates[j];
        }
    }
}

int main(int argc, char *argv[]) {
    parse_options(argc, argv);
    parse_input();
    calculate_results();

    // Wypisanie wyników
    printf("Wyniki podziału mandatów:\n");
    for (int i = 0; i < num_committees; i++) {
        if (committees[i].total_mandates > 0) {
            printf("%s: %d\n", committees[i].name, committees[i].total_mandates);
        }
    }
    return 0;
}
