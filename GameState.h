#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED


typedef struct GameState {
    GameMap gm;
    City cities[MAX_CITIES];
    Unit units[MAX_UNITS];
    Faction factions[MAX_FACTIONS];
    int selected_unit;
    int selected_city;
} GameState;

#endif // GAMESTATE_H_INCLUDED
