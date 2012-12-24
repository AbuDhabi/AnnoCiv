#ifndef FACTION_H_INCLUDED
#define FACTION_H_INCLUDED

#define MAX_FACTIONS 10

#define FACTION_TYPE_INACTIVE 0
#define FACTION_TYPE_PLAYER 1
#define FACTION_TYPE_AI 2
#define FACTION_TYPE_BARBARIAN 3

#define FACTION_STATUS_ELIMINATED 0
#define FACTION_STATUS_ACTIVE 1

#define FACTION_MAX_UNIT_TYPES 8

typedef struct Faction {
    int type; // human, ai, barbarian, other, etc
    int status; // 1 active, 0 eliminated
    char name[80]; 
    int fog[MAX_GAME_MAP_X][MAX_GAME_MAP_Y]; // 0 means revealed, 1 means black
    SDL_Color color;
    Language language; // the language the faction uses for names and stuff
    Unit unit_types[FACTION_MAX_UNIT_TYPES];
} Faction;

#endif // FACTION_H_INCLUDED
