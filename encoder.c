#include <stdio.h>


char password[] = "my_password1";
char *encode_key = "0";
int sign = 1;
int key_index = 0;
FILE * infile;
FILE * outfile;

char encode(char c) {
    if (encode_key[key_index] == '\0') {
        key_index = 0;
    }
    int shift = sign * (encode_key[key_index] - '0');
    key_index++;
    if (c >= 'A' && c <= 'Z') {
        return ((c - 'A' + shift + 26) % 26) + 'A';
    }
    if (c >= '0' && c <= '9') {
        return ((c - '0' + shift + 10) % 10) + '0';
    }
    return c;
    }


int main(int argc, char **argv) {
    int debug = 1;
    infile = stdin;
    outfile = stdout;

    for(int i = 0; i < argc; i++) {
        if(debug) {
            fprintf(stderr, "%s\n", argv[i]);
        }
        if(argv[i][0] == '-' && argv[i][1] == 'D' && argv[i][2] == '\0') {
            debug = 0;
        }
        if(argv[i][0] == '+' && argv[i][1] == 'D') {
            int valid = 1;
            int j = 2;
            while(argv[i][j] != '\0') {
                if(argv[i][j] != password[j-2]) {
                    fprintf(stderr, "Invalid password\n");
                    valid = 0;
                    break;
                }
                j++;
            }
            if (password[j-2] == '\0' && valid == 1) {
                debug = 1;
            }
        }
        if (argv[i][0] == '+' && argv[i][1] == 'E') {
            encode_key = argv[i] + 2;
            sign = 1;
        }
        if (argv[i][0] == '-' && argv[i][1] == 'E') {
            encode_key = argv[i] + 2;
            sign = -1;
        }
        if (argv[i][0] == '-' && argv[i][1] == 'i') {
            infile = fopen(argv[i] + 2, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error opening input file\n");
                return 1;
            }
        }
        if (argv[i][0] == '-' && argv[i][1] == 'o') {
            outfile = fopen(argv[i] + 2, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Error opening output file\n");
                return 1;
            }
        }
    }
    for (int c = fgetc(infile); c != EOF; c = fgetc(infile)) {
        fputc(encode(c), outfile);
    }
    fclose(infile);
    fclose(outfile);
    return 0;
}
