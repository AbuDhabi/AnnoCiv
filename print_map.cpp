#include "header.h"
#include "globals.h"

int print_map(int x,int y) {
    for (int i=x;i<x+10;i++) {
        for (int j=y;j<y+7;j++) {
            // tiles
            print_image_at((i-x)*64,(j-y)*64,BITMAPS[gs.gm.tiles[i][j]]);
            // any river on the tile?
            if (gs.gm.rivers[i][j] == 1) { // danger! array access not sanitized!
                int done=0;
                if (gs.gm.rivers[i-1][j-1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if (gs.gm.rivers[i][j-1] == 1)  {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,150,255);done++;}
                if (gs.gm.rivers[i+1][j-1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,150,255);done++;}
                if (gs.gm.rivers[i-1][j] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,150,255);done++;}
                if (gs.gm.rivers[i+1][j] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if (gs.gm.rivers[i-1][j+1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if (gs.gm.rivers[i][j+1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if (gs.gm.rivers[i+1][j+1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,150,255); done++;}
                if (done == 0) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+16,(i-x)*64+48,(j-y)*64+48,0,0,150,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+48,(j-y)*64+16,(i-x)*64+16,(j-y)*64+48,0,0,150,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+16,(i-x)*64+32,(j-y)*64+48,0,0,150,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+32,(i-x)*64+48,(j-y)*64+32,0,0,150,255);
                }
            }
            // any road on the tile?
            if (gs.gm.roads[i][j] == 1) { // danger! array access not sanitized!
                int done=0;
                if (gs.gm.roads[i-1][j-1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (gs.gm.roads[i][j-1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (gs.gm.roads[i+1][j-1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (gs.gm.roads[i-1][j] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (gs.gm.roads[i+1][j] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+32,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (gs.gm.roads[i-1][j+1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (gs.gm.roads[i][j+1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (gs.gm.roads[i+1][j+1] == 1) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+63,(j-y)*64+63,(i-x)*64+32,(j-y)*64+32,0,0,0,255); done++;}
                if (done == 0) {
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+16,(i-x)*64+48,(j-y)*64+48,0,0,0,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+48,(j-y)*64+16,(i-x)*64+16,(j-y)*64+48,0,0,0,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+32,(j-y)*64+16,(i-x)*64+32,(j-y)*64+48,0,0,0,255);
                    lineRGBA(MAIN_SCREEN,(i-x)*64+16,(j-y)*64+32,(i-x)*64+48,(j-y)*64+32,0,0,0,255);
                }
            }
            // any city on the tile?
            for (int k=0;k<MAX_CITIES;k++) {
                if (i==gs.cities[k].x && j==gs.cities[k].y) {
                    print_image_at((i-x)*64,(j-y)*64,BITMAPS[IMG_STATIC_CITY]);
                }
            }
            
        }
    }
    

    return 0;
}
