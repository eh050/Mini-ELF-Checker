/*
 * CS 261: Main driver
 *
 * Name: Elias Hawkins
 */

#include "p1-check.h"

/* Helper variables. */
bool header_mode = false;
elf_hdr_t hdr;

/*
 * helper function for printing help text
 */
void usage (char **argv)
{
    printf("Usage: %s <option(s)> mini-elf-file\n", argv[0]);
    printf(" Options are:\n");
    printf("  -h      Display usage\n");
    printf("  -H      Show the Mini-ELF header\n");
}

int main (int argc, char **argv)
{
    // getopt to handle CLI arguments.
    int opt;
    while ((opt = getopt(argc, argv, "hH")) != -1) {
        switch (opt) {
            case 'h':
                usage(argv);
                return EXIT_SUCCESS;
            case 'H':
                header_mode = true;
                break;
            default:
                usage(argv);
                return EXIT_FAILURE;
        }
    }

    // Check for invalid parameters.
    if (argc - optind != 1) {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    // Check validity regardless of whether the "-H" flag is specified!
    char *header_mode_file = argv[optind];
    FILE *file = fopen(header_mode_file, "r");

    // Catch the error when the file does not exist.
    if (file == NULL) {
        printf("%s\n", "Failed to read file");
        return EXIT_FAILURE;
    }

    // Catch the error when read_header is false.
    if (!(read_header(file, &hdr))) {
        printf("%s\n", "Failed to read file");
        return EXIT_FAILURE;
    }

    // If everything passes, print the header.
    if (header_mode) {
        // Already read the file so we can just point to hdr.
        // Use unsigned to avoid 0xf4 being interpreted as -12.
        unsigned char *data = (unsigned char *)&hdr;
        for (int i=0; i < sizeof(elf_hdr_t); i++) {
            printf("%02x", data[i]);
            if (i != sizeof(elf_hdr_t) - 1) {
                printf(" ");
            }
            if (i == 7) {
                printf(" ");
            }
        }
        printf("\n");
        dump_header(&hdr);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
