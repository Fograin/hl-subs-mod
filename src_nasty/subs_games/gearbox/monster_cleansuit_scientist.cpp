//===========================================
// Opposing Force: Subtitles MOD
// Content: Cleansuit Scientist
//===========================================

#ifdef SM_OPFORCE

/*
@PointClass base(Monster, TalkMonster, Sequence) studio("models/cleansuit_scientist.mdl") = monster_cleansuit_scientist : "Cleansuit Scientist" 
[
    body(Choices) : "Body" : -1 =
    [
        -1 : "Random"
        0 : "Glasses"
        1 : "Einstein"
        2 : "Luther"
        3 : "Slick"
    ]
]

@PointClass base(Targetname,Appearflags,RenderFields, Sequence) studio("models/cleansuit_scientist.mdl") = monster_cleansuit_scientist_dead : "Dead Cleansuit Scientist" 
[
  body(Choices) : "Body" : -1 =
  [
    -1 : "Random"
    0 : "Glasses"
    1 : "Einstein"
    2 : "Luther"
    3 : "Slick"
  ]
      pose(Choices) : "Pose" : 0 =
  [
    0 : "On back"
    1 : "On Stomach"
    2 : "Sitting"
    3 : "Hanging"
    4 : "Table1"
    5 : "Table2"
    6 : "Table3"
    7 : "Hi Mike!"
    8 : "Dead Against Wall"
  ]
]

@PointClass base(Monster, Sequence) studio("models/cleansuit_scientist.mdl") = monster_sitting_cleansuit_scientist : "Sitting Cleansuit Scientist" 
[
      body(Choices) : "Body" : -1 =
  [
    -1 : "Random"
    0 : "Glasses"
    1 : "Einstein"
    2 : "Luther"
    3 : "Slick"
  ]
]
*/

#endif