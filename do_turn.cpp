#include "header.h"
#include "globals.h"

int do_turn() {
    int lastunit = get_last_unit_id();
    // hack to restore move
    for (int i=0;i<lastunit;i++) {
        gs.units[i].curmove = gs.units[i].maxmove;
    }
    
    return 0;
}
