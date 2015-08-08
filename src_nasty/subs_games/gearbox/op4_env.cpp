//===========================================
// Opposing Force: Subtitles MOD
// Content: Visible environment/FX entities
//===========================================

#ifdef SM_OPFORCE

/*

@PointClass base(Targetname) size(-16 -16 -16, 16 16 16) = env_blowercannon : "Blower Cannon"
[
  delay(string) : "Delay" : "0"
  zoffset(integer) : "Z Offset" : 0
  target(string) : "Target" : ""
  weaptype(choices) :"Weapon Type" : 1 =
  [
    1: "Spore (Rocket)"
    2: "Spore (Grenade)"
    3: "Shock Beam"
    4: "Displacer Ball"
  ]
  firetype(choices) :"Fire Type" : 1 =
  [
    1: "Toggle On/Off"
    2: "Fire When Triggered"
  ]
]

@PointClass base(Targetname) size(-16 -16 -16, 16 16 16) = env_electrified_wire : "Electrified Wire"
[
  segments(integer) : "Segments" : 16
  sparkfrequency(integer) : "Spark Frequency" : 3
  bodysparkfrequency(integer) : "Body Spark Frequency" : 3
  lightningfrequency(integer) : "Lightning Frequency" : 3
  xforce(integer) : "X Force" : 80000
  yforce(integer) : "Y Force" : 80000
  zforce(integer) : "Z Force" : 80000
  disable(choices) :"Disable Use" : 0 =
  [
    0: "Not Disabled"
    1: "Disabled"
  ]
  endingmodel(studio) : "Ending Model" : "models/wire_copper16.mdl"
  bodymodel(studio) : "Body Model" : "models/wire_black16.mdl"
]

@PointClass base(Targetname) size(-16 -16 -16, 16 16 16) = env_rope : "Rope"
[
  segments(integer) : "Segments" : 16
  disable(choices) :"Disable Use" : 0 =
  [
    0: "Not Disabled"
    1: "Disabled"
  ]
  endingmodel(studio) : "Ending Model" : "models/rope16.mdl"
  bodymodel(studio) : "Body Model" : "models/rope16.mdl"
]



@PointClass base(Targetname) size(-16 -16 -16, 16 16 16) color(0 128 255)= env_spritetrain : "Sprite Train"
[
  target(target_source) : "First stop target"
  model(sprite) : "Sprite Name" : "sprites/glow01.spr"
  speed(integer) : "Speed (units per second)" : 64
  scale(string) : "Sprite Scale"      
]


//
// FUNC ENTITIES
//

@SolidClass base(Target) = func_op4mortarcontroller : "Op4 Mortar Controller" 
[
    mortar_axis(Choices) : "Axis" : 0 =
    [
        0 : "Vertical"
        1 : "Horizontal"
    ]
]

@BaseClass base(Targetname, Target, RenderFields, Global) = BaseTankOF
[
  spawnflags(flags) =
  [
    1 : "Active" : 0
    16: "Only Direct" : 0
    32: "Controllable" : 0
  ]

  // Mainly for use with 1009 team settings (game_team_master)
  master(string) : "(Team) Master" 

  yawrate(string) : "Yaw rate" : "30"
  yawrange(string) : "Yaw range" : "180"
  yawtolerance(string) : "Yaw tolerance" : "15"
  pitchrate(string) : "Pitch rate" : "0"
  pitchrange(string) : "Pitch range" : "0"
  pitchtolerance(string) : "Pitch tolerance" : "5"
  barrel(string) : "Barrel Length" : "0"
  barrely(string) : "Barrel Horizontal" : "0"
  barrelz(string) : "Barrel Vertical" : "0"
  spritesmoke(string) : "Smoke Sprite" : ""
  spriteflash(string) : "Flash Sprite" : ""
  spritescale(string) : "Sprite scale" : "1"
  rotatesound(sound) : "Rotate Sound" : ""
  firerate(string) : "Rate of Fire" : "1"
  bullet_damage(string) : "Damage Per Bullet" : "0"
  persistence(string) : "Firing persistence" : "1"
  firespread(choices) : "Bullet accuracy" : 0 =
  [
    0: "Perfect Shot"
    1: "Small cone"
    2: "Medium cone"
    3: "Large cone"
    4: "Extra-large cone"
  ]
  minRange(string) : "Minmum target range" : "0"
  maxRange(string) : "Maximum target range" : "0"
  _minlight(string) : "Minimum light level"
  enemytype(Choices) : "Enemy Type" : 1 =
  [
    0: "Player"
    1: "Ally"
    2: "Random"
  ]
]

// Don't forget func_tankcontrols_of
@SolidClass base(BaseTankOF) = func_tank_of : "Brush Gun Turret" 
[
  bullet(choices) : "Bullets" : 0 = 
  [
    0: "None"
    1: "9mm"
    2: "MP5"
    3: "12mm"
  ]
]

@SolidClass = func_tankcontrols_of : "Tank controls"
[
  target(target_destination) : "Tank entity name"
]

// Don't forget func_tankcontrols_of
@SolidClass base(BaseTankOF) = func_tanklaser_of : "Brush Laser Turret" 
[
  laserentity(target_source) : "env_laser Entity"
]

// Don't forget func_tankcontrols
@SolidClass base(BaseTankOF) = func_tankrocket_of : "Brush Rocket Turret" []


// Don't forget func_tankcontrols
@SolidClass base(BaseTankOF) = func_tankmortar_of : "Brush Mortar Turret" 
[
  iMagnitude(Integer) : "Explosion Magnitude" : 100
]

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