#include "header.h"
#include "globals.h"

/// TODO: Improve quality of generated syllables, as per Erik's suggestion

// makes a new 'language' - a list of syllables
Language create_language() {
    Language output;
    char temp[8], demp[8];
    temp[0] = 0;
    demp[0] = 0;
    char vowels[] = {'a','o','e','u','i','y'}; //6
    char consonants[] = {'p','f','g','c','r','l','s','n','t','h','d','q','j','k','x','b','m','w','v','z'}; //20
    int preconsonants, midvowels, postconsonants;
    int counter;
    for (int i=0;i<MAX_SYLLABLES;i++) {
        preconsonants = rand()%3; // 0-2
        midvowels = rand()%2+1; // 1-2
        postconsonants = rand()%3; // 0-2
        // 1-6
        counter = 0;
        for (int z=0;z<preconsonants;z++) {
            sprintf(demp,temp);
            snprintf(temp,8,"%s%c",demp,consonants[rand()%20]);
            counter++;
        }
        for (int z=0;z<midvowels;z++) {
            sprintf(demp,temp);
            snprintf(temp,8,"%s%c",demp,vowels[rand()%6]);
            counter++;
        }
        for (int z=0;z<postconsonants;z++) {
            sprintf(demp,temp);
            snprintf(temp,8,"%s%c",demp,consonants[rand()%20]);
            counter++;
        }
        //temp[counter] = NULL;
        sprintf(output.syllables[i].text,temp);
        //put_text_at(0,0,temp);
        //SDL_Flip(MAIN_SCREEN);
        //SDL_Delay(1000);
    }
    
    return output;
}

/// TODO: Make sure temp has enough space to actually hold all these syllables
/// otherwise things could get... dicey
void make_up_word(char * output, Language lang, int syllables) {
    char temp[80];
    sprintf(temp," ");
    for (int i=0;i<syllables;i++) {
        snprintf(temp,80,"%s%s",temp,lang.syllables[rand()%MAX_SYLLABLES].text);
    }
        
    sprintf(output,temp);
}

/// TODO: THIS IS A CRUDE HACK, improve it so it resembles a proper handling of the problem
void capitalize_first(char* inout) {
    inout[0] = inout[0]-32;
}
