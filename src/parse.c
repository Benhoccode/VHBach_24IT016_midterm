#include "parse.h"

int parse_arguments(int argc, char *argv[], Flags *flags) {
    int opt;
    memset(flags, 0, sizeof(Flags));

    /* Mac dinh theo man page NetBSD:
       Neu xuat ra terminal thi -q duoc bat mac dinh */
    if (isatty(STDOUT_FILENO)) {
        flags->print_raw = 0; /* -q mac dinh */
    } else {
        flags->print_raw = 1; /* -w mac dinh khi redirect */
    }

    while ((opt = getopt(argc, argv, "AacdFfhiklnqRrSstuw")) != -1) {
        switch (opt) {
            case 'a':
                flags->show_all = 1;
                break;
            case 'A':
                flags->almost_all = 1;
                break;
            case 'c':
                flags->time_type = 2; /* Su dung ctime ghi de lenh truoc do */
                break;
            case 'u':
                flags->time_type = 1; /* Su dung atime ghi de lenh truoc do */
                break;
            case 'd':
                flags->directory_only = 1;
                break;
            case 'F':
                flags->classify = 1;
                break;
            case 'f':
                flags->no_sort = 1;
                flags->show_all = 1; /* -f tu dong bat -a va tat sort */
                break;
            case 'h':
                flags->human_readable = 1;
                flags->block_kb = 0; /* -h ghi de -k */
                break;
            case 'k':
                flags->block_kb = 1;
                flags->human_readable = 0; /* -k ghi de -h */
                break;
            case 'i':
                flags->inode = 1;
                break;
            case 'l':
                flags->long_format = 1; /* -l ghi de -n */
                break;
            case 'n':
                flags->long_format = 2; /* -n ghi de -l */
                break;
            case 'q':
                flags->print_raw = 0; /* -q ghi de -w */
                break;
            case 'w':
                flags->print_raw = 1; /* -w ghi de -q */
                break;
            case 'R':
                flags->recursive = 1;
                break;
            case 'r':
                flags->reverse = 1;
                break;
            case 'S':
                flags->sort_size = 1;
                break;
            case 's':
                flags->blocks = 1;
                break;
            case 't':
                flags->sort_time = 1;
                break;
            default:
                return -1;
        }
    }
    return optind;
}
