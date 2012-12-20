#include "header.h"
#include "globals.h"

// 00:30 <~Vornicus> basic method afaict is to use a plasma fractal (easy to look 
//                  up) to assign altitudes, then use the altitudes to assign 
//                  terrains.
// 00:31 <~Vornicus> You can then do things like "rain piles up on the windward 
//                  side of mountains", "rivers go from cell to cell in the 
//                  steepest direction", and some other stuff like that.

// RIVERS ARE FUCKED UP GOD DAMN

bool are_coords_valid(int x, int y) {
    if (x <0) return false;
    if (y <0) return false;
    if (x >= MAX_GAME_MAP_X) return false;
    if (y >= MAX_GAME_MAP_Y) return false;
    return true;
}

bool any_surrounding_tile_match(int x, int y, int tile_code) {
    if (gs.gm.tiles[x+1][y+1].tile_id == tile_code && are_coords_valid(x+1,y+1)) { return true; }
    if (gs.gm.tiles[x+1][y].tile_id == tile_code && are_coords_valid(x+1,y)) { return true; }
    if (gs.gm.tiles[x+1][y-1].tile_id == tile_code && are_coords_valid(x+1,y-1)) { return true; }
    if (gs.gm.tiles[x][y+1].tile_id == tile_code && are_coords_valid(x,y+1)) { return true; }
    if (gs.gm.tiles[x][y-1].tile_id == tile_code && are_coords_valid(x,y-1)) { return true; }
    if (gs.gm.tiles[x-1][y+1].tile_id == tile_code && are_coords_valid(x-1,y+1)) { return true; }
    if (gs.gm.tiles[x-1][y].tile_id == tile_code && are_coords_valid(x-1,y)) { return true; }
    if (gs.gm.tiles[x-1][y-1].tile_id == tile_code && are_coords_valid(x-1,y-1)) { return true; }
    
    return false;
}

bool any_surrounding_unvisited_river(int x, int y) {
    if ((gs.gm.rivers[x+1][y+1] == 1) && (gs.gm.roads[x+1][y+1] == 0) && are_coords_valid(x+1,y+1)) { return true; }
    if ((gs.gm.rivers[x+1][y] == 1) && (gs.gm.roads[x+1][y] == 0) && are_coords_valid(x+1,y)) { return true; }
    if ((gs.gm.rivers[x+1][y-1] == 1) && (gs.gm.roads[x+1][y-1] == 0) && are_coords_valid(x+1,y-1)) { return true; }
    if ((gs.gm.rivers[x][y+1] == 1) && (gs.gm.roads[x][y+1] == 0) && are_coords_valid(x,y+1)) { return true; }
    if ((gs.gm.rivers[x][y-1] == 1) && (gs.gm.roads[x][y-1] == 0) && are_coords_valid(x,y-1)) { return true; }
    if ((gs.gm.rivers[x-1][y+1] == 1) && (gs.gm.roads[x-1][y+1] == 0) && are_coords_valid(x-1,y+1)) { return true; }
    if ((gs.gm.rivers[x-1][y] == 1) && (gs.gm.roads[x-1][y] == 0) && are_coords_valid(x-1,y)) { return true; }
    if ((gs.gm.rivers[x-1][y-1] == 1) && (gs.gm.roads[x-1][y-1] == 0) && are_coords_valid(x-1,y-1)) { return true; }
    
    return false;
}

bool any_available_spaces_to_go(int x, int y) {
    if (are_coords_valid(x+1,y+1) && (gs.gm.roads[x+1][y+1] == 0)) { return true; }
    if (are_coords_valid(x+1,y) && (gs.gm.roads[x+1][y] == 0)) { return true; }
    if (are_coords_valid(x+1,y-1) && (gs.gm.roads[x+1][y-1] == 0)) { return true; }
    if (are_coords_valid(x,y+1) && (gs.gm.roads[x][y+1] == 0)) { return true; }
    if (are_coords_valid(x,y-1) && (gs.gm.roads[x][y-1] == 0)) { return true; }
    if (are_coords_valid(x-1,y+1) && (gs.gm.roads[x-1][y+1] == 0)) { return true; }
    if (are_coords_valid(x-1,y) && (gs.gm.roads[x-1][y] == 0)) { return true; }
    if (are_coords_valid(x-1,y-1) && (gs.gm.roads[x-1][y-1] == 0)) { return true; }
    
    return false;
}

bool valid_spot(int x, int y) {
    if (are_coords_valid(x,y) && (gs.gm.roads[x][y] == 0)) return true;
    return false;
}


int generate_map (int seed, int params) {
    int number;
    // just making sure everything is initialized somehow
    for (int i=0;i<MAX_GAME_MAP_X;i++) {
        for (int j=0;j<MAX_GAME_MAP_Y;j++) {
            gs.gm.tiles[i][j]=TILE_ARCTIC;
            gs.gm.rivers[i][j]=0;
            gs.gm.roads[i][j]=0;
        }
    }
    
    // let's try beginning with water/land division
    for (int i=0;i<MAX_GAME_MAP_X;i++) {
        for (int j=0;j<MAX_GAME_MAP_Y;j++) {
            if (rand()%100 < 5 ) {
                gs.gm.tiles[i][j]=TILE_WATER;
            } else {
                gs.gm.tiles[i][j]=TILE_GRASSLAND;
            }
        }
    }
    // passes of adding water, assigning to rivers as a placeholder
    for (int k=0;k<5;k++) {
        for (int i=0;i<MAX_GAME_MAP_X;i++) {
            for (int j=0;j<MAX_GAME_MAP_Y;j++) {
                if (gs.gm.tiles[i][j].tile_id == IMG_TILE_WATER) {
                    if (rand()%100 < 10 && j-1 > 0) gs.gm.rivers[i][j-1] = IMG_TILE_WATER;
                    if (rand()%100 < 10 && j-1 > 0 && i+1 < MAX_GAME_MAP_X) gs.gm.rivers[i+1][j-1] = IMG_TILE_WATER;
                    if (rand()%100 < 10 && j-1 > 0 && i-1 > 0) gs.gm.rivers[i-1][j-1] = IMG_TILE_WATER;
                    if (rand()%100 < 10 && i+1 < MAX_GAME_MAP_X) gs.gm.rivers[i+1][j] = IMG_TILE_WATER;
                    if (rand()%100 < 10 && i-1 > 0) gs.gm.rivers[i-1][j] = IMG_TILE_WATER;
                    if (rand()%100 < 10 && j+1 < MAX_GAME_MAP_Y && i+1 < MAX_GAME_MAP_X) gs.gm.rivers[i+1][j+1] = IMG_TILE_WATER;
                    if (rand()%100 < 10 && j+1 < MAX_GAME_MAP_Y) gs.gm.rivers[i][j+1] = IMG_TILE_WATER;
                    if (rand()%100 < 10 && i-1 > 0 && j+1 < MAX_GAME_MAP_Y) gs.gm.rivers[i-1][j+1] = IMG_TILE_WATER;
                }
            }
        }
        for (int i=0;i<MAX_GAME_MAP_X;i++) {
            for (int j=0;j<MAX_GAME_MAP_Y;j++) {
                if (gs.gm.rivers[i][j] == IMG_TILE_WATER ) {
                    gs.gm.tiles[i][j]=TILE_WATER;
                    gs.gm.rivers[i][j] = 0;
                }
            }
        }
    }

    //now filling out the ground tiles, according to zones of climate
    for (int i=0;i<MAX_GAME_MAP_X;i++) {
        for (int j=0;j<MAX_GAME_MAP_Y;j++) {
            if (gs.gm.tiles[i][j].tile_id == IMG_TILE_WATER) continue;
            if (j<MAX_GAME_MAP_Y*0.10 || j>=MAX_GAME_MAP_Y*0.90) { // extremely cold
                number = rand()%10+1;
                switch (number) {
                    case 1:
                    case 2:
                    case 3:
                        gs.gm.tiles[i][j]=TILE_ARCTIC;
                        break;
                    case 4:
                    case 5:
                    case 6:
                        gs.gm.tiles[i][j]=TILE_TUNDRA;
                        break;
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                        gs.gm.tiles[i][j]=TILE_TUNDRA;
                        break;
                    default:
                        gs.gm.tiles[i][j]=TILE_WATER;
                        break;
                }
            } else if ((j>=MAX_GAME_MAP_Y*0.10 && j<MAX_GAME_MAP_Y*0.20) || (j>=MAX_GAME_MAP_Y*0.80 && j<MAX_GAME_MAP_Y*0.90)) { // cold
                number = rand()%10+1;
                switch (number) {
                    case 1:
                    case 2:
                        gs.gm.tiles[i][j]=TILE_TUNDRA;
                        break;
                    case 3:
                    case 4:
                        gs.gm.tiles[i][j]=TILE_FOREST;
                        break;
                    case 5:
                        gs.gm.tiles[i][j]=TILE_GRASSLAND;
                        break;
                    case 6:
                        gs.gm.tiles[i][j]=TILE_HILLS;
                        break;                    
                    case 7:
                        gs.gm.tiles[i][j]=TILE_MOUNTAIN;
                        break;                    
                    case 8:
                        gs.gm.tiles[i][j]=TILE_SWAMP;
                        break;                    
                    case 9:
                        gs.gm.tiles[i][j]=TILE_SWAMP;
                        break;                     
                    case 10:
                        gs.gm.tiles[i][j]=TILE_FOREST;
                        break;
                    default:
                        gs.gm.tiles[i][j]=TILE_WATER;
                        break;
                }
            } else if ((j>=MAX_GAME_MAP_Y*0.20 && j<MAX_GAME_MAP_Y*0.30) || (j>=MAX_GAME_MAP_Y*0.70 && j<MAX_GAME_MAP_Y*0.80)) { // temperate
                                number = rand()%10+1;
                switch (number) {
                    case 1:
                    case 2:
                        gs.gm.tiles[i][j]=TILE_GRASSLAND;
                        break;
                    case 3:
                    case 4:
                        gs.gm.tiles[i][j]=TILE_FOREST;
                        break;
                    case 5:
                        gs.gm.tiles[i][j]=TILE_GRASSLAND;
                        break;
                    case 6:
                        gs.gm.tiles[i][j]=TILE_HILLS;
                        break;                    
                    case 7:
                        gs.gm.tiles[i][j]=TILE_MOUNTAIN;
                        break;                    
                    case 8:
                        gs.gm.tiles[i][j]=TILE_SWAMP;
                        break;                    
                    case 9:
                    case 10:
                        gs.gm.tiles[i][j]=TILE_FOREST;
                        break;
                    default:
                        gs.gm.tiles[i][j]=TILE_WATER;
                        break;
                }
            } else if ((j>=MAX_GAME_MAP_Y*0.30 && j<MAX_GAME_MAP_Y*0.40) || (j>=MAX_GAME_MAP_Y*0.60 && j<MAX_GAME_MAP_Y*0.70)) { // hot and dry
                                number = rand()%10+1;
                switch (number) {
                    case 1:
                    case 2:
                        gs.gm.tiles[i][j]=TILE_DESERT;
                        break;
                    case 3:
                    case 4:
                        gs.gm.tiles[i][j]=TILE_GRASSLAND;
                        break;
                    case 5:
                        gs.gm.tiles[i][j]=TILE_GRASSLAND;
                        break;
                    case 6:
                        gs.gm.tiles[i][j]=TILE_HILLS;
                        break;                    
                    case 7:
                        gs.gm.tiles[i][j]=TILE_MOUNTAIN;
                        break;                    
                    case 8:
                        gs.gm.tiles[i][j]=TILE_DESERT;
                        break;                    
                    case 9:
                    case 10:
                        gs.gm.tiles[i][j]=TILE_DESERT;
                        break;
                    default:
                        gs.gm.tiles[i][j]=TILE_WATER;
                        break;
                }
            } else { // hot and wet
                number = rand()%10+1;
                switch (number) {
                    case 1:
                    case 2:
                        gs.gm.tiles[i][j]=TILE_JUNGLE;
                        break;
                    case 3:
                    case 4:
                        gs.gm.tiles[i][j]=TILE_JUNGLE;
                        break;
                    case 5:
                        gs.gm.tiles[i][j]=TILE_GRASSLAND;
                        break;
                    case 6:
                        gs.gm.tiles[i][j]=TILE_HILLS;
                        break;                    
                    case 7:
                        gs.gm.tiles[i][j]=TILE_MOUNTAIN;
                        break;                    
                    case 8:
                        gs.gm.tiles[i][j]=TILE_SWAMP;
                        break;                    
                    case 9:
                    case 10:
                        gs.gm.tiles[i][j]=TILE_JUNGLE;
                        break;
                    default:
                        gs.gm.tiles[i][j]=TILE_WATER;
                        break;
                }
            }
            //gs.gm.tiles[i][j]=rand()%10+1;
            //gs.gm.rivers[i][j]=rand()%2-rand()%3+1;
            //gs.gm.roads[i][j]=rand()%2-rand()%3+1;
        }
    }
    // at this point, it's a random map with only tiles defined
    // it makes sort of sense, according to climate zones
    
    // let's try rivers next
    // starting somewhere and randomly walking towards water
    int xx,yy; int oxx, oyy;
    int counter;
    int validopts[8];
    for (int k=0;k<MAX_RIVERS;k++) {
        do { // generate non-water, non-river-adjacent initial tile
            xx = rand()%MAX_GAME_MAP_X;
            yy = rand()%MAX_GAME_MAP_Y;
        } while (gs.gm.tiles[xx][yy].tile_id == IMG_TILE_WATER || gs.gm.rivers[xx][yy] == 1 || any_surrounding_unvisited_river(xx,yy));
        gs.gm.rivers[xx][yy] = 1; // place river here
        
        while (!any_surrounding_tile_match(xx,yy,IMG_TILE_WATER) 
               && !any_surrounding_unvisited_river(xx,yy)) {
            // save old coords
            oxx = xx;
            oyy = yy;
            // pick a random valid neighbour to go to, or call it quits if none exist
            if (!any_available_spaces_to_go(xx, yy)) { break; }
            
            counter=0;
            for (int i=0;i<8;i++) validopts[i] = 0;
            if (valid_spot(xx+1,yy+1)) { validopts[counter] = 0; counter++; }
            if (valid_spot(xx+1,yy)) { validopts[counter] = 1; counter++; }
            if (valid_spot(xx+1,yy-1)) { validopts[counter] = 2; counter++; }
            if (valid_spot(xx,yy+1)) { validopts[counter] = 3; counter++; }
            if (valid_spot(xx,yy-1)) { validopts[counter] = 4; counter++; }
            if (valid_spot(xx-1,yy+1)) { validopts[counter] = 5; counter++; }
            if (valid_spot(xx-1,yy)) { validopts[counter] = 6; counter++; }
            if (valid_spot(xx-1,yy-1)) { validopts[counter] = 7; counter++; }
            if (counter>0) number=validopts[rand()%counter]; else break;
            if      (number == 0) { xx++; yy++; }
            else if (number == 1) { xx++;  }
            else if (number == 2) { xx++; yy--; }
            else if (number == 3) {  yy++; }
            else if (number == 4) {  yy--; }
            else if (number == 5) { xx--; yy++; }
            else if (number == 6) { xx--; }
            else if (number == 7) { xx--; yy--; }
            else { break; } // what the shit?
            
            // add river here
            gs.gm.rivers[xx][yy] = 1;
            // visited spots get tracked
            if (valid_spot(oxx+1,oyy+1)) gs.gm.roads[oxx+1][oyy+1] = 1;
            if (valid_spot(oxx+1,oyy))   gs.gm.roads[oxx+1][oyy] = 1;
            if (valid_spot(oxx+1,oyy-1)) gs.gm.roads[oxx+1][oyy-1] = 1;
            if (valid_spot(oxx,oyy+1))   gs.gm.roads[oxx][oyy+1] = 1;
            if (valid_spot(oxx,oyy))     gs.gm.roads[oxx][oyy] = 1;
            if (valid_spot(oxx,oyy-1))   gs.gm.roads[oxx][oyy-1] = 1;
            if (valid_spot(oxx-1,oyy+1)) gs.gm.roads[oxx-1][oyy+1] = 1;
            if (valid_spot(oxx-1,oyy))   gs.gm.roads[oxx-1][oyy] = 1;
            if (valid_spot(oxx-1,oyy-1)) gs.gm.roads[oxx-1][oyy-1] = 1;            
        }
        // clean up visited
        for (int i=0;i<MAX_GAME_MAP_X;i++) {
            for (int j=0;j<MAX_GAME_MAP_Y;j++) {
                gs.gm.roads[i][j] = 0;
            }
        }
            
    }
    
    
    // SHIT'S FUCKED
    /*
    int xx,yy; int oxx, oyy; 
    int validopts[8];
    int xc, yc;
    int done;
    int dir;
    //789
    //4 6
    //123
    int counter;
    for (int k=0;k<MAX_RIVERS;k++) {
        do { // generate non-water, non-river-adjacent initial tile
            xx = rand()%MAX_GAME_MAP_X;
            yy = rand()%MAX_GAME_MAP_Y;
        } while (gs.gm.tiles[xx][yy] == IMG_TILE_WATER || any_surrounding_unvisited_river(xx,yy));
        gs.gm.rivers[xx][yy] = 1; // place river here
        
        while (!any_surrounding_tile_match(xx,yy,IMG_TILE_WATER) 
               && !any_surrounding_unvisited_river(xx,yy)) {
            // save old coords
            oxx = xx;
            oyy = yy;
            // pick a random valid neighbour to go to, or call it quits if none exist
            if (!any_available_spaces_to_go(xx, yy)) { break; }
            
            if (valid_spot(xx+1,yy+1)) { xx++; yy++;}
            else if (valid_spot(xx+1,yy)) { xx++; yy;}
            else if (valid_spot(xx+1,yy-1)) { xx++; yy--;}
            else if (valid_spot(xx,yy+1)) { xx; yy++;}
            else if (valid_spot(xx,yy-1)) { xx; yy--;}
            else if (valid_spot(xx-1,yy+1)) { xx--; yy++;}
            else if (valid_spot(xx-1,yy)) { xx--; yy;}
            else if (valid_spot(xx-1,yy-1)) { xx--; yy--;}
            else {break;}
            /// *
            counter=0;
            for (int i=0;i<8;i++) validopts[i] = 0;
            if (valid_spot(xx+1,yy+1)) { validopts[counter] = 0; counter++; }
            if (valid_spot(xx+1,yy)) { validopts[counter] = 1; counter++; }
            if (valid_spot(xx+1,yy-1)) { validopts[counter] = 2; counter++; }
            if (valid_spot(xx,yy+1)) { validopts[counter] = 3; counter++; }
            if (valid_spot(xx,yy-1)) { validopts[counter] = 4; counter++; }
            if (valid_spot(xx-1,yy+1)) { validopts[counter] = 5; counter++; }
            if (valid_spot(xx-1,yy)) { validopts[counter] = 6; counter++; }
            if (valid_spot(xx-1,yy-1)) { validopts[counter] = 7; counter++; }
            if (counter>0) number=validopts[rand()%counter]; else break;
            if      (number == 0) { xx++; yy++; }
            else if (number == 1) { xx++; yy; }
            else if (number == 2) { xx++; yy--; }
            else if (number == 3) { xx; yy++; }
            else if (number == 4) { xx; yy--; }
            else if (number == 5) { xx--; yy++; }
            else if (number == 6) { xx--; yy; }
            else if (number == 7) { xx--; yy--; }
            else { break; } // what the shit?
            // * /

            
            // add river here
            gs.gm.rivers[xx][yy] = 1;
            // visited spots get tracked
            if (valid_spot(oxx+1,oyy+1)) gs.gm.roads[oxx+1][oyy+1] = 1;
            if (valid_spot(oxx+1,oyy))   gs.gm.roads[oxx+1][oyy] = 1;
            if (valid_spot(oxx+1,oyy-1)) gs.gm.roads[oxx+1][oyy-1] = 1;
            if (valid_spot(oxx,oyy+1))   gs.gm.roads[oxx][oyy+1] = 1;
            if (valid_spot(oxx,oyy))     gs.gm.roads[oxx][oyy] = 1;
            if (valid_spot(oxx,oyy-1))   gs.gm.roads[oxx][oyy-1] = 1;
            if (valid_spot(oxx-1,oyy+1)) gs.gm.roads[oxx-1][oyy+1] = 1;
            if (valid_spot(oxx-1,oyy))   gs.gm.roads[oxx-1][oyy] = 1;
            if (valid_spot(oxx-1,oyy-1)) gs.gm.roads[oxx-1][oyy-1] = 1;            
        }
        // clean up visited
        for (int i=0;i<MAX_GAME_MAP_X;i++) {
            for (int j=0;j<MAX_GAME_MAP_Y;j++) {
                gs.gm.roads[i][j] = 0;
            }
        }
        
    }
    */
//00:39 <~Vornicus> After each step of your random walk, add all 8 tiles around 
//                  the previous step to the visited list.
//00:42 <@AnnoDomini> Intredasting.
//00:42 <~Vornicus> This will prevent your river from looping.
//00:43 <~Vornicus> Successful termination occurs when the river reaches a sea or 
//                  other river tile; failure occurs when you run out of tiles to 
//                  go to that are not on the visited list.

    
    
    return 0;
}
