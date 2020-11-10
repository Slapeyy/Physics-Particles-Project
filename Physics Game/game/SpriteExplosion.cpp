#include "stdafx.h"
#include "SpriteExplosion.h"

CSpriteExplosion::CSpriteExplosion(CVector v, float vmax, float hue, float brightness, long time)
: CSprite(v, 10, 10, time)
{
	SetState(1);	// state=1 says particles are visible

	// create particles...
	m_n = 600;
	m_particles = new PARTICLE[m_n];
	memset(m_particles, 0, m_n * sizeof(PARTICLE));

	// initialisation of the individual particles
	for (int i = 0; i < m_n; i++)
	{
		// calculate runaway velocity
		float phi = acos(2 * (float)rand()/(float)RAND_MAX - 1);
		float lambda = (float)M_PI * 2.f * (float)rand()/(float)RAND_MAX;
		float vvar = 0.1f;
		float v = vmax * (1 - vvar + vvar * (float)rand()/(float)RAND_MAX);

		m_particles[i].vel = CVector3D(
			v * sin(phi) * cos(lambda),
			v * cos(phi),
			v * sin(phi) * sin(lambda));
	}

	// initialisation of the tail
	m_i = 0;

	// colour
	m_hue = hue;
	m_brightness = brightness;
}

CSpriteExplosion::~CSpriteExplosion()
{
	delete [] m_particles;
}

void CSpriteExplosion::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	CSprite::OnUpdate(time, deltaTime);

	if (!GetState()) return;

	// Fade all particles (decrease brightness)
	m_brightness -= 0.01f;
	if (m_brightness <= 0) 
	{
		m_brightness = 0;
		SetState(0);	// state=1 says particles are visible
		return;
	}

	// update particles
	m_i = (m_i + 1) % PARTICLE::N;
	int maxx = 0, maxy = 0;
	for (int i = 0; i < m_n; i++)
	{
		CVector3D vel = m_particles[i].vel;

		// apply air resistance
		float v = Length(vel);
		v -= v * v * 0.0001f;
		vel = Normalise(vel) * v;

		// vector equation for generating a vortex
		CVector3D vorvel(-m_particles[i].pos[m_i].m_y, m_particles[i].pos[m_i].m_x, 0);
		vorvel.Normalise();
		vorvel *=  6; // change these values for some funky effects!!

		vel += vorvel;

		// apply gravitation
		//vel += (float)deltaTime * CVector3D(0.f, -0.04f, 0.f);

		// update velocity
		m_particles[i].vel = vel;

		// update position
		int prev_i = (m_i + PARTICLE::N - 1) % PARTICLE::N;
		m_particles[i].pos[m_i] = m_particles[i].pos[prev_i] + vel * (float)deltaTime / 1000.f;
		maxx = (int)max(maxx, abs(m_particles[i].pos[m_i].m_x));
		maxy = (int)max(maxy, abs(m_particles[i].pos[m_i].m_y));
	}
	SetSize((float)min(maxx+maxx+2, 1600), (float)min(maxy+maxy+2, 1200));
}

void CSpriteExplosion::OnPrepareGraphics(CGraphics *pG)
{
	if (m_pGraphics != NULL) 
		delete m_pGraphics;
	m_pGraphics = new CGraphics((int)GetWidth(), (int)GetHeight(), 32, 0xff0000, 0xff00, 0xff, 0);
	m_pGraphics->SetColorKey(CColor::Black());
}

void CSpriteExplosion::OnDraw(CGraphics *g)
{
	g->Clear(CColor::Black());
	if (!GetState()) return;

	// draw particles
	CVector offset(g->GetWidth() / 2, g->GetHeight() / 2);
	for (int i = 0; i < m_n; i++)
	{
		// draw the forehead
		g->FillCircle(offset + m_particles[i].pos[m_i].vec2D(), 1, CColor::HSB(m_hue, 1.0f, m_brightness));

		// draw the tail
		int n = PARTICLE::N;
		for (int j = 1; j < n; j++)
			g->DrawLine(
				offset + m_particles[i].pos[(j + m_i) % n].vec2D(), 
				offset + m_particles[i].pos[(j + 1 + m_i) % n].vec2D(), 
				CColor::HSB(m_hue, 1.0, m_brightness * ((float)j / n)));
	}
}
