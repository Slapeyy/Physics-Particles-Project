#pragma once

#include "Vector3D.h"

struct PARTICLE
{
	static const int N = 4;		// length of a "tail"
	CVector3D pos[N];			// position
	CVector3D vel;				// velocity
};

struct Vortex
{
	float posX;
	float posY;
	float speed;
	float scale;
};

class CSpriteExplosion : public CSprite
{
	int m_n;				// number of particles
	PARTICLE *m_particles;	// velocity - for each particle
	int m_i;				// current index to m_particles

	float m_hue;			// colour hue
	float m_brightness;		// colour brightness

public:
	CSpriteExplosion(CVector v, float vmax, float hue, float brightness, long time);
	virtual ~CSpriteExplosion();

protected:
	virtual void OnUpdate(Uint32 time, Uint32 deltaTime);
	virtual void OnPrepareGraphics(CGraphics *pG = NULL);
	virtual void OnDraw(CGraphics *g);
};
