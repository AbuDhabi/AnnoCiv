#ifndef LANGUAGE_H_INCLUDED
#define LANGUAGE_H_INCLUDED

#define MAX_SYLLABLES 255

typedef struct Syllable {
    char text[8];
    
} Syllable;

typedef struct Language {
    Syllable syllables[MAX_SYLLABLES];
    
} Language;

#endif // LANGUAGE_H_INCLUDED

/*
Languages
   1. Make list of syllables.
   2. For each civilization, randomly select a number of syllables.
   3. Use the civ's syllables to make words. Different civs have different sets.
*/
