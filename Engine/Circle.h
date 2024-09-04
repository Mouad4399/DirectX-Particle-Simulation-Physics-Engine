#pragma once

#include "Colors.h"
#include "Graphics.h"
class Circle {

public:
	int circleSize = 10;
	Color rgb = { 255,255,255 };
	double x = 10;
	double y = 300;
	double vx = 5;
	double vy = 0;


	bool inhibitUp = false;
	bool inhibitDown = false;
	bool inhibitLeft = false;
	bool inhibitRight = false;

	bool buttonIsHold = true;
	
	void Update();
	void Draw(Graphics & gfx);

};