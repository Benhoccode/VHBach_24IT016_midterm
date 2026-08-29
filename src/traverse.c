#include "ls.h"

void list_directory(const char *dir_path, Flags *flags) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror(dir_path);
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
        /* X l lc file n */
        if (!flags->show_all && !flags->almost_all && entry->d_name[0] == '.') {
            continue;
        }
        if (flags->almost_all && (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))) {
            continue;
        }

        /* MM rng mng ng nu y */
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

        /* Lu tn v ng dn */
        strncpy(entries[count].name, entry->d_name, sizeof(entries[count].name) - 1);
        entries[count].name[sizeof(entries[count].name) - 1] = '\0';

        snprintf(entries[count].path, sizeof(entries[count].path), "%s/%s", dir_path, entry->d_name);

        /* Dng lstat  ly thng tin kch thc v thi gian */
        if (lstat(entries[count].path, &entries[count].st) == -1) {
            memset(&entries[count].st, 0, sizeof(struct stat));
        }

        count++;
    }
    closedir(dir);

    /* Sp xp danh sch */
    sort_entries(entries, count, flags);

    /* In danh sch */
    for (int i = 0; i < count; i++) {
        printf("%s\n", entries[i].name);
    }

    free(entries);
}
