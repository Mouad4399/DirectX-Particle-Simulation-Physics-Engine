/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Circle.h"
#include <vector>
class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/


	std::vector<Circle> players = std::vector<Circle>(2);

	//Circle &p =  players[0];
	//Circle &o= players[1];
public:
	bool applySpringEffect = false;
	bool displayEdges = false;
	bool dipslayConnections = false;
	bool displayVertices = true;

	bool isMouseHold = false;
	Circle* holdenItem = nullptr;

	double mouseX_hold;
	double mouseY_hold;

	bool isMouseHoldingShape = false;


	
	//p.rgb = { 255,255,0 };
	/*
		int circleSize = 10;
	double x = 10;
	double y = 300;
	double vx = 5;
	double vy = 0;
	*/

	/*
		int ocircleSize = 10;
	double ox =gfx.ScreenWidth-100;
	double oy = 300;
	double ovx = -5;
	double ovy = 0;
	*/
	// objects



	/*
	
		bool inhibitUp= false;
	bool inhibitDown= false;
	bool inhibitLeft= false;
	bool inhibitRight= false;

	bool buttonIsHold = true;
	*/

};