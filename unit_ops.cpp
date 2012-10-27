#include "header.h"
#include "globals.h"

Unit get_unit(int id) {
    return gs.units[id];
}

int get_last_unit_id() {
    int id=0;
    for (int i=0;i<MAX_UNITS;i++) {
        if (gs.units[i].hp >0) id = i;
    }
    return id;
}

void unit_type_to_text(int id, char * output) {
    if (id == IMG_UNIT_AIRTRANSPORT) sprintf(output,"Air Transport");
    if (id == IMG_UNIT_ARMOUR) sprintf(output,"Armour");
    if (id == IMG_UNIT_ARTILLERY) sprintf(output,"Artillery");
    if (id == IMG_UNIT_BATTLESHIP) sprintf(output,"Battleship");
    if (id == IMG_UNIT_BOMBER) sprintf(output,"Bomber");
    if (id == IMG_UNIT_CAVALRY) sprintf(output,"Cavalry");
    if (id == IMG_UNIT_FIGHTER) sprintf(output,"Fighter");
    if (id == IMG_UNIT_INFANTRY) sprintf(output,"Infantry");
    if (id == IMG_UNIT_MISSILE) sprintf(output,"Missile");
    if (id == IMG_UNIT_SEATRANSPORT) sprintf(output,"Sea Transport");
    if (id == IMG_UNIT_SUBMARINE) sprintf(output,"Submarine");
    if (id == IMG_UNIT_WORKERS) sprintf(output,"Workers");
}
