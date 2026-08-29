#include "ls.h"

int main(int argc, char *argv[]) {
    Flags flags;
    memset(&flags, 0, sizeof(Flags));

    int opt;
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
            case 'f':
                flags.no_sort = 1;
                flags.show_all = 1; /* Theo manual: -f bt show_all v b sort */
                break;
            default:
                break;
        }
    }

    if (optind >= argc) {
        list_directory(".", &flags);
    } else {
        for (int i = optind; i < argc; i++) {
            list_directory(argv[i], &flags);
        }
    }

    return 0;
}
