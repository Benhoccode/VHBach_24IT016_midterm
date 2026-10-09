#include "sort.h"
#include "util.h"

static const Flags *g_flags = NULL;

static int compare_entries(const void *a, const void *b) {
    const FileEntry *fa = (const FileEntry *)a;
    const FileEntry *fb = (const FileEntry *)b;
    int res = 0;

    /* 1. Uu tien co -S: sap xep theo kich thuoc */
    if (g_flags->sort_size) {
        if (fa->st.st_size > fb->st.st_size) res = -1;
        else if (fa->st.st_size < fb->st.st_size) res = 1;
        else res = strcmp(fa->name, fb->name);
    }
    /* 2. Co -t: sap xep theo thoi gian */
    else if (g_flags->sort_time) {
        time_t ta = get_entry_time(&fa->st, g_flags->time_type);
        time_t tb = get_entry_time(&fb->st, g_flags->time_type);

        if (ta > tb) res = -1;
        else if (ta < tb) res = 1;
        else res = strcmp(fa->name, fb->name);
    }
    /* 3. Mac dinh: sap theo bang chu cai */
    else {
        res = strcmp(fa->name, fb->name);
    }

    /* Neu co -r thi dao nguoc ket qua */
    if (g_flags->reverse) {
        res = -res;
    }

    return res;
}

void sort_entries(FileEntry *entries, int count, const Flags *flags) {
    if (flags->no_sort || count <= 1) {
        return;
    }
    g_flags = flags;
    qsort(entries, count, sizeof(FileEntry), compare_entries);
}
