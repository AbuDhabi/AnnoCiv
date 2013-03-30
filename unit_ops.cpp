#include "header.h"
#include "globals.h"

Unit get_unit(int id) {
    return gs.units[id];
}

int get_last_unit_id() {
    int id=0;
    for (int i=0;i<MAX_UNITS;i++) {
        if (gs.units[i].active == UNIT_ACTIVE) id = i;
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
    sprintf(output,"%d",u.flags);
}

// by design, you just feed references to units and this function handles it
void unit_combat(int attacker_id, int defender_id, Tile place) {
    int attack = gs.units[attacker_id].power * 1.5; // the 1.5 is attack bonus
    int defense = gs.units[defender_id].power * place.defense_bonus;
    // hack
    if (attack == 0) attack = 1;
    if (defense == 0) defense = 1;
    // end hack
    int combined = attack + defense;
    int number;
    /// TODO: Make units with 0 power unable to attack
    /// TODO: THEN remove hacks
    while (gs.units[attacker_id].hp > 0 && gs.units[defender_id].hp > 0) {
        number = rand()%combined+1;
        if (number <= attack) {
            gs.units[defender_id].hp -= gs.units[attacker_id].power;
            // hack
            if (gs.units[attacker_id].power == 0) gs.units[defender_id].hp--;
            // end hack
        } else {
            gs.units[attacker_id].hp -= gs.units[defender_id].power;
            // hack
            if (gs.units[defender_id].power == 0) gs.units[attacker_id].hp--;
            // end hack
        }
    }
    
    // making sure dead units are deactivated
    if (gs.units[attacker_id].hp < 1) gs.units[attacker_id].active = UNIT_INACTIVE;
    if (gs.units[defender_id].hp < 1) gs.units[defender_id].active = UNIT_INACTIVE;
     
    
    // total placeholder
    /// TODO: Make this actually do something decent
    //if (rand()%2) gs.units[attacker_id].hp = 0; else gs.units[defender_id].hp = 0;
}

// this function takes a unit's flags, and modifies the unit's various stats
// to be in line with its flags, such as armored units having more HPs
Unit mould_unit(int type, int flags) {
    Unit temp;
    // type, x, y, maxhp, hp, power, maxmove, curmove, faction, flags, cost, upkeep
    // some initial setup
    temp.x = -1; temp.y = -1; // placeholders, put something better in here
    temp.faction_id = -1; // placeholder
    temp.flags = flags; // flags inherited
    temp.type = type; // type inherited
    if (type == UNIT_TYPE_AIR) {
        temp.hp = 10;
        temp.maxhp = 10;
        temp.power = 1;
        temp.maxmove = 10;
        temp.curmove = 10;
        temp.cost = 20;
    } else if (type == UNIT_TYPE_SEA) {
        temp.hp = 10;
        temp.maxhp = 10;
        temp.power = 1;
        temp.maxmove = 5;
        temp.curmove = 5;
        temp.cost = 10;
    } else { // assuming ground if something unusual is here
        temp.hp = 10;
        temp.maxhp = 10;
        temp.power = 1;
        temp.maxmove = 2;
        temp.curmove = 2;
        temp.cost = 5;
    }
    if (temp.flags & UNIT_FLAG_ANTIAIR) {
        // antiair are a bit better, more costly, and have special bonuses, not included here
        temp.power += 1;
        temp.cost += 5;
    }
    if (temp.flags & UNIT_FLAG_ANTITANK) {
        // antitank are lots more powerful and costly, and have special bonuses not included here
        temp.power += 5;
        temp.cost += 20;
    }
    if (temp.flags & UNIT_FLAG_ARMORED) {
        // more hp, more cost, less move
        temp.hp += 10;
        temp.maxhp += 10;
        temp.maxmove -= 1;
        temp.curmove -= 1;
        temp.cost += 20;
    }
    if (temp.flags & UNIT_FLAG_ARTILLERY) {
        // lots more power, more cost, less move, possibly special properties
        temp.power += 5;
        temp.maxmove -= 1;
        temp.curmove -= 1;
        temp.cost += 20;
    }
    if (temp.flags & UNIT_FLAG_ATROCITY) {
        // lots more power, little more cost, with special properties, but really nasty for diplomacy
        temp.power += 5;
        temp.cost += 5;
    }
    if (temp.flags & UNIT_FLAG_CAVALRY) {
        // more more, a bit more power, more cost
        temp.power += 1;
        temp.maxmove += 1;
        temp.curmove += 1;
        temp.cost += 10;
    }
    if (temp.flags & UNIT_FLAG_ELITE) {
        // more power, more move, more hit points, more cost
        temp.power += 2;
        temp.maxmove += 1;
        temp.curmove += 1;
        temp.hp += 5;
        temp.maxhp += 5;
        temp.cost += 20;
    }
    if (temp.flags & UNIT_FLAG_ENGINEER) {
        // more hit points, special properties, more cost
        temp.hp += 5;
        temp.maxhp += 5;
        temp.cost += 10;
    }
    if (temp.flags & UNIT_FLAG_FANATIC) {
        // more power, more cost, special property of no upkeep (later here)
        temp.power += 1;
        temp.cost += 20;
    }
    if (temp.flags & UNIT_FLAG_GUERILLA) {
        // more move, more cost, special properties
        temp.maxmove += 1;
        temp.curmove += 1;
        temp.cost += 10;
    }
    if (temp.flags & UNIT_FLAG_INFILTRATOR) {
        // more move, more cost, special properties
        temp.maxmove += 1;
        temp.curmove += 1;
        temp.cost += 10;
    }
    if (temp.flags & UNIT_FLAG_MECHANIZED) {
        // more power, more hp, more cost, more move
        temp.power += 2;
        temp.hp += 5;
        temp.maxhp += 5;
        temp.maxmove += 1;
        temp.curmove += 1;
        temp.cost += 20;
    }
    if (temp.flags & UNIT_FLAG_MISSILE) {
        // lots more power, more cost, special properties
        temp.power += 5;
        temp.cost += 20;
    }
    if (temp.flags & UNIT_FLAG_SCOUT) {
        // less power, less hit points, more move, same cost, specials?
        temp.power -= 1;
        temp.hp -= 5;
        temp.maxhp -= 5;
        temp.maxmove += 1;
        temp.curmove += 1;
    }
    if (temp.flags & UNIT_FLAG_SETTLER) {
        // less move, less power, more hp, can build city, more cost, specials
        temp.power -= 1;
        temp.maxmove -= 1;
        temp.curmove -= 1;
        temp.hp += 5;
        temp.maxhp += 5;
        temp.cost += 10;
    }
    if (temp.flags & UNIT_FLAG_STEALTH) {
        // bit more power, special abilities, more cost
        temp.power += 2;
        temp.cost += 10;
    }
    
    temp.upkeep = temp.cost / 20;
    if (temp.upkeep == 0) temp.upkeep = 1;
    if (temp.flags & UNIT_FLAG_FANATIC) temp.upkeep = 0;
    
    // sanity checks
    if (temp.maxmove < 0) temp.maxmove = 0;
    if (temp.curmove < 0) temp.curmove = 0;
    
    
    return temp;
}

// put the unit into the unit registry
int spawn_unit(Unit unit, int x, int y, int faction) {
    // find spot for unit
    bool found = false;
    int i=0; 
    while (!found) {
        if (gs.units[i].active == UNIT_INACTIVE) found = true;
        if (!found && i == MAX_UNITS) return TOO_MANY_UNITS; // error code
        if (found) i--;
        i++;
    }
    unit.x = x;
    unit.y = y;
    unit.faction_id = faction;
    unit.active = UNIT_ACTIVE;
    gs.units[i] = unit;
    
    
    return 0;
}

// how much upkeep do units of this faction need?
int sum_unit_upkeep(int faction) {
    int lastunit = get_last_unit_id();
    int sum = 0;
    for (int i=0;i<=lastunit;i++) {
        if (gs.units[i].faction_id == faction) {
            sum +=  gs.units[i].upkeep;
        }
    }
    return sum;
}
