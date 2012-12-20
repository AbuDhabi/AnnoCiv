#ifndef RESEARCH_H_INCLUDED
#define RESEARCH_H_INCLUDED

/// TODO: Implement specific techs and stuff
/// TODO: Decide on a formula for teching

typedef struct Research {
    int InfCom; // level
    float InfCom_progress; // progress towards next level, current level determines how much is needed
    int SocGov;
    float SocGov_progress;
    int ProEng;
    float ProEng_progress;
    int ComTra;
    float ComTra_progress;
    int AgrEne;
    float AgrEne_progress;
} Research;

#endif // RESEARCH_H_INCLUDED

/*
Technology akin to MoO and EU3
   Division into broad groups of techs, with numeric ratings. None of this specific tech tree stuff. 
   Bonus points if we can skip certain techs, so it's impossible to get them without trading/looting. 
   -Information & Communication - writing, printing, computers, networks, etc.
   -Society & Government - types of civics available, dealing with large empires, etc.
   -Military - weapons, tactics, doctrines, strategy, etc.
   -Production & Engineering - machines, robots, production, unit chassises, etc.
   -Commerce & Trade - making money, converting resources, trade, banking, etc.
   -Agriculture & Energy - resource extraction, farming, mining, energy collection, etc.
   I'm thinking of making it proportionally harder to advance to higher levels as other technologies 
   are left in the dirt, in a cliche move to discourage minmaxing. For example, if InfCom and AgrEne 
   are low, and you want to push ProdEng, you're going to have problems because you can't get good 
   automation software or high quality raw materials.
*/
