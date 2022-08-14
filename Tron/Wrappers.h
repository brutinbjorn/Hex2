#pragma once
//#include <SDL_rect.h>
#include <SDL.h>

#include "glm/glm.hpp"

#include "ENUMS.h"

//struct WRect
//{
//	WRect(SDL_Rect rect) : m_rect(rect) {};
//	SDL_Rect m_rect;
//};

//returns non zero if there is overlap
//direction is relevent to a
//char IsRectsOverLapping(SDL_Rect a,SDL_Rect b)
//{
//	char overlap = 0;
//	glm::ivec2 Cube1TL = { a.x,a.y };
//	glm::ivec2 Cube1BR = { a.x + a.w,a.y + a.h };
//
//	glm::ivec2 Cube2TL = { b.x,b.y };
//	glm::ivec2 Cube2BR = { b.x + b.w, b.y + b.h };
//
//	if ((Cube1TL.x <= Cube2BR.x && Cube1BR.x >= Cube2TL.x) && (Cube1TL.y <= Cube2BR.y && Cube1BR.y >= Cube2TL.y))
//	{
//		if(Cube1TL.x <= Cube2BR.x) overlap += DIRECTION_LEFT;
//		if(Cube1BR.x >= Cube2TL.x) overlap += DIRECTION_RIGHT;
//		if (Cube1TL.y <= Cube2BR.y) overlap += DIRECTION_UP;
//		if (Cube1BR.y >= Cube2TL.y) overlap += DIRECTION_DOWN;
//		//m_gotHit = true;
//		return overlap;
//	}
//	return false;
//	
//}