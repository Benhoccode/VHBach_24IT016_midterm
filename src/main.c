#include "defs.h"
#include "parse.h"
#include "traverse.h"

int main(int argc, char *argv[]) {
    Flags flags;
    int arg_index = parse_arguments(argc, argv, &flags);
    if (arg_index == -1) {
        fprintf(stderr, "usage: ls [-AacdFfhiklnqRrSstuw] [file ...]\n");
        exit(EXIT_FAILURE);
    }

    /* Neu khong co doi so duong dan nao, mac dinh mo thu muc hien tai "." */
    if (arg_index >= argc) {
        process_path(".", &flags, 1);
    } else {
        int num_files = argc - arg_index;
        for (int i = arg_index; i < argc; i++) {
            if (num_files > 1) {
                printf("%s:\n", argv[i]);
            }
            process_path(argv[i], &flags, 1);
            if (num_files > 1 && i < argc - 1) {
                putchar('\n');
            }
        }
    }

    return EXIT_SUCCESS;
}
