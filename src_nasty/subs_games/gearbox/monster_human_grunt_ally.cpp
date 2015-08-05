//===========================================
// Opposing Force: Subtitles MOD
// Content: HGrunt (Ally)
//===========================================

#ifdef SM_OPFORCE

/*
@PointClass base(Monster, Sequence) studio("models/hgrunt_opfor.mdl") = monster_grunt_ally_repel : "Human Grunt Ally (Repel)"
[
  spawnflags(Flags) =
  [
    32 : "SquadLeader" : 0
  ]
  netname(string) : "Squad Name"
  weapons(Choices) : "Weapons" : 3 =
  [
    1 : "9mmAR"
    3 : "9mmAR + HG"
    5 : "9mmAR + GL"
    8 : "Shotgun"
    10 : "Shotgun + HG"
    16 : "Saw"
  ]
  head(Choices) : "Heads" : -1 =
  [
    -1 : "Default"
    0 : "Gas Mask"
    1 : "Beret"
    2 : "Ops Mask"
    3 : "Bandana White"
    4 : "Bandana Black"
  ]
]

@PointClass base(Monster, Sequence) studio("models/hgrunt_opfor.mdl") = monster_human_grunt_ally : "Human Grunt Ally (camo)" 
[
    netname(string) : "Squad Name"
    
    spawnflags(Flags) =
    [
        32 : "SquadLeader" : 0
    ]

    weapons(Choices) : "Weapons" : 3 =
    [
        0 : "None"
        1 : "9mmAR"
        3 : "9mmAR + HG"
        5 : "9mmAR + GL"
        8 : "Shotgun"
        10 : "Shotgun + HG"
        16 : "Saw"
    ]

    head(Choices) : "Heads" : -1 =
    [
        -1 : "Default"
         0 : "Gas Mask"
         1 : "Beret"
         2 : "Ops Mask"
         3 : "Bandana White"
         4 : "Bandana Black"
         5 : "MP"
         6 : "Major"
         7 : "Beret (Black)"
    ]
]


@PointClass base(Targetname,Appearflags,RenderFields, Sequence) studio("models/hgrunt_opfor.mdl") = monster_human_grunt_ally_dead : "Dead Human Grunt Ally" 
[
      pose(Choices) : "Pose" : 0 =
	[
		0 : "On stomach"
		1 : "On side"
		2 : "Seated"
		3 : "Dead On Back"
		4 : "Dead On Stomach"
		5 : "Head Crabbed"
	]

	weapons(Choices) : "Weapons" : 1 =
	[
		0 : "None"
		1 : "9mmAR"
		8 : "Shotgun"
		16 : "Saw"
	]

	head(Choices) : "Heads" : 0 =
	[
		0 : "Gas Mask"
		1 : "Beret"
		2 : "Ops Mask"
		3 : "Bandana White"
		4 : "Bandana Black"
		5 : "MP"
	]
]
*/

#endif