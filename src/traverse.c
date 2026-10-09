#include "traverse.h"
#include "sort.h"
#include "print.h"

void process_path(const char *path, const Flags *flags, int is_argument) {
    struct stat st;
    if (lstat(path, &st) == -1) {
        perror(path);
        return;
    }

    /* Neu la file don le hoac co co -d (chi xem thu muc nhu file) */
    if (!S_ISDIR(st.st_mode) || flags->directory_only) {
        FileEntry single_entry;
        strncpy(single_entry.name, path, sizeof(single_entry.name) - 1);
        single_entry.name[sizeof(single_entry.name) - 1] = '\0';
        strncpy(single_entry.path, path, sizeof(single_entry.path) - 1);
        single_entry.path[sizeof(single_entry.path) - 1] = '\0';
        single_entry.st = st;

        print_entry(&single_entry, flags);
        return;
    }

    /* Xu ly mo va doc thu muc */
    DIR *dir = opendir(path);
    if (!dir) {
        perror(path);
        return;
    }

    int capacity = 64;
    int count = 0;
    FileEntry *entries = malloc(capacity * sizeof(FileEntry));
    if (!entries) {
        perror("malloc");
        closedir(dir);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        /* Loc cac file an */
        if (!flags->show_all && !flags->almost_all && entry->d_name[0] == '.') {
            continue;
        }
        if (flags->almost_all && (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))) {
            continue;
        }

        if (count >= capacity) {
            capacity *= 2;
            FileEntry *tmp = realloc(entries, capacity * sizeof(FileEntry));
            if (!tmp) {
                perror("realloc");
                free(entries);
                closedir(dir);
                return;
            }
            entries = tmp;
        }

        strncpy(entries[count].name, entry->d_name, sizeof(entries[count].name) - 1);
        entries[count].name[sizeof(entries[count].name) - 1] = '\0';

        if (!strcmp(path, ".")) {
            snprintf(entries[count].path, sizeof(entries[count].path), "%s", entry->d_name);
        } else {
            snprintf(entries[count].path, sizeof(entries[count].path), "%s/%s", path, entry->d_name);
        }

        if (lstat(entries[count].path, &entries[count].st) == -1) {
            memset(&entries[count].st, 0, sizeof(struct stat));
        }
        count++;
    }
    closedir(dir);

    /* Sap xep danh sach */
    sort_entries(entries, count, flags);

    /* In dong tong so blocks neu co -l hoac -s */
    if ((flags->long_format || flags->blocks) && count > 0) {
        print_total_blocks(entries, count, flags);
    }

    /* In cac file trong thu muc */
    for (int i = 0; i < count; i++) {
        print_entry(&entries[i], flags);
    }

    /* Xu ly de quy (-R) */
    if (flags->recursive) {
        for (int i = 0; i < count; i++) {
            if (S_ISDIR(entries[i].st.st_mode) &&
                strcmp(entries[i].name, ".") != 0 &&
                strcmp(entries[i].name, "..") != 0) {
                printf("\n%s:\n", entries[i].path);
                process_path(entries[i].path, flags, 0);
            }
        }
    }

    free(entries);
    (void)is_argument;
}
