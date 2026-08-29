#include "ls.h"

static Flags *g_flags = NULL;

static int compare_entries(const void *a, const void *b) {
    const FileEntry *fa = (const FileEntry *)a;
    const FileEntry *fb = (const FileEntry *)b;
    int res = 0;

    /* Sp xp theo kch thc (-S) */
    if (g_flags->sort_size) {
        if (fa->st.st_size > fb->st.st_size) res = -1;
        else if (fa->st.st_size < fb->st.st_size) res = 1;
        else res = strcmp(fa->name, fb->name);
    }
    /* Sp xp theo thi gian (-t) */
    else if (g_flags->sort_time) {
        if (fa->st.st_mtime > fb->st.st_mtime) res = -1;
        else if (fa->st.st_mtime < fb->st.st_mtime) res = 1;
        else res = strcmp(fa->name, fb->name);
    }
    /* Mc nh sp theo bng ch ci */
    else {
        res = strcmp(fa->name, fb->name);
    }

    /* o ngc th t nu c c -r */
    if (g_flags->reverse) {
        res = -res;
    }

    return res;
}

void sort_entries(FileEntry *entries, int count, Flags *flags) {
    if (flags->no_sort || count <= 1) {
        return;
    }
    g_flags = flags;
    qsort(entries, count, sizeof(FileEntry), compare_entries);
}
