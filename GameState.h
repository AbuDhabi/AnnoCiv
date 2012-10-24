#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED


typedef struct GameState {
    GameMap gm;
    City cities[MAX_CITIES];
} GameState;

#endif // GAMESTATE_H_INCLUDED
