#include "ls.h"

void list_directory(const char *dir_path, Flags *flags) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror(dir_path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        /* Mc nh b qua file n (bt u bng du chm) nu khng c c -a / -A */
        if (!flags->show_all && !flags->almost_all && entry->d_name[0] == '.') {
            continue;
        }

        /* Tm thi in tn file ra mi dng */
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}
