#ifndef LS_H
#define LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int show_all;       /* -a */
    int almost_all;     /* -A */
    int long_format;    /* -l: 1, -n: 2 */
    int recursive;      /* -R */
    int sort_time;      /* -t */
    int sort_size;      /* -S */
    int reverse;        /* -r */
    int no_sort;        /* -f */
    int classify;       /* -F */
    int inode;          /* -i */
    int directory_only; /* -d */
} Flags;

typedef struct {
    char name[256];
    char path[1024];
    struct stat st;
} FileEntry;

void list_directory(const char *dir_path, Flags *flags);
void sort_entries(FileEntry *entries, int count, Flags *flags);

#endif
