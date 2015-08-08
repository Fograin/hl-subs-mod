//===========================================
// Opposing Force: Subtitles MOD
// Content: Visible item entities
//===========================================

#ifdef SM_OPFORCE

/*
@PointClass base(Targetname) size(-4 -4 -4, 4 4 4) color(200 100 50) = info_displacer_xen_target : "Displacer XEN Target" []
@PointClass base(Targetname) size(-4 -4 -4, 4 4 4) color(200 100 50) = info_displacer_earth_target : "Displacer EARTH Target" []
@PointClass base(Targetname, Target) = info_pitworm_steam_lock : "Pitworm Steam Lock" []

@PointClass base(Weapon, Targetx) = item_generic : "Generic scenery item"
[
	model(studio) : "Model" : "models/egg.mdl"
	sequencename(string) : "Sequence Name" : "idle"
	skin(integer) : "Skin" : 0
	body(integer) : "Body" : 0
]

@PointClass base(Weapon, Targetx) size(-16 -16 0, 16 16 36) = item_nuclearbomb : "Nuclear Bomb"
[
      initialstate(integer) : "Initial State" : 0
	wait(integer) : "Wait" : 1
]


@PointClass base(Weapon, Targetx, RenderFields) studio("models/W_saw_clip.mdl") = ammo_556 : "M249 Ammo" []
@PointClass base(Weapon, Targetx, RenderFields) studio("models/w_m40a1clip.mdl") = ammo_762 : "Sniper Ammo" []

//Spore ammo orientation refers to the direction that the base of the plant faces
@PointClass base(Weapon, Targetx, RenderFields) studio("models/spore_ammo.mdl") = ammo_spore : "Spore" []
*/

#endif