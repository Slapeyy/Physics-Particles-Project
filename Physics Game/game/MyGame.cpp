#include "stdafx.h"
#include "MyGame.h"
#include "SpriteExplosion.h"

CMyGame::CMyGame(void)
{
	// TODO: add initialisation here
}

CMyGame::~CMyGame(void)
{
//	for each (CSprite *pSprite in m_sprites)
//		delete pSprite;
//	m_sprites.clear();
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	// generate explosions every 20th frame, on average
	if (rand() % 120 == 0)
	{
		// initialise a new explosion, on a random basis
		CVector pos(GetWidth() / 2, GetHeight() / 2);
		float vmax = (float)(rand() % 200);
		float hue = (float)(rand() % 360);
		m_sprites.push_back(new CSpriteExplosion(pos, vmax, hue, 1.0, GetTime()));
	}

	// update all explosions
	// remove explosions that have faded out

	for each (CSprite *pSprite in m_sprites)
	{
		pSprite->Update(GetTime());
		if (pSprite->GetState() == 0)
			pSprite->Delete();
	}
	m_sprites.remove_if(deleted);
}

void CMyGame::OnDraw(CGraphics* g)
{
	for each (CSprite *pSprite in m_sprites)
		pSprite->Draw(g);
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	StartGame();
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	CVector pos(x, y);
	float vmax = (float)(rand() % 100);
	float hue = (float)(rand() % 360);
	m_sprites.push_back(new CSpriteExplosion(pos, vmax, hue, 1.0, GetTime()));
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
