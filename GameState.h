#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#define SELECTED_CITY 1
#define SELECTED_UNIT 2


typedef struct GameState {
    long unsigned int turn;
    GameMap gm;
    City cities[MAX_CITIES];
    Unit units[MAX_UNITS];
    Faction factions[MAX_FACTIONS];
    int selected_thing;
    int selected_type;
    int curx; // current looking at map x, top left corner
    int cury; // ''
    int selx; // selected (pointing at) x
    int sely; // ''
} GameState;

#endif // GAMESTATE_H_INCLUDED
