#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

static bool is_letter(char c) {
    int n = (int) c;
    return (n >= 65 && n <= 90) || (n >= 97 && n <= 122);
}

static char to_upper(char c) {
    int n = (int) c;
    if (n >= 97) {
        return (char) (n - 32);
    }
    return c;
}

char delimiters[] = {' ', '-'};

static bool is_delimiter(const char c) {
    for (size_t i = 0; i < strlen(delimiters); i++) {
        if (c == delimiters[i]) {
            return true;
        }
    }
    return false;
}

char* abbreviate(const char *phrase) {
    if (phrase == NULL) {
        return NULL;
    }

    size_t len = strlen(phrase);
    if (len == 0) {
        return NULL;
    }

    char* abbr = calloc(len, sizeof(char));
    bool flushed = false;
    char c;

    while (*phrase != '\0') {
        if (is_letter(*phrase) && !flushed) {
            c = to_upper(*phrase);
            strcat(abbr, &c);
            flushed = true;
        } else if (is_delimiter(*phrase)) {
            flushed = false;
        }
        phrase++;
    }

    return abbr;
}
