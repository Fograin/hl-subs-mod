//===========================================
// Opposing Force: Subtitles MOD
// Content: Invisible trigger entities
//===========================================

#ifdef SM_OPFORCE

/*
@SolidClass base(Targetname,Target) = trigger_geneworm_hit : "Trigger GeneWorm Hit" 
[
  spawnflags(flags) = 
  [ 
    1: "Target Once" : 0 
    2: "Start Off" : 0
    8: "No clients" : 0
    16:"FireClientOnly" : 0
    32:"TouchClientOnly" : 0
  ]
  master(string) : "Master" 
  delay(string) : "Delay before trigger" : "0"
]

@PointClass base(Targetx, Targetname) = trigger_playerfreeze : "Trigger Player Freeze" []
@SolidClass base(Trigger) = trigger_xen_return : "Return To Earth (self-tele)" []
*/

#endif