#ifndef PRINT_H
#define PRINT_H

#include "defs.h"

/* In thng tin ca mt file/th mc n l */
void print_entry(const FileEntry *entry, const Flags *flags);

/* In dng tng s blocks (total X) X)  u danh sch khi c -l hoc -s */
void print_total_blocks(const FileEntry *entries, int count, const Flags *flags);

#endif /* PRINT_H */
