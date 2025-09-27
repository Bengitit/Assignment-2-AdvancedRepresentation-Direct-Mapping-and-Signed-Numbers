#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Prototypes
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int num, char *out);
void to_ones_complement(int num, char *out);
void to_twos_complement(int num, char *out);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s test_file.txt\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    char line[512];
    char out[512];
    int total = 0, pass = 0, testnum = 1;

    while (fgets(line, sizeof(line), fp)) {
        // Trim leading spaces
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;

        // Skip comments and blank lines
        if (*p == '#' || *p == '\0' || *p == '\n') continue;

        // Tokenize
        char *func = strtok(p, " \t\r\n");
        char *input = strtok(NULL, " \t\r\n");
        char *expected = strtok(NULL, " \t\r\n");

        if (!func || !input || !expected) continue; // malformed line

        memset(out, 0, sizeof(out));

        if (strcmp(func, "oct_to_bin") == 0) {
            oct_to_bin(input, out);
        } else if (strcmp(func, "oct_to_hex") == 0) {
            oct_to_hex(input, out);
        } else if (strcmp(func, "hex_to_bin") == 0) {
            hex_to_bin(input, out);
        } else if (strcmp(func, "to_sign_magnitude") == 0) {
            int32_t n = atoi(input);
            to_sign_magnitude(n, out);
        } else if (strcmp(func, "to_ones_complement") == 0) {
            int32_t n = atoi(input);
            to_ones_complement(n, out);
        } else if (strcmp(func, "to_twos_complement") == 0) {
            int32_t n = atoi(input);
            to_twos_complement(n, out);
        } else {
            printf("Test %d: Unknown function %s\n", testnum++, func);
            continue;
        }

        total++;
        int ispass = (strcmp(out, expected) == 0);
        if (ispass) pass++;

        printf("Test %d: %s %s -> got=%s expected=%s [%s]\n",
               testnum++, func, input, out, expected,
               ispass ? "PASS" : "FAIL");
    }

    printf("\nSummary: %d/%d tests passed\n", pass, total);

    fclose(fp);
    return 0;
}
