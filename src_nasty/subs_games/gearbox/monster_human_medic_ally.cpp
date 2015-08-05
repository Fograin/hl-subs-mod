//===========================================
// Opposing Force: Subtitles MOD
// Content: HGrunt (Ally, Medic)
//===========================================

#ifdef SM_OPFORCE

/*
@PointClass base(Monster, Sequence) studio("models/hgrunt_medic.mdl") = monster_human_medic_ally : "Medic" 
[
    netname(string) : "Squad Name"
    
    spawnflags(Flags) =
    [
        32 : "SquadLeader" : 0
    ]

    head(Choices) : "Heads" : -1 =
    [
       -1 : "Random"
        0 : "White"
        1 : "Black"
    ]

    weapons(Choices) : "Weapons" : 2 =
    [
	  0 : "None"
        1 : "Desert Eagle"
        2 : "9mm Handgun"
        4 : "Hypodermic Needle"
    ]
]
*/

#endif