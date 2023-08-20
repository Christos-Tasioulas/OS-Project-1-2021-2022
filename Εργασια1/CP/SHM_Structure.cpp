#include "SHM_Structure.h"

// sends the number of the line it wants
void set_line_num(struct SHM_Structure *shm, int line_num)
{
    shm->line_num = line_num;
}