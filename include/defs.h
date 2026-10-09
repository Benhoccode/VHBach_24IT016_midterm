#ifndef DEFS_H
#define DEFS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Dinh nghia cau truc luu toan bo co */
typedef struct {
    int show_all;       /* -a: 1 */
    int almost_all;     /* -A: 1 */
    int long_format;    /* 0: mac dinh, 1: -l, 2: -n */
    int recursive;      /* -R */
    int sort_time;      /* -t */
    int sort_size;      /* -S */
    int reverse;        /* -r */
    int no_sort;        /* -f */
    int classify;       /* -F */
    int inode;          /* -i */
    int blocks;         /* -s */
    int human_readable; /* -h */
    int block_kb;       /* -k */
    int directory_only; /* -d */
    int time_type;      /* 0: mtime, 1: -u (atime), 2: -c (ctime) */
    int print_raw;      /* 0: -q, 1: -w */
} Flags;

/* Cau truc luu thong tin mot muc tep tin */
typedef struct {
    char name[256];
    char path[1024];
    struct stat st;
} FileEntry;

#endif /* DEFS_H */
