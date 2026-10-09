#ifndef UTIL_H
#define UTIL_H

#include "defs.h"

/* Ly trng thi gian tng ng (mtime / atime / ctime) da vo flags->time_type */
time_t get_entry_time(const struct stat *st, int time_type);

/* nh dng dung lng theo kiu c c (-h) */
void format_human_size(off_t bytes, char *out, size_t out_len);

#endif /* UTIL_H */
