#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

// PRIMARY is the base type, and is shown on the icon
// SECONDARY is a subtype, and is shown on the icon, there may be more than one. Specials go here. Mere bonuses don't.
// Otherwise, they are tertiary and not shown on the icon, but on the sidebar

#define MAX_UNITS 65535
#define TOO_MANY_UNITS 1
#define UNIT_INACTIVE -1
#define UNIT_ACTIVE 1

#define UNIT_TYPE_AIR 1 // PRIMARY
#define UNIT_TYPE_GROUND 2 // PRIMARY
#define UNIT_TYPE_SEA 3 // PRIMARY

#define UNIT_FLAG_SETTLER 1 // can make cities, eats food? // SECONDARY // 1
#define UNIT_FLAG_ENGINEER 2 // can terraform terrain // SECONDARY // 3
#define UNIT_FLAG_CAVALRY 4 // more move, early (merge with scouts?) // PRIMARY // 5
#define UNIT_FLAG_MECHANIZED 8 // even more move, later // 7
#define UNIT_FLAG_ARMORED 16 // more hit points, etc, less move // PRIMARY // 9
#define UNIT_FLAG_ELITE 32 // more combat power in general // 11
#define UNIT_FLAG_STEALTH 64 // can't be seen unless stepped on, more attack power // 13
#define UNIT_FLAG_ARTILLERY 128 // ignores walls, bonus to firepower // 15
#define UNIT_FLAG_GUERILLA 256 // gets terrain bonus on attack AND defense // 17
#define UNIT_FLAG_FANATIC 512 // costs no upkeep // 19
#define UNIT_FLAG_MISSILE 1024 // additional firepower // 21
#define UNIT_FLAG_ANTIAIR 2048 // good vs air units // 23
#define UNIT_FLAG_ANTITANK 4096 // good vs mechanized/armored units // 25
#define UNIT_FLAG_ATROCITY 8192 // more firepower, but damages reputation // SECONDARY // 27
#define UNIT_FLAG_SCOUT 16384 // sees 2 squares around, can detects invisibles // PRIMARY // 29
#define UNIT_FLAG_INFILTRATOR 32768 // can perform spy tricks // SECONDARY // 31

// missing: status (sentry, fortified, etc)

typedef struct Unit {
    int active; // whether the unit is active or not
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
