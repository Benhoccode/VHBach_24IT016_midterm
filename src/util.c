#include "util.h"

/* Lay moc thoi gian can thiet tuy theo co -u hay -c */
time_t get_entry_time(const struct stat *st, int time_type) {
    if (time_type == 1) {
        return st->st_atime; /* -u: access time */
    } else if (time_type == 2) {
        return st->st_ctime; /* -c: status change time */
    }
    return st->st_mtime;     /* mac dinh: modification time */
}

/* Dinh dang dung luong dang B, K, M, G (-h) */
void format_human_size(off_t bytes, char *out, size_t out_len) {
    const char *units[] = {"B", "K", "M", "G", "T"};
    int unit_idx = 0;
    double size = (double)bytes;

    while (size >= 1024.0 && unit_idx < 4) {
        size /= 1024.0;
        unit_idx++;
    }

    if (unit_idx == 0) {
        snprintf(out, out_len, "%lldB", (long long)bytes);
    } else if (size < 10.0) {
        snprintf(out, out_len, "%.1f%s", size, units[unit_idx]);
    } else {
        snprintf(out, out_len, "%.0f%s", size, units[unit_idx]);
    }
}
