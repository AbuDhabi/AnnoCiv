#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

// defines that don't fit anywhere else
#define MAX_RIVERS 200
#define MAX_RIVER_REROLL 20
#define CODE_INTRO 1
#define CODE_MAIN_MENU 2
#define CODE_LOAD_GAME 3
#define CODE_EXIT_GAME 4
#define CODE_SAVE_GAME 5
#define CODE_MAIN_GAME_INTERFACE 6
#define CODE_START_NEW_GAME 7
#define CHOICE_SAVE 8
#define CHOICE_LOAD 9
#define MAX_GAME_MAP_X 100
#define MAX_GAME_MAP_Y 100

// image enums
#define IMG_FULL_BLANK 0
#define IMG_TILE_GRASSLAND 1
#define IMG_TILE_FOREST 2
#define IMG_TILE_HILLS 3
#define IMG_TILE_MOUNTAIN 4
#define IMG_TILE_DESERT 5
#define IMG_TILE_JUNGLE 6
#define IMG_TILE_SWAMP 7
#define IMG_TILE_TUNDRA 8
#define IMG_TILE_WATER 9
#define IMG_TILE_ARCTIC 10
#define IMG_STATIC_CITY 11
#define IMG_UNIT_INFANTRY 12
#define IMG_UNIT_CAVALRY 13
#define IMG_UNIT_ARMOUR 14
#define IMG_UNIT_ARTILLERY 15
#define IMG_UNIT_WORKERS 16
#define IMG_UNIT_BATTLESHIP 17
#define IMG_UNIT_SUBMARINE 18
#define IMG_UNIT_SEATRANSPORT 19
#define IMG_UNIT_FIGHTER 20
#define IMG_UNIT_BOMBER 21
#define IMG_UNIT_MISSILE 22
#define IMG_UNIT_AIRTRANSPORT 23
#define IMG_FULL_INTRO 24
#define IMG_FULL_MENU 25
#define IMG_FULL_SAVELOAD 26
#define IMG_FULL_NEWGAMESETUP 27

//sound enums


//misc enums


#ifdef __cplusplus
    #include <cstdlib>
    #include <stdlib.h>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#else
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#endif

#include <cstring>
#include <time.h>

// custom structs/classes go here
#include "Point.h"
#include "City.h"
#include "Language.h"
#include "Faction.h"
#include "Unit.h"
#include "Tile.h"
#include "GameMap.h"
#include "GameState.h"
#include "Research.h"



// function declarations go here
bool load_media();
bool clean_up();
int print_full_picture(SDL_Surface* image);
int print_image_at(int x,int y,SDL_Surface* image);
int print_map(int x,int y);
int put_text_at(int x, int y, const char *text);
int generate_map (int seed, int params);
int show_intro();
int main_menu();
int main_game_interface();
int save_load_interface(int which);
int new_game_setup();
int print_interface();
bool are_coords_valid(int x, int y);
int get_last_unit_id();
int do_turn(); 
void unit_type_to_text(int id, char * output);
float appraise_city_value(int city_id);
int do_ai(int faction_id);
void unit_flags_to_text(Unit u, char* output);
int build_new_city(int x, int y, int faction);
void unit_combat(int attacker_id, int defender_id, Tile place);
int get_tile_food(int x, int y);
int get_tile_prod(int x, int y);
int get_tile_comm(int x, int y);
int resolve_city_turn(int city_id);
void make_up_word(char * output, Language lang, int syllables);
Language create_language();
void capitalize_first(char* inout);
int get_city_food(int city_id);
int city_growth(int city_id);


#endif // HEADER_H_INCLUDED
