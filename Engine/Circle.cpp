#include "Circle.h"
#include "Graphics.h"
#include <iostream>

void Circle::Update()
{



	/*
	bouncing effect :

	*/

	if (y - circleSize <= 1) {
		y = circleSize + 1;
		vy *= -0.6;
	}
	else if (y + circleSize >= Graphics::ScreenHeight - 1) {
		y = Graphics::ScreenHeight - 1 - circleSize;
		vy *= -0.6;
	}
	if (x - circleSize <= 1) {
		x = circleSize + 1;
		vx *= -0.6;
	}
	else if (x + circleSize >= Graphics::ScreenWidth - 1) {
		x = Graphics::ScreenWidth - 1 - circleSize;
		vx *= -0.6;
	}

}

void Circle::Draw(Graphics & gfx)
{
	constexpr double PI = 3.141592653589793238463;
	gfx.PutPixel(x, y, rgb);
	for (double i = 0; i < 2 * PI; i = i + 0.0174533) {

		gfx.PutPixel(x + std::cos(i)*circleSize, y + std::sin(i)*circleSize, rgb);

	}
}
