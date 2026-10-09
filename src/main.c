#include "defs.h"
#include "parse.h"
#include "sort.h"
#include "print.h"
#include "traverse.h"

static int compare_names(const void *a, const void *b) {
    const char *sa = *(const char **)a;
    const char *sb = *(const char **)b;
    return strcmp(sa, sb);
}

int main(int argc, char *argv[]) {
    Flags flags;
    int arg_idx = parse_arguments(argc, argv, &flags);
    if (arg_idx == -1) {
        fprintf(stderr, "usage: ls [-AacdFfhiklnqRrSstuw] [file ...]\n");
        return EXIT_FAILURE;
    }

    /* Khong truyen doi so: mac dinh duyet thu muc hien tai "." */
    if (arg_idx >= argc) {
        process_path(".", &flags, 1);
        return EXIT_SUCCESS;
    }

    int total_args = argc - arg_idx;
    char **file_args = malloc(total_args * sizeof(char *));
    char **dir_args = malloc(total_args * sizeof(char *));
    int file_cnt = 0, dir_cnt = 0;

    /* Phan loai giua file thuong va thu muc */
    for (int i = arg_idx; i < argc; i++) {
        struct stat st;
        if (lstat(argv[i], &st) == -1) {
            perror(argv[i]);
            continue;
        }

        if (S_ISDIR(st.st_mode) && !flags.directory_only) {
            dir_args[dir_cnt++] = argv[i];
        } else {
            file_args[file_cnt++] = argv[i];
        }
    }

    /* Sap xep cac doi so theo thu tu bang chu cai */
    if (!flags.no_sort) {
        if (file_cnt > 1) qsort(file_args, file_cnt, sizeof(char *), compare_names);
        if (dir_cnt > 1) qsort(dir_args, dir_cnt, sizeof(char *), compare_names);
    }

    /* 1. In cac file thuong truoc */
    for (int i = 0; i < file_cnt; i++) {
        process_path(file_args[i], &flags, 1);
    }

    if (file_cnt > 0 && dir_cnt > 0) {
        putchar('\n');
    }

    /* 2. In cac thu muc sau */
    for (int i = 0; i < dir_cnt; i++) {
        if (total_args > 1) {
            printf("%s:\n", dir_args[i]);
        }
        process_path(dir_args[i], &flags, 1);
        if (i < dir_cnt - 1) {
            putchar('\n');
        }
    }

    free(file_args);
    free(dir_args);
    return EXIT_SUCCESS;
}
