#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#define MAX_UNITS 65535
#define UNIT_TYPE_AIR 1
#define UNIT_TYPE_GROUND 2
#define UNIT_TYPE_SEA 3

#define UNIT_FLAG_SETTLER 1 // can make cities, eats food?
#define UNIT_FLAG_ENGINEER 2 // can terraform terrain
#define UNIT_FLAG_CAVALRY 4 // more move, early
#define UNIT_FLAG_MECHANIZED 8 // even more move, later
#define UNIT_FLAG_ARMORED 16 // more hit points, etc, less move
#define UNIT_FLAG_ELITE 32 // more combat power in general
#define UNIT_FLAG_STEALTH 64 // can't be seen unless stepped on, more attack power
#define UNIT_FLAG_ARTILLERY 128 // ignores walls, bonus to firepower
#define UNIT_FLAG_GUERILLA 256 // gets terrain bonus on attack AND defense
#define UNIT_FLAG_FANATIC 512 // costs no upkeep
#define UNIT_FLAG_MISSILE 1024 // additional firepower
#define UNIT_FLAG_ANTIAIR 2048 // good vs air units
#define UNIT_FLAG_ANTITANK 4096 // good vs mechanized/armored units
#define UNIT_FLAG_ATROCITY 8192 // more firepower, but damages reputation
#define UNIT_FLAG_SCOUT 16384 // sees 2 squares around, can detects invisibles
#define UNIT_FLAG_INFILTRATOR 32768 // can perform spy tricks

// missing: status (sentry, fortified, etc)

typedef struct Unit {
    int type; // as defined above
    int x;
    int y;
    int maxhp; // maximum hit points
    int hp; // current hit points
    int power; // combat power
    int maxmove; // move points
    int curmove; // current move points left
    //int move_type; // air/ground/sea MEANINGLESS
    //int load; // how many other units it can carry MEANINGLESS
    int faction_id; // id of the spawning faction
    unsigned int flags; // qualities the unit has, see defines above
    int cost; // figuring out cost can be handled as a function, then applied to prototype
    int upkeep; // how much it costs to keep up per turn
} Unit;

#endif // UNIT_H_INCLUDED
