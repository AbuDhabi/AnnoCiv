#include "header.h"
#include "globals.h"

int print_map(int x,int y) {
    int lastunit = get_last_unit_id();
    for (int i=x;i<x+10;i++) {
        for (int j=y;j<y+7;j++) {
            // tiles
            print_image_at((i-x)*64,(j-y)*64,BITMAPS[gs.gm.tiles[i][j]]);
            // any river on the tile?
            if (gs.gm.rivers[i][j] == 1) { // this may need tweaking for optimal prettiness
                int done=0;
                if ((are_coords_valid(i-1,j-1) && (gs.gm.rivers[i-1][j-1] == 1 || gs.gm.tiles[i-1][j-1] == IMG_TILE_WATER)) || !are_coords_valid(i-1,j-1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if ((are_coords_valid(i,j-1) && (gs.gm.rivers[i][j-1] == 1 || gs.gm.tiles[i][j-1] == IMG_TILE_WATER)) || !are_coords_valid(i,j-1))  {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,150,255);done++;}
                if ((are_coords_valid(i+1,j-1) && (gs.gm.rivers[i+1][j-1] == 1 || gs.gm.tiles[i+1][j-1] == IMG_TILE_WATER)) || !are_coords_valid(i+1,j-1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,150,255);done++;}
                if ((are_coords_valid(i-1,j) && (gs.gm.rivers[i-1][j] == 1 || gs.gm.tiles[i-1][j] == IMG_TILE_WATER)) || !are_coords_valid(i-1,j)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,150,255);done++;}
                if ((are_coords_valid(i+1,j) && (gs.gm.rivers[i+1][j] == 1 || gs.gm.tiles[i+1][j] == IMG_TILE_WATER)) || !are_coords_valid(i+1,j)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if ((are_coords_valid(i-1,j+1) && (gs.gm.rivers[i-1][j+1] == 1 || gs.gm.tiles[i-1][j+1] == IMG_TILE_WATER)) || !are_coords_valid(i-1,j+1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if ((are_coords_valid(i,j+1) && (gs.gm.rivers[i][j+1] == 1 || gs.gm.tiles[i][j+1] == IMG_TILE_WATER)) || !are_coords_valid(i,j+1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if ((are_coords_valid(i+1,j+1) && (gs.gm.rivers[i+1][j+1] == 1 || gs.gm.tiles[i+1][j+1] == IMG_TILE_WATER)) || !are_coords_valid(i+1,j+1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if (done == 0) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+16,(i-x)*64+48,(j-y)*64+48,0,0,150,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+48,(j-y)*64+16,(i-x)*64+16,(j-y)*64+48,0,0,150,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+16,(i-x)*64+32,(j-y)*64+48,0,0,150,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+32,(i-x)*64+48,(j-y)*64+32,0,0,150,255);
                }
            }
            // any road on the tile?
            if (gs.gm.roads[i][j] == 1) {
                int done=0;
                if (are_coords_valid(i-1,j-1) && (gs.gm.roads[i-1][j-1] == 1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i,j-1) && (gs.gm.roads[i][j-1] == 1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i+1,j-1) && (gs.gm.roads[i+1][j-1] == 1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i-1,j) && (gs.gm.roads[i-1][j] == 1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i+1,j) && (gs.gm.roads[i+1][j] == 1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i-1,j+1) && (gs.gm.roads[i-1][j+1] == 1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i,j+1) && (gs.gm.roads[i][j+1] == 1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i+1,j+1) && (gs.gm.roads[i+1][j+1] == 1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (done == 0) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+16,(i-x)*64+48,(j-y)*64+48,0,0,0,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+48,(j-y)*64+16,(i-x)*64+16,(j-y)*64+48,0,0,0,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+16,(i-x)*64+32,(j-y)*64+48,0,0,0,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+32,(i-x)*64+48,(j-y)*64+32,0,0,0,255);
                }
            }
        }
    }
    // cities and units
    for (int i=x;i<x+10;i++) {
        for (int j=y;j<y+7;j++) {
            // any city on the tile?
            for (int k=0;k<MAX_CITIES;k++) {
                if (gs.cities[k].size > 0) {
                    if (i==gs.cities[k].x && j==gs.cities[k].y) {
                        print_image_at((i-x)*64,(j-y)*64,BITMAPS[IMG_STATIC_CITY]);
                        put_text_at((i-x)*64,(j-y+1)*64,gs.cities[k].name);
                        char temp[80];
                        sprintf(temp,"%d",gs.cities[k].size);
                        boxRGBA(MAIN_SCREEN,(i-x+1)*64-24,(j-y+1)*64-15,(i-x+1)*64,(j-y+1)*64,gs.factions[gs.cities[k].faction_id].color.r,gs.factions[gs.cities[k].faction_id].color.g,gs.factions[gs.cities[k].faction_id].color.b,gs.factions[gs.cities[k].faction_id].color.unused);
                        rectangleRGBA(MAIN_SCREEN,(i-x+1)*64-24,(j-y+1)*64-15,(i-x+1)*64,(j-y+1)*64,0,0,0,255);
                        if (gs.cities[k].size > 9) 
                            put_text_at((i-x+1)*64-20,(j-y+1)*64-17,temp); 
                        else 
                            put_text_at((i-x+1)*64-10,(j-y+1)*64-17,temp);
                    }
                }
            }
            // units
            for (int k=0;k<lastunit;k++) {
                if (gs.units[k].hp > 0) {
                    if (i==gs.units[k].x && j==gs.units[k].y) {
                        print_image_at((i-x)*64,(j-y)*64,BITMAPS[gs.units[k].type]);
                        //put_text_at((i-x)*64,(j-y+1)*64,gs.cities[k].name);
                        //char temp[80];
                        //sprintf(temp,"%d",gs.cities[k].size);
                        //put_text_at((i-x+1)*64-24,(j-y+1)*64-15,temp);
                    }
                }
            }
        }
    }

    

    return 0;
}
