/*Leon, Zenon i Wacek
Trzech kosmitów - Leon, Zenon i Wacek - przybyło na Ziemię. Niestety, ich statek kosmiczny uległ awarii i rozbił się w okolicach Bieszczad.
Kosmici postanowili zaszyć się w lesie, by nie wzbudzać podejrzeń. Niestety, nie posiadają oni odpowiednich umiejętności, by przetrwać w dziczy.
W związku z tym, postanowili oni wysłać wiadomości w formie ASCI ART'ów do swoich rodaków, by ci mogli ich odnaleźć i uratować.
Niestety, wiadomości zostały zakodowana w sposób, który nie jest zrozumiały dla ludzi.
Twoim zadaniem jest odkodowanie wiadomości.

Po trzech dniach intensywnych poszukiwań, udało się ustalić następujące fakty:

Finalna wiadomość została zakodowana w formacie Base64,
Używając następującej tabeli kodowania:

static const char b64_table[] = 

    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
Po zdekodowaniu wiadomości z formatu Base64, otrzymasz tablicę compressed (kodów o typie int).
Oto krótki opis kroków algorytmu dekompresji który udało się ustalić:

Maksymalna wielkość słownika to 4096 elementów.

Na początku tworzony jest słownik, w którym kody (0…255) odpowiadają początkowym łańcuchom znaków składającym się z jednego znaku.
To znaczy, że kod 32 odpowiada spacji, kod 65 odpowiada literze A, itd. Czyli elementy słownika 0..255 odpowiadają ich kodom ASCI, pozostałe są puste. Zmienna old_code przyjmuje wartość pierwszego kodu ze skompresowanej tablicy.
Odczytywany jest pierwszy kod z tablicy compressed (old_code) i wpisywany do bufora wyjściowego na podstawie słownika dict[old_code].
Następnie, dla kolejnych kodów:
Pobierany jest nowy kod new_code - kolejny element tablicy.
Jeśli new_code istnieje w słowniku, to pobierany jest zapisany tam ciąg znaków.
Jeśli nie, konstruowany jest ciąg znaków z poprzedniego łańcucha old_code rozszerzonego o pierwszy znak tego poprzedniego łańcucha.
Otrzymany ciąg (z kroku powyżej) zapisywany jest do bufora wyjściowego.
Do słownika (na pierwszej wolnej pozycji) dodawany jest nowy łańcuch, który powstaje przez połączenie ciągu przypisanego do old_code i pierwszego znaku ciągu z new_code.
Zmienna old_code przyjmuje wartość new_code i algorytm kontynuuje aż do przetworzenia wszystkich kodów.
Po zakończeniu bufor wyjściowy zawiera zdekodowany tekst, będący wynikiem dekompresji.

Przykład 1
Wejście:
IAAAACAAAABfAAAAAgEAAAABAAAEAQAABQEAAAQBAABfAAAABwEAAAIBAAADAQAACgAAACAAAAAvAAAAAQEAACAAAABcAAAABgEAAAYBAAAoAAAAXwAAACkAAAANAQAAAAEAAAMBAABcAAAACgAAAA4BAAAvAAAAXwAAABEBAABcAAAACAEAAAMBAAABAQAAAwEAAAgBAAAgAAAAfAAAABcBAAAQAQAALwAAAAoAAAAnAQAADwEAACYBAAAgAAAAJwAAAAgBAABcAAAADgEAAAIBAAAnAQAANQEAAC4BAAAEAQAAKwEAAC4BAAA2AQAANgEAACABAAAxAQAAOgEAABABAAACAQAALwAAABoBAAAgAQAANQEAAF8AAAAdAQAARQEAAHwAAAAKAQAARwEAAAABAAA9AQAAQQEAAA==

Kody pośrednie:
[32, 32, 95, 258, 256, 260, 261, 260, 95, 263, 258, 259, 10, 32, 47, 257, 32, 92, 262, 262, 40, 95, 41, 269, 256, 259, 92, 10, 270, 47, 95, 273, 92, 264, 259, 257, 259, 264, 32, 124, 279, 272, 47, 10, 295, 271, 294, 32, 39, 264, 92, 270, 258, 295, 309, 302, 260, 299, 302, 310, 310, 288, 305, 314, 272, 258, 47, 282, 288, 309, 95, 285, 325, 124, 266, 327, 256, 317, 321]

Wyjście:


Przykład 2
Wejście:
4gAAAKAAAACAAAAAAAEAAAIBAAABAQAAAwEAAOIAAACiAAAAAgEAAKMAAAAJAQAApAAAAOIAAACjAAAADAEAAA4BAAANAQAADwEAAIQAAADiAAAAoQAAAAQBAAAWAQAABgEAAAEBAAAKAAAABgEAAAgBAAARAQAADQEAAL4AAAANAQAAvwAAAB4BAAAgAQAAIwEAAKMAAAAhAQAAJQEAACQBAAAmAQAAtwAAAA0BAAATAQAABQEAABkBAAAHAQAAoAAAACIBAAAnAQAAogAAAJsAAAANAQAAvAAAACgBAAA3AQAAJwEAADkBAAAmAQAAOwEAAA0BAAAqAQAAFQEAABoBAACjAAAAHwEAAKMAAACvAAAAPQEAADgBAAA8AQAAOgEAAEYBAABJAQAAowAAAKcAAABAAQAARwEAAE4BAABKAQAATwEAAEgBAABSAQAAvwAAAE0BAAAUAQAAIQEAAKAAAAC7AAAABwEAAFEBAABbAQAANwEAAKEAAABXAQAAWQEAAKIAAAAhAQAAoQAAALUAAAAaAQAAogAAALgAAAAUAQAAhwAAABgBAAAEAQAAiQAAAAABAAA0AQAAoAAAADQBAABIAQAAbwEAAG0BAAAAAQAAbAEAAC0BAAAJAQAAYgEAAIcAAABlAQAAZwEAADkBAAAXAQAAHAEAAKMAAAAwAQAAowAAALQAAABoAQAAAAEAALkAAAANAQAApgAAACsBAAAUAQAAFwEAAH8BAAAjAQAAoQAAAHkBAAAAAQAAiAAAAAABAABZAQAAoAAAAFcBAAAmAQAAnwAAADgBAACHAQAAEAEAAKMAAAA2AQAAcQEAAJQBAAAAAQAAlgEAAC4BAAB2AQAAagEAAAABAABnAQAAXgEAADcBAABhAQAAVgEAAFoBAAAAAQAAaQEAAKEBAAB2AQAAGgEAAKwBAAAXAQAArAEAAJABAACgAAAAgQAAAI8BAAAAAQAAtAEAAK8BAACiAQAAAQEAAA==

Kody pośrednie:
[226, 160, 128, 256, 258, 257, 259, 226, 162, 258, 163, 265, 164, 226, 163, 268, 270, 269, 271, 132, 226, 161, 260, 278, 262, 257, 10, 262, 264, 273, 269, 190, 269, 191, 286, 288, 291, 163, 289, 293, 292, 294, 183, 269, 275, 261, 281, 263, 160, 290, 295, 162, 155, 269, 188, 296, 311, 295, 313, 294, 315, 269, 298, 277, 282, 163, 287, 163, 175, 317, 312, 316, 314, 326, 329, 163, 167, 320, 327, 334, 330, 335, 328, 338, 191, 333, 276, 289, 160, 187, 263, 337, 347, 311, 161, 343, 345, 162, 289, 161, 181, 282, 162, 184, 276, 135, 280, 260, 137, 256, 308, 160, 308, 328, 367, 365, 256, 364, 301, 265, 354, 135, 357, 359, 313, 279, 284, 163, 304, 163, 180, 360, 256, 185, 269, 166, 299, 276, 279, 383, 291, 161, 377, 256, 136, 256, 345, 160, 343, 294, 159, 312, 391, 272, 163, 310, 369, 404, 256, 406, 302, 374, 362, 256, 359, 350, 311, 353, 342, 346, 256, 361, 417, 374, 282, 428, 279, 428, 400, 160, 129, 399, 256, 436, 431, 418, 257]

Wyjście:


Przykład 3
Wejście:
IAAAAAABAAABAQAAAgEAAAEBAABfAAAABQEAAAoAAAADAQAACAEAACAAAAAvAAAAAQEAAFwAAAAHAQAACQEAAAQBAABcAAAABQEAAF8AAAAvAAAAXwAAAA4BAAAPAQAAJwAAAC0AAAA+AAAALQAAABsBAAA8AAAALQAAACcAAAAWAQAADwEAACgAAAAgAAAAXgAAACMBAAAgAAAAKQAAACABAAAPAQAAXAAAACAAAAAjAAAACgEAACgBAAADAQAABQEAAC8AAAAYAQAAJwAAABEBAAAVAQAADwEAAAoBAAAAAQAAXAAAADEBAAA5AQAAOAEAAC4BAAAAAQAACwEAABMBAAAgAAAAPgAAAG8AAAADAQAADQEAAAkBAAALAQAAQQEAACAAAAAoAAAAKQAAAF8AAABvAAAAXwAAAAABAAA8AAAAKgEAAEUBAAAIAQAAEQEAAC8AAABUAQAAIAAAAHwAAAAgAAAANAEAAFwAAABRAQAAIAAAADUBAAApAQAAQAEAADcBAAAMAQAAWQEAAF8AAABcAAAAKAAAAF4BAABGAQAAAgEAACoBAAACAQAAKQAAAGMBAAATAQAAPQEAADgBAAACAQAARwEAAD4BAABpAQAAUgEAAA8BAAA+AAAAYgEAAHgBAAAMAQAAdQEAAAABAAAFAQAAXQEAAHIBAABhAQAAYgEAAH0BAABZAQAAewEAACIBAACDAQAAEgEAAAUBAAA0AQAAEgEAAC8AAABHAQAAbAEAAIMBAAAoAQAANAEAAGAAAAASAQAAhQEAACYBAACKAQAAMAEAAGkBAAA3AAAA

Kody pośrednie:
[32, 256, 257, 258, 257, 95, 261, 10, 259, 264, 32, 47, 257, 92, 263, 265, 260, 92, 261, 95, 47, 95, 270, 271, 39, 45, 62, 45, 283, 60, 45, 39, 278, 271, 40, 32, 94, 291, 32, 41, 288, 271, 92, 32, 35, 266, 296, 259, 261, 47, 280, 39, 273, 277, 271, 266, 256, 92, 305, 313, 312, 302, 256, 267, 275, 32, 62, 111, 259, 269, 265, 267, 321, 32, 40, 41, 95, 111, 95, 256, 60, 298, 325, 264, 273, 47, 340, 32, 124, 32, 308, 92, 337, 32, 309, 297, 320, 311, 268, 345, 95, 92, 40, 350, 326, 258, 298, 258, 41, 355, 275, 317, 312, 258, 327, 318, 361, 338, 271, 62, 354, 376, 268, 373, 256, 261, 349, 370, 353, 354, 381, 345, 379, 290, 387, 274, 261, 308, 274, 47, 327, 364, 387, 296, 308, 96, 274, 389, 294, 394, 304, 361, 55]

Wyjście:


Największy zakodowany obrazek: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_DICT_SIZE 4096

// Dekodowanie Base64
int base64_decode(const char *input, unsigned char **output) {
    static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t input_len = strlen(input);
    size_t output_len = input_len * 3 / 4;

    if (input_len % 4 != 0) return -1;

    *output = malloc(output_len);
    if (*output == NULL) return -1;

    size_t i, j = 0;
    uint32_t temp;
    for (i = 0; i < input_len; i += 4) {
        char *c1 = strchr(base64_table, input[i]);
        char *c2 = strchr(base64_table, input[i + 1]);
        char *c3 = (input[i + 2] == '=') ? NULL : strchr(base64_table, input[i + 2]);
        char *c4 = (input[i + 3] == '=') ? NULL : strchr(base64_table, input[i + 3]);

        if (!c1 || !c2 || (!c3 && input[i + 2] != '=') || (!c4 && input[i + 3] != '=')) {
            free(*output);
            return -1;
        }

        temp = (c1 - base64_table) << 18;
        temp |= (c2 - base64_table) << 12;
        temp |= c3 ? (c3 - base64_table) << 6 : 0;
        temp |= c4 ? (c4 - base64_table) : 0;

        (*output)[j++] = (temp >> 16) & 0xFF;
        if (c3) (*output)[j++] = (temp >> 8) & 0xFF;
        if (c4) (*output)[j++] = temp & 0xFF;
    }
    return j;
}

char* my_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *dup = malloc(len);
    if (dup) memcpy(dup, str, len);
    return dup;
}

// Struktura słownika
typedef struct {
    int code;
    char *value;
} DictionaryEntry;

size_t lzw_decompress(const uint32_t *compressed, size_t compressed_size, char **decompressed) {
    DictionaryEntry dictionary[MAX_DICT_SIZE];
    size_t dict_count = 256;

    for (int i = 0; i < 256; i++) {
        dictionary[i].code = i;
        dictionary[i].value = malloc(2);
        if (!dictionary[i].value) return 0;
        dictionary[i].value[0] = i;
        dictionary[i].value[1] = '\0';
    }

    size_t output_capacity = 1024;
    char *output = malloc(output_capacity);
    if (!output) return 0;

    size_t output_index = 0;
    int old_code = compressed[0];
    char *prev_string = my_strdup(dictionary[old_code].value);

    for (size_t i = 1; i < compressed_size; i++) {
        size_t new_code = compressed[i];
        char *entry = NULL;

        if (new_code < dict_count) {
            entry = dictionary[new_code].value;
        } else if (new_code == dict_count) {  
            entry = malloc(strlen(prev_string) + 2);
            if (!entry) break;
            strcpy(entry, prev_string);
            entry[strlen(prev_string)] = prev_string[0];
            entry[strlen(prev_string) + 1] = '\0';
        } else break;

        size_t entry_len = strlen(entry);
        if (output_index + entry_len >= output_capacity) {
            char *new_output = realloc(output, output_capacity * 2);
            if (!new_output) {
                free(output);
                return 0;
            }
            output = new_output;
            output_capacity *= 2;
        }

        memcpy(output + output_index, entry, entry_len);
        output_index += entry_len;
        output[output_index] = '\0';

        if (dict_count < MAX_DICT_SIZE) {
            dictionary[dict_count].value = malloc(strlen(prev_string) + 2);
            if (!dictionary[dict_count].value) break;
            strcpy(dictionary[dict_count].value, prev_string);
            dictionary[dict_count].value[strlen(prev_string)] = entry[0];
            dictionary[dict_count].value[strlen(prev_string) + 1] = '\0';
            dict_count++;
        }

        free(prev_string);
        prev_string = my_strdup(entry);

        if (new_code == dict_count - 1) free(entry);
    }

    for (size_t i = 0; i < dict_count; i++) free(dictionary[i].value);
    free(prev_string);
    *decompressed = output;
    return output_index;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("BLAD\n");
        return 1;
    }

    unsigned char *decoded_data;
    int decoded_size = base64_decode(argv[1], &decoded_data);
    if (decoded_size == -1) {
        printf("BLAD\n");
        return 1;
    }

    uint32_t *compressed_data = (uint32_t *)decoded_data;
    size_t compressed_size = decoded_size / sizeof(uint32_t);

    char *decompressed_output;
    size_t decompressed_size = lzw_decompress(compressed_data, compressed_size, &decompressed_output);

    printf(" ");
    if (decompressed_size > 0) printf("%s\n", decompressed_output);
    else printf("BLAD\n");

    free(decompressed_output);
    free(decoded_data);
    return 0;
}
