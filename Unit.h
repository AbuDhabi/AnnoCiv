#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#define MAX_UNITS 65535
#define MOVE_TYPE_AIR 1
#define MOVE_TYPE_GROUND 2
#define MOVE_TYPE_SEA 3

// missing: status (sentry, fortified, etc), method for handling loaded units

typedef struct Unit {
    int type; // same as unit image designations
    int x;
    int y;
    int maxhp; // maximum hit points
    int hp; // current hit points
    int power; // combat power
    int maxmove; // move points
    int curmove; // current move points left
    int move_type; // air/ground/sea
    int load; // how many other units it can carry
    int faction_id; // id of the spawning faction
} Unit;

#endif // UNIT_H_INCLUDED
