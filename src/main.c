#include "ls.h"

int main(int argc, char *argv[]) {
    Flags flags;
    memset(&flags, 0, sizeof(Flags));

    int opt;
    /* c cc c t dng lnh bng getopt */
    while ((opt = getopt(argc, argv, "AacdFfhiklnqRrSstuw")) != -1) {
        switch (opt) {
            case 'a': flags.show_all = 1; break;
            case 'A': flags.almost_all = 1; break;
            case 'l': flags.long_format = 1; break;
            case 'R': flags.recursive = 1; break;
            case 'r': flags.reverse = 1; break;
            case 't': flags.sort_time = 1; break;
            case 'S': flags.sort_size = 1; break;
            case 'F': flags.classify = 1; break;
            case 'i': flags.inode = 1; break;
            default:
                break;
        }
    }

    /* Nu khng truyn ng dn no, mc nh lit k th mc hin ti "." */
    if (optind >= argc) {
        list_directory(".", &flags);
    } else {
        /* Duyt qua tng ng dn c truyn vo */
        for (int i = optind; i < argc; i++) {
            list_directory(argv[i], &flags);
        }
    }

    return 0;
}
