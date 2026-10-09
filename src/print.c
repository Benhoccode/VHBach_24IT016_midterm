#include "print.h"
#include "util.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <ctype.h>

/* In ky tu phan loai (-F) */
static void print_classification(mode_t mode) {
    if (S_ISDIR(mode)) printf("/");
    else if (S_ISLNK(mode)) printf("@");
    else if (S_ISSOCK(mode)) printf("=");
    else if (S_ISFIFO(mode)) printf("|");
    else if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) printf("*");
}

/* In ten file, xu ly co -q hoac -w */
static void print_filename(const char *name, int print_raw) {
    while (*name) {
        if (!print_raw && !isprint((unsigned char)*name)) {
            putchar('?');
        } else {
            putchar(*name);
        }
        name++;
    }
}

/* In dong tong so block */
void print_total_blocks(const FileEntry *entries, int count, const Flags *flags) {
    long long total_blocks = 0;
    for (int i = 0; i < count; i++) {
        total_blocks += entries[i].st.st_blocks;
    }

    /* Tren NetBSD, st_blocks tinh theo don vi 512-byte blocks.
       Doi sang 1024-byte (1KB) don vi mac dinh chia 2 */
    long long display_blocks = (total_blocks + 1) / 2;
    printf("total %lld\n", display_blocks);
    (void)flags;
}

void print_entry(const FileEntry *entry, const Flags *flags) {
    /* 1. Co -i: In so Inode */
    if (flags->inode) {
        printf("%llu ", (unsigned long long)entry->st.st_ino);
    }

    /* 2. Co -s: In so block */
    if (flags->blocks) {
        long long blk = (entry->st.st_blocks + 1) / 2;
        printf("%4lld ", blk);
    }

    /* 3. Neu khong co co -l / -n: in ten don gian */
    if (!flags->long_format) {
        print_filename(entry->name, flags->print_raw);
        if (flags->classify) {
            print_classification(entry->st.st_mode);
        }
        putchar('\n');
        return;
    }

    /* 4. Dinh dang dai (-l / -n) */
    char mode_str[12];
    strmode(entry->st.st_mode, mode_str);

    char user_str[32], group_str[32];
    if (flags->long_format == 2) {
        snprintf(user_str, sizeof(user_str), "%u", (unsigned int)entry->st.st_uid);
        snprintf(group_str, sizeof(group_str), "%u", (unsigned int)entry->st.st_gid);
    } else {
        struct passwd *pw = getpwuid(entry->st.st_uid);
        struct group *gr = getgrgid(entry->st.st_gid);
        if (pw) snprintf(user_str, sizeof(user_str), "%s", pw->pw_name);
        else snprintf(user_str, sizeof(user_str), "%u", (unsigned int)entry->st.st_uid);

        if (gr) snprintf(group_str, sizeof(group_str), "%s", gr->gr_name);
        else snprintf(group_str, sizeof(group_str), "%u", (unsigned int)entry->st.st_gid);
    }

    char size_buf[32];
    if (flags->human_readable) {
        format_human_size(entry->st.st_size, size_buf, sizeof(size_buf));
    } else {
        snprintf(size_buf, sizeof(size_buf), "%lld", (long long)entry->st.st_size);
    }

    time_t ftime = get_entry_time(&entry->st, flags->time_type);
    struct tm *tm_info = localtime(&ftime);
    char time_str[32];
    strftime(time_str, sizeof(time_str), "%b %e %H:%M", tm_info);

    printf("%s %2ld %-8s %-8s %8s %s ",
           mode_str,
           (long)entry->st.st_nlink,
           user_str,
           group_str,
           size_buf,
           time_str);

    print_filename(entry->name, flags->print_raw);

    if (flags->classify) {
        print_classification(entry->st.st_mode);
    }

    /* Doc va in dich cua symlink */
    if (S_ISLNK(entry->st.st_mode)) {
        char link_target[1024];
        ssize_t len = readlink(entry->path, link_target, sizeof(link_target) - 1);
        if (len != -1) {
            link_target[len] = '\0';
            printf(" -> %s", link_target);
        }
    }
    putchar('\n');
}
