#ifndef FACTION_H_INCLUDED
#define FACTION_H_INCLUDED

#define MAX_FACTIONS 10

#define FACTION_TYPE_INACTIVE 0
#define FACTION_TYPE_PLAYER 1
#define FACTION_TYPE_AI 2
#define FACTION_TYPE_BARBARIAN 3


typedef struct Faction {
    int type; // human, ai, barbarian, other, etc
    char name[80]; 
    SDL_Color color;
} Faction;

#endif // FACTION_H_INCLUDED
