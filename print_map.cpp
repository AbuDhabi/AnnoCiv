#include "header.h"
#include "globals.h"

int print_map(int x,int y) {
    char temp [80];
    int lastunit = get_last_unit_id();
    for (int i=x;i<x+10;i++) {
        for (int j=y;j<y+7;j++) {
            // tiles
            print_image_at((i-x)*64,(j-y)*64,BITMAPS[gs.gm.tiles[i][j].tile_id]);
            // any river on the tile?
            if (gs.gm.tiles[i][j].flags&TILE_FLAGS_RIVER) { /// TODO: Improve prettiness
                int done=0;
                if ((are_coords_valid(i-1,j-1) && (gs.gm.tiles[i-1][j-1].flags&TILE_FLAGS_RIVER || gs.gm.tiles[i-1][j-1].tile_id == IMG_TILE_WATER)) || !are_coords_valid(i-1,j-1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if ((are_coords_valid(i,j-1) && (gs.gm.tiles[i][j-1].flags&TILE_FLAGS_RIVER || gs.gm.tiles[i][j-1].tile_id == IMG_TILE_WATER)) || !are_coords_valid(i,j-1))  {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,150,255);done++;}
                if ((are_coords_valid(i+1,j-1) && (gs.gm.tiles[i+1][j-1].flags&TILE_FLAGS_RIVER || gs.gm.tiles[i+1][j-1].tile_id == IMG_TILE_WATER)) || !are_coords_valid(i+1,j-1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,150,255);done++;}
                if ((are_coords_valid(i-1,j) && (gs.gm.tiles[i-1][j].flags&TILE_FLAGS_RIVER || gs.gm.tiles[i-1][j].tile_id == IMG_TILE_WATER)) || !are_coords_valid(i-1,j)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,150,255);done++;}
                if ((are_coords_valid(i+1,j) && (gs.gm.tiles[i+1][j].flags&TILE_FLAGS_RIVER || gs.gm.tiles[i+1][j].tile_id == IMG_TILE_WATER)) || !are_coords_valid(i+1,j)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if ((are_coords_valid(i-1,j+1) && (gs.gm.tiles[i-1][j+1].flags&TILE_FLAGS_RIVER || gs.gm.tiles[i-1][j+1].tile_id == IMG_TILE_WATER)) || !are_coords_valid(i-1,j+1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if ((are_coords_valid(i,j+1) && (gs.gm.tiles[i][j+1].flags&TILE_FLAGS_RIVER || gs.gm.tiles[i][j+1].tile_id == IMG_TILE_WATER)) || !are_coords_valid(i,j+1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if ((are_coords_valid(i+1,j+1) && (gs.gm.tiles[i+1][j+1].flags&TILE_FLAGS_RIVER || gs.gm.tiles[i+1][j+1].tile_id == IMG_TILE_WATER)) || !are_coords_valid(i+1,j+1)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if (done == 0) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+16,(i-x)*64+48,(j-y)*64+48,0,0,150,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+48,(j-y)*64+16,(i-x)*64+16,(j-y)*64+48,0,0,150,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+16,(i-x)*64+32,(j-y)*64+48,0,0,150,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+32,(i-x)*64+48,(j-y)*64+32,0,0,150,255);
                }
            }
            // any road on the tile?
            /// TODO: Improve prettiness
            if (gs.gm.tiles[i][j].flags&TILE_FLAGS_ROAD) {
                int done=0;
                if (are_coords_valid(i-1,j-1) && (gs.gm.tiles[i-1][j-1].flags&TILE_FLAGS_ROAD)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i,j-1) && (gs.gm.tiles[i][j-1].flags&TILE_FLAGS_ROAD)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i+1,j-1) && (gs.gm.tiles[i+1][j-1].flags&TILE_FLAGS_ROAD)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i-1,j) && (gs.gm.tiles[i-1][j].flags&TILE_FLAGS_ROAD)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i+1,j) && (gs.gm.tiles[i+1][j].flags&TILE_FLAGS_ROAD)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i-1,j+1) && (gs.gm.tiles[i-1][j+1].flags&TILE_FLAGS_ROAD)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i,j+1) && (gs.gm.tiles[i][j+1].flags&TILE_FLAGS_ROAD)) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (are_coords_valid(i+1,j+1) && (gs.gm.tiles[i+1][j+1].flags&TILE_FLAGS_ROAD)) {
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
            int r,g,b;
            int healthbar_length;
            int symbolcount=0;
            Sint16 vx[3], vy[3];
            for (int k=0;k<=lastunit;k++) {
                if (gs.units[k].hp > 0) {
                    if (i==gs.units[k].x && j==gs.units[k].y) {
                        /// TODO: complete figuring out the edge cases
                        /// TODO: Make the unimplemented graphical symbols and stuff
                        /// TODO: also make symbol placement so that everything is visible
                        // the basic box with black outline
                        boxRGBA(MAIN_SCREEN,(i-x)*64+12,(j-y)*64+16,(i-x)*64+52,(j-y)*64+48,gs.factions[gs.cities[k].faction_id].color.r,gs.factions[gs.cities[k].faction_id].color.g,gs.factions[gs.cities[k].faction_id].color.b,gs.factions[gs.cities[k].faction_id].color.unused);
                        rectangleRGBA(MAIN_SCREEN,(i-x)*64+12,(j-y)*64+16,(i-x)*64+52,(j-y)*64+48,0,0,0,255);
                        if (gs.units[k].type == UNIT_TYPE_GROUND) {
                            // figure out which basic type it is
                            if (gs.units[k].flags & (UNIT_FLAG_CAVALRY|UNIT_FLAG_SCOUT)) {
                                // this is a recon/cavalry unit
                                // one diagonal line
                                lineRGBA(MAIN_SCREEN,(i-x)*64+52,(j-y)*64+16,(i-x)*64+12,(j-y)*64+48,0,0,0,255);
                            } else {
                                // otherwise assume it's infantry
                                lineRGBA(MAIN_SCREEN,(i-x)*64+12,(j-y)*64+16,(i-x)*64+52,(j-y)*64+48,0,0,0,255);
                                lineRGBA(MAIN_SCREEN,(i-x)*64+52,(j-y)*64+16,(i-x)*64+12,(j-y)*64+48,0,0,0,255);
                            }
                        } else if (gs.units[k].type == UNIT_TYPE_AIR) {
                            // print a lopsided 8 or something like that here
                            // first triangle
                            vx[0] = (i-x)*64+20; vx[1] = (i-x)*64+32; vx[2] = (i-x)*64+20;
                            vy[0] = (j-y)*64+28; vy[1] = (j-y)*64+32; vy[2] = (j-y)*64+36;
                            polygonRGBA(MAIN_SCREEN, vx,vy, 3, 0, 0,0, 255);
                            // second triangle
                            vx[0] = (i-x)*64+44; vx[1] = (i-x)*64+32; vx[2] = (i-x)*64+44;
                            vy[0] = (j-y)*64+28; vy[1] = (j-y)*64+32; vy[2] = (j-y)*64+36;
                            polygonRGBA(MAIN_SCREEN, vx,vy, 3, 0, 0,0, 255);
                            
                        } else if (gs.units[k].type == UNIT_TYPE_SEA) {
                            // print an anchor here
                            // the fiddly bit
                            arcRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+36,6,-1,180,0,0,0,255);
                            // vertical line
                            lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+42,(i-x)*64+32,(j-y)*64+22,0,0,0,255);
                            // horizontal line
                            lineRGBA(MAIN_SCREEN,(i-x)*64+28,(j-y)*64+28,(i-x)*64+36,(j-y)*64+28,0,0,0,255);
                            symbolcount++;
                        }
                        // now for modifiers
                        if (gs.units[k].flags & UNIT_FLAG_ANTIAIR) {
                            // top of a dome at the bottom of the box
                            arcRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+73,32,230,310,0,0,0,255);
                            // centerx, centery, radius, degrees starting at right-center going down, end degrees, rgba
                        }
                        if (gs.units[k].flags & UNIT_FLAG_ANTITANK) {
                            // triangle across whole
                            lineRGBA(MAIN_SCREEN,(i-x)*64+12,(j-y)*64+48,(i-x)*64+32,(j-y)*64+16,0,0,0,255);
                            lineRGBA(MAIN_SCREEN,(i-x)*64+52,(j-y)*64+48,(i-x)*64+32,(j-y)*64+16,0,0,0,255);
                            
                        }
                        if (gs.units[k].flags & UNIT_FLAG_ARMORED) {
                            // stylized tank treads in center
                            ellipseRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+32,15,8,0,0,0,255);
                        }
                        if (gs.units[k].flags & UNIT_FLAG_ARTILLERY) {
                            // dot in the middle
                            filledCircleRGBA(MAIN_SCREEN,(i-x)*64+32+get_symbol_offset_x(symbolcount),
                                                         (j-y)*64+32+get_symbol_offset_y(symbolcount),2,0,0,0,255);
                            symbolcount++;
                        }
                        if (gs.units[k].flags & UNIT_FLAG_ATROCITY) {
                            // perhaps a skull? or a twist of the CBRN defence
                            
                        }
                        // cavalry already handled
                        if (gs.units[k].flags & UNIT_FLAG_ELITE) {
                            //boxed SF for special forces maybe
                        }
                        if (gs.units[k].flags & UNIT_FLAG_ENGINEER) {
                            // lopsided E in the middle
                            // horizontal line
                            lineRGBA(MAIN_SCREEN,(i-x)*64+20,(j-y)*64+32,
                                                 (i-x)*64+44,(j-y)*64+32,0,0,0,255);
                            // vertical 1
                            lineRGBA(MAIN_SCREEN,(i-x)*64+20,(j-y)*64+32,
                                                 (i-x)*64+20,(j-y)*64+36,0,0,0,255);
                            // vertical 2
                            lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+32,
                                                 (i-x)*64+32,(j-y)*64+36,0,0,0,255);
                            // vertical 3
                            lineRGBA(MAIN_SCREEN,(i-x)*64+44,(j-y)*64+32,
                                                 (i-x)*64+44,(j-y)*64+36,0,0,0,255);
                            symbolcount++;
                        }
                        if (gs.units[k].flags & UNIT_FLAG_FANATIC) {
                            // not sure what I'd use here
                        }
                        if (gs.units[k].flags & UNIT_FLAG_GUERILLA) {
                            // also not sure, perhaps the mountain
                            // lets go with a tree
                            // first triangle
                            vx[0] = (i-x)*64+28; vx[1] = (i-x)*64+32; vx[2] = (i-x)*64+36;
                            vy[0] = (j-y)*64+32; vy[1] = (j-y)*64+28; vy[2] = (j-y)*64+32;
                            for (int ii=0;i<3;i++) vx[ii] += get_symbol_offset_x(symbolcount);
                            for (int ii=0;i<3;i++) vy[ii] += get_symbol_offset_y(symbolcount);
                            filledPolygonRGBA(MAIN_SCREEN, vx,vy, 3, 0, 0,0, 255);
                            // second triangle
                            vx[0] = (i-x)*64+28; vx[1] = (i-x)*64+32; vx[2] = (i-x)*64+36;
                            vy[0] = (j-y)*64+36; vy[1] = (j-y)*64+32; vy[2] = (j-y)*64+36;
                            for (int ii=0;i<3;i++) vx[ii] += get_symbol_offset_x(symbolcount);
                            for (int ii=0;i<3;i++) vy[ii] += get_symbol_offset_y(symbolcount);
                            filledPolygonRGBA(MAIN_SCREEN, vx,vy, 3, 0, 0,0, 255);
                            // vertical line
                            lineRGBA(MAIN_SCREEN,(i-x)*64+32+get_symbol_offset_x(symbolcount),(j-y)*64+28+get_symbol_offset_y(symbolcount),
                                                 (i-x)*64+32+get_symbol_offset_x(symbolcount),(j-y)*64+38+get_symbol_offset_y(symbolcount),0,0,0,255);
                            symbolcount++;
                        }
                        if (gs.units[k].flags & UNIT_FLAG_INFILTRATOR) {
                            // boxed SOF for special operations forces, probably
                            put_text_at((i-x)*64+16,(j-y)*64+24,"SOF");
                            symbolcount++;
                        }
                        if (gs.units[k].flags & UNIT_FLAG_MECHANIZED) {
                            // vertical line
                            lineRGBA(MAIN_SCREEN,(i-x)*64+20,(j-y)*64+16,(i-x)*64+20,(j-y)*64+48,0,0,0,255);
                        }
                        if (gs.units[k].flags & UNIT_FLAG_MISSILE) {
                            // two chevrons in the middle
                            // chevron 1
                            lineRGBA(MAIN_SCREEN,(i-x)*64+32+get_symbol_offset_x(symbolcount),(j-y)*64+28+get_symbol_offset_y(symbolcount),
                                                 (i-x)*64+28+get_symbol_offset_x(symbolcount),(j-y)*64+32+get_symbol_offset_y(symbolcount),0,0,0,255);
                            lineRGBA(MAIN_SCREEN,(i-x)*64+32+get_symbol_offset_x(symbolcount),(j-y)*64+28+get_symbol_offset_y(symbolcount),
                                                 (i-x)*64+36+get_symbol_offset_x(symbolcount),(j-y)*64+32+get_symbol_offset_y(symbolcount),0,0,0,255);
                            // chevron 2
                            lineRGBA(MAIN_SCREEN,(i-x)*64+32+get_symbol_offset_x(symbolcount),(j-y)*64+30+get_symbol_offset_y(symbolcount),
                                                 (i-x)*64+28+get_symbol_offset_x(symbolcount),(j-y)*64+34+get_symbol_offset_y(symbolcount),0,0,0,255);
                            lineRGBA(MAIN_SCREEN,(i-x)*64+32+get_symbol_offset_x(symbolcount),(j-y)*64+30+get_symbol_offset_y(symbolcount),
                                                 (i-x)*64+36+get_symbol_offset_x(symbolcount),(j-y)*64+34+get_symbol_offset_y(symbolcount),0,0,0,255);
                            symbolcount++;
                        }
                        // scout already handled
                        if (gs.units[k].flags & UNIT_FLAG_SETTLER) {
                            // Boxed SET? or maybe a little housey
                            //put_text_at((i-x)*64+16,(j-y)*64+24,"SET");
                            // chevron
                            lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+24,(i-x)*64+28,(j-y)*64+28,0,0,0,255);
                            lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+24,(i-x)*64+36,(j-y)*64+28,0,0,0,255);
                            // box
                            rectangleRGBA(MAIN_SCREEN,(i-x)*64+28,(j-y)*64+28,(i-x)*64+36,(j-y)*64+36,0,0,0,255);
                            symbolcount++;
                        }
                        if (gs.units[k].flags & UNIT_FLAG_STEALTH) {
                            // EW in middle for Electronic Warfare?
                        }
                        // a simple health bar
                        // now with more colours!
                        healthbar_length = (int)(63*((gs.units[k].hp*1.0)/(gs.units[k].maxhp*1.0)));
                        if (healthbar_length > 42) { r = 0; g = 200, b = 0; }
                        else if (healthbar_length > 21) { r = 255; g = 255, b = 0; }
                        else { r = 200; g = 0, b = 0; }
                        boxRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64,(i-x)*64+healthbar_length,(j-y)*64+5,r,g,b,255);
                        // unit flags can form the basis of unique designations
                        unit_flags_to_text(gs.units[k],temp);
                        put_text_at((i-x)*64,(j-y)*64+63,temp);
                        
                    }
                }
            }
        }
    }
    //int modx, mody; // modified x and y, for cursor printing
    //modx = (5)*64; // center of display
    //mody = (3)*64; // ''
    
    // cursor printing
    for (int i=x;i<x+10;i++) {
        for (int j=y;j<y+7;j++) {
            // is the cursor location on this spot?
            if (i==gs.selx && j == gs.sely) {
                // draw the rectangle in red
                rectangleRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64,(i-x)*64+63,(j-y)*64+63,255,0,0,255);
            }
        }
    }
    

    

    return 0;
}

//  7 1 5 
//  3 0 4 
//  6 2 8  

// returns the x offset for symbol placement
int get_symbol_offset_x(int count) {
    if (count == 1) return 0;
    else if (count == 2) return 0;
    else if (count == 3) return -12;
    else if (count == 4) return +12;
    else if (count == 5) return +12;
    else if (count == 6) return -12;
    else if (count == 7) return -12;
    else if (count == 8) return +12;
    return 0; // if count == 0
}
//  7 1 5 
//  3 0 4 
//  6 2 8 
// returns the x offset for symbol placement
int get_symbol_offset_y(int count) {
    if (count == 1) return -10;
    else if (count == 2) return +10;
    else if (count == 3) return 0;
    else if (count == 4) return 0;
    else if (count == 5) return -10;
    else if (count == 6) return +10;
    else if (count == 7) return -10;
    else if (count == 8) return +10;
    return 0; // if count == 0
}
