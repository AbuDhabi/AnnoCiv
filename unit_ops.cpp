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
    /// TODO: Need better names, and generation based on unit attributes/flags
    if (id == UNIT_TYPE_AIR) sprintf(output, "Air Unit");
    if (id == UNIT_TYPE_GROUND) sprintf(output, "Land Unit");
    if (id == UNIT_TYPE_SEA) sprintf(output, "Naval Unit");
}

void unit_flags_to_text(Unit u, char* output) {
    /// TODO: figure out a better way to do this. A hash?
    sprintf(output,"%d-%d",u.flags1,u.flags2);
}

// by design, you just feed references to units and this function handles it
void unit_combat(int attacker_id, int defender_id, Tile place) {
    int attack = gs.units[attacker_id].power * 1.5; // the 1.5 is attack bonus
    int defense = gs.units[defender_id].power * place.defense_bonus;
    int combined = attack + defense;
    int number;
    
    while (gs.units[attacker_id].hp > 0 && gs.units[defender_id].hp > 0) {
        number = rand()%combined+1;
        if (number <= attack) {
            gs.units[defender_id].hp -= gs.units[attacker_id].power;
        } else {
            gs.units[attacker_id].hp -= gs.units[defender_id].power;
        }
    }
     
    
    // total placeholder
    /// TODO: Make this actually do something decent
    //if (rand()%2) gs.units[attacker_id].hp = 0; else gs.units[defender_id].hp = 0;
}
