#ifndef LS_H
#define LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Cu trc lu tr trng thi cc c lnh */
typedef struct {
    int show_all;       /* -a (1: hin tt c gm . v ..) */
    int almost_all;     /* -A (1: hin tt c tr . v ..) */
    int long_format;    /* -l (1) hoc -n (2) */
    int recursive;      /* -R */
    int sort_time;      /* -t */
    int sort_size;      /* -S */
    int reverse;        /* -r */
    int no_sort;        /* -f */
    int classify;       /* -F */
    int inode;          /* -i */
    int directory_only; /* -d */
} Flags;

/* Cu trc lu thng tin ca tng file  sp xp */
typedef struct {
    char name[256];
    char path[1024];
    struct stat st;
} FileEntry;

/* Khai bo hm */
void list_directory(const char *dir_path, Flags *flags);

#endif
