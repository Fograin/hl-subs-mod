//===========================================
// Blue-Shift: Subtitles MOD
// Content: Visible environment/FX entities
//===========================================
#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "effects.h"
#include "weapons.h"


//////////////////////////
// env_warpball - entity 
// Written by: Fograin92
//////////////////////////

// env_warpball entity; when triggered-> it spawns alien-teleport-in-like effect including sprite, green beams and sound

/*
FGD ENTRY FROM blueshift.fgd file
@PointClass iconsprite("sprites/env_warpball.spr") base(Targetname, Target) size(-32 -32 -32, 32 32 32) color(0 255 0) = env_warpball : "Warp In Ball"
[
	spawnflags(flags) =
	[
		1: "Remove On fire" : 0
		2: "Kill Center" : 0
	]
	radius(string) : "Beam Radius" : "256"
	warp_target(string) : "Warp Target" : ""	<- Fograin92: I'm not sure what is this.
]
*/

// FGD Flags
#define SF_WARPBALL_ONCE	0x0001		// Remove On fire <- Kill entity when it was triggered and completed
#define SF_WARPBALL_KILLC	0x0002		// Kill Center <- I don't know, maybe kill "living" entity if it's inside that effect? 

class CWarpball : public CBaseDelay
{
public:
	void	Spawn( void );
	void	Precache( void );
	void	EXPORT FX_Think( void );
	void	Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );
	void	KeyValue( KeyValueData *pkvd );

	int		m_iLoop;
	int		m_iBeam;
	CBeam	*m_pBeam[24];
	float	m_flBeamTime[24];
	float	m_flStartTime;
	int		m_iRadius;
};

LINK_ENTITY_TO_CLASS( env_warpball, CWarpball );

void CWarpball::Precache( void )
{
	PRECACHE_MODEL( "sprites/Fexplo1.spr" );	// This should be perfect for "spawn-center"
	PRECACHE_MODEL( "sprites/lgtning.spr" );
	PRECACHE_SOUND( "debris/alien_teleport.wav" );
}

void CWarpball::Spawn( void )
{
	Precache();
}

void CWarpball::FX_Think( void )
{
	int i;
	float t = (gpGlobals->time - m_flStartTime);

	if (m_iBeam < 24)	// 24 Beams should be enough
	{
		CBeam *pBeam;
		TraceResult		tr;

		Vector vecSrc = pev->origin;
		Vector vecDir = Vector( RANDOM_FLOAT( -1.0, 1.0 ), RANDOM_FLOAT( -1.0, 1.0 ),RANDOM_FLOAT( -1.0, 1.0 ) );
		vecDir = vecDir.Normalize();
		UTIL_TraceLine( vecSrc, vecSrc + vecDir*m_iRadius, ignore_monsters, ENT(pev), &tr);

		// Did we hit anything with that trace?
		if (tr.flFraction != 1.0)
		{
			// Create the beam
			pBeam = CBeam::BeamCreate("sprites/lgtning.spr",200);
			pBeam->PointsInit( pev->origin, tr.vecEndPos );
			pBeam->SetColor( 50, 255, 80 );
			pBeam->SetNoise( 80 );
			pBeam->SetBrightness( 250 );
			pBeam->SetWidth( 20 );
			pBeam->SetScrollRate( 60 );

			m_flBeamTime[m_iBeam] = gpGlobals->time;
			m_pBeam[m_iBeam] = pBeam; // Beam created and added to the array
			m_iBeam++;

			// A little bit of sparks!
			UTIL_Sparks(tr.vecEndPos);	// Sparkling at the end of the beam

			DecalGunshot( &tr, BULLET_PLAYER_CROWBAR ); // Some decals :)

			// Dynamic world light (not really BS-like but it looks nice :D)
			MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, vecSrc );
				WRITE_BYTE(TE_DLIGHT);
				WRITE_COORD(vecSrc.x);	// X
				WRITE_COORD(vecSrc.y);	// Y
				WRITE_COORD(vecSrc.z);	// Z
				WRITE_BYTE( 10 );		// radius * 0.1 // was 8
				WRITE_BYTE( 50 );		// r
				WRITE_BYTE( 255 );		// g
				WRITE_BYTE( 80 );		// b
				WRITE_BYTE( 10 );		// time * 10
				WRITE_BYTE( 0 );		// decay * 0.1
			MESSAGE_END( );

			// Dynamic entity light
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_ELIGHT );
				WRITE_SHORT( entindex( ) );		// entity, attachment
				WRITE_COORD(vecSrc.x);	// X
				WRITE_COORD(vecSrc.y);	// Y
				WRITE_COORD(vecSrc.z);	// Z
				WRITE_COORD( pev->renderamt );	// radius
				WRITE_BYTE( 50 );		// r
				WRITE_BYTE( 255 );		// g
				WRITE_BYTE( 80 );		// b
				WRITE_BYTE( 2 );	// life * 10
				WRITE_COORD( 0 ); // decay
			MESSAGE_END();
		}
	}

	// Check if 1,5 sec passed
	if (t < 1.5)
	{
		/*
		CAPITAN! The beams are showing up too slow!!!
		- Decrease nextthink delay!
		BUT SIR! We're already at +0.1!
		- Change it to +0.01!!!
		SIR! THAT WILL OVERKILL CBaseDelay, IT'S NOT CONVENTIONAL-
		- TO HELL WITH CONVENTIONAL METHODS! DECREASE IT TO 0.01!
		*/
		pev->nextthink = gpGlobals->time + 0.01;
	}
	else
	{
		for (i = 0; i < m_iBeam; i++)
		{
			UTIL_Remove( m_pBeam[i] );
		}
		m_flStartTime = gpGlobals->time;
		m_iBeam = 0;
		SetThink( NULL );

		// Remove entity from the game, if flag "Remove On fire" is set
		if ( pev->spawnflags & SF_WARPBALL_ONCE )
			UTIL_Remove( this );
	}
}

void CWarpball::Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )
{
	EMIT_SOUND( edict(), CHAN_BODY, "debris/alien_teleport.wav", 1, ATTN_NORM );

	CSprite *pSprite = CSprite::SpriteCreate( "sprites/Fexplo1.spr", pev->origin, TRUE );
	pSprite->AnimateAndDie( RANDOM_FLOAT( 10.0, 15.0 ) ); // Sprite framerate, maybe with little variation?
	pSprite->SetTransparency(kRenderGlow, 90, 255, 130, 255, kRenderFxNoDissipation);

	SetThink( &CWarpball::FX_Think );
	pev->nextthink = gpGlobals->time + 0.01;
	m_flStartTime = gpGlobals->time;
}

void CWarpball::KeyValue( KeyValueData *pkvd )
{
	// If "radius" was set, use it as radius
	if (FStrEq(pkvd->szKeyName, "radius"))	
	{
		m_iRadius = atoi(pkvd->szValue);

		// Just to be sure
		if(m_iRadius < 1)
			m_iRadius = 128;

		pkvd->fHandled = TRUE;
	}
	else
		CBaseDelay::KeyValue( pkvd );
}

