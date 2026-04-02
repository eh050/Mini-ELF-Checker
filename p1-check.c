/*
 * CS 261 PA1: Mini-ELF header verifier
 *
 * Name: Elias Hawkins
 */

#include "p1-check.h"

/**********************************************************************
 *                         REQUIRED FUNCTIONS
 *********************************************************************/

bool read_header (FILE *file, elf_hdr_t *hdr)
{
    /* Check if the file and pointer are NULL. */
    if (file == NULL || hdr == NULL) {
        return false;
    }

    /* Read the first line into a size struct to be checked later. */
    size_t first_line = fread(hdr, sizeof(elf_hdr_t), 1, file);

    /* Check if the file is large enough. */
    if (first_line != 1) {
        return false;
    }

    /* Check the magic number. */
    if (hdr->magic != 0x00464c45) {
        return false;
    }

    return true;

}

/**********************************************************************
 *                         OPTIONAL FUNCTIONS
 *********************************************************************/

void dump_header (elf_hdr_t *hdr)
{
    /* The first line is printed in main.c because I followed the P1 Exp. Video. */
    printf("Mini-ELF version %u\n", (uint16_t)(hdr->e_version));
    printf("Entry point 0x%x\n", (uint16_t)(hdr->e_entry));
    printf("There are %u program headers, starting at offset %u (0x%x)\n", (uint16_t)(hdr->e_num_phdr),
           (uint16_t)(hdr->e_phdr_start), (uint16_t)(hdr->e_phdr_start));
    if ((uint16_t)(hdr->e_symtab) == 0) {
        printf("There is no symbol table present\n");
    } else {
        printf("There is a symbol table starting at offset %u (0x%x)\n", (uint16_t)(hdr->e_symtab),
               (uint16_t)(hdr->e_symtab));
    }
    if ((uint16_t)(hdr->e_strtab) == 0) {
        printf("There is no string table present\n");
    } else {
        printf("There is a string table starting at offset %u (0x%x)\n", (uint16_t)(hdr->e_strtab),
               (uint16_t)(hdr->e_strtab));
    }

}
