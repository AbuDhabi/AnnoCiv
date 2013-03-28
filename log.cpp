#include "header.h"
#include "globals.h"

int write_to_log (char * text) {
    FILE *fp; 
    // text dump
    fp=fopen("save//log.txt","a");
    if (fp!=0) {
        fwrite("lol",1,sizeof(text),fp);
        fclose(fp);
    } else {

        fprintf(stderr,"File not open. Could not log.");
        return 1; // error!
    }
    return 0;
}
