/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include<iostream>
#include <cmath>
#include <ctime>
#include <algorithm> 
void collisionHandlerLoop(std::vector<Circle> & players, std::vector<Circle*>& combination, int start, int n);
void checkCollision(std::vector<Circle*>& comb);

void springHandlerLoop(std::vector<Circle> & players, std::vector<int>& combination, int start, int n);
void applySpring(std::vector<Circle> & players,std::vector<int>& comb);

void drawHandlerLoop(std::vector<Circle> & players, std::vector<int>& combination, int start, int n,Graphics &gfx);
void drawSpring(std::vector<Circle> & players, std::vector<int>& comb, Graphics &gfx);
#include <cmath>
const double PI = 3.141592653589793238463;

bool isInside(double x, double y, double i, double j, double r, int n) {

	// Helper lambda to compute atan2 (equivalent to T() in Desmos)
	auto T = [](double y, double x) {
		double at2 = atan2(y, x);
		//		std::cout<<"test angle : "<<(at2 > 0 ? at2 : (2*PI + at2))<<"\n";
		return (at2 > 0 ? at2 : (2 * PI + at2));
	};

	// Calculate common expressions
	double deltaX = x - i;
	double deltaY = y - j;
	double angle = T(deltaY, deltaX);
	double pi_over_n = PI / n;

	// Floor operations
	double term1 = floor((angle - r) / (2 * pi_over_n));
	double term2 = term1 + 1;

	// Cosine and Sine operations
	double cos1 = cos(term1 * 2 * pi_over_n + r);
	double cos2 = cos(term2 * 2 * pi_over_n + r);
	double sin1 = sin(term1 * 2 * pi_over_n + r);
	double sin2 = sin(term2 * 2 * pi_over_n + r);

	// Calculating the combined values
	double cos_sum = cos1 + cos2;
	double sin_sum = sin1 + sin2;

	// Calculate the square root term
	double sqrt_term = sqrt(pow(cos_sum, 2) + pow(sin_sum, 2));

	// Avoid division by zero by adding a small epsilon
	if (sqrt_term == 0) {
		sqrt_term = 1e-10;
	}

	// Calculate the main function value
	double numerator = deltaX * cos_sum + deltaY * sin_sum;
	double result = numerator / (sqrt_term);

	return (result - (sqrt_term / 2)*100) <= 1.27019e-005;
}
bool *TapplySpringEffect ;
bool *TdisplayEdges ;
bool *TdipslayConnections;
bool *TdisplayVertices ;

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{

	srand(time(NULL));
	for (Circle &i : players) {
		i.rgb = { 255,255,255 };
		i.x = (rand() % Graphics::ScreenWidth-1) + 1;
		i.y = (rand() % Graphics::ScreenHeight-1) + 1;
		i.vx = (rand() % 10) + 1;
		i.vy = (rand() % 10) + 1;
	}
	players[0].rgb = {0, 255, 0 };


	TapplySpringEffect=&(applySpringEffect);
	TdisplayEdges=&(displayEdges);
	TdipslayConnections=&(dipslayConnections);
	TdisplayVertices =& (displayVertices);


}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	Circle &p = players[0];
	players[0].rgb = { 0, 255, 0 };
	if (wnd.kbd.KeyIsPressed(VK_CONTROL)) {
		if (wnd.kbd.KeyIsPressed(VK_UP)) {
			p.circleSize += p.circleSize>=80 ?0:10;
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
			p.circleSize -= p.circleSize ==0 ? 0 : 10;
		}

	}
	else if (wnd.kbd.KeyIsPressed(VK_SHIFT)) {
		if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
			// if we are not holding
			//if (!inhibitDown) {
			p.vy += 1.5;

			//}
			//y += p.vy;

		}

		if (wnd.kbd.KeyIsPressed(VK_UP)) {

			//if ( !inhibitUp) {
			p.vy -= 1.5;


			//}
	//y += p.vy;
		}

		if (wnd.kbd.KeyIsPressed(VK_LEFT)) {

			//if (!inhibitLeft) {
			p.vx -= 1.5;

			//}
			//x += p.vx;
		}

		if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {

			//if ( !inhibitRight) {
			p.vx += 1.5;

			//}
			//x +=p.vx;

		}
	}
	else {

		if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
			// if we are not holding
			//if (!inhibitDown) {
				p.vy += 0.5;
			
			//}
			//y += p.vy;
		
		}

		if (wnd.kbd.KeyIsPressed(VK_UP)) {

			//if ( !inhibitUp) {
				p.vy -= 0.5;
			

			//}
	//y += p.vy;
		}

		if (wnd.kbd.KeyIsPressed(VK_LEFT)) {

			//if (!inhibitLeft) {
				p.vx -= 0.5;
	
			//}
			//x += p.vx;
		}
		
		if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		
			//if ( !inhibitRight) {
				p.vx += 0.5;
		
			//}
			//x +=p.vx;

		}

		
	}

	if (wnd.kbd.KeyIsPressed('S')) {
		applySpringEffect = !applySpringEffect;
	}
	if (wnd.kbd.KeyIsPressed('E')) {
		displayEdges = !displayEdges;
	}
	if (wnd.kbd.KeyIsPressed('C')) {
		dipslayConnections = !dipslayConnections;
	}
	if (wnd.kbd.KeyIsPressed('V')) {
		displayVertices = !displayVertices;
	}

	if (wnd.kbd.KeyIsPressed('N')) {
		Circle* a = new Circle;
		(*a).rgb = { 255,255,0 };
		(*a).x = (rand() % Graphics::ScreenWidth - 1) + 1;
		(*a).y = (rand() % Graphics::ScreenHeight - 1) + 1;
		(*a).vx = (rand() % 10) + 1;
		(*a).vy = (rand() % 10) + 1;

		players.push_back(*a);
		delete a;

	}
	if (wnd.kbd.KeyIsPressed('P')) {
		players.size()>2?players.pop_back():NULL;

	}


		double cx = 0;
		double cy = 0;
		for (Circle i : players) {
			cx += i.x;
			cy += i.y;
		}
		cx = cx / players.size();
		cy = cy / players.size();
		gfx.PutPixel(cx, cy, { 255,0,0 });


		double px = p.x;
		double py = p.y;
		double radius = 100;
		int n = players.size();

		double Base_at2 = atan2(0, radius);
		Base_at2 = (Base_at2 > 0 ? Base_at2 : (2 * PI + Base_at2));

		double pat2 = atan2(py - cy, px - cx);
		pat2 = (pat2 > 0 ? pat2 : (2 * PI + pat2));

		double r =pat2-Base_at2;

		if (wnd.mouse.LeftIsPressed()) {
			
			//double r = PI / 2;
			//for (double i = 0; i < 2 * PI; i = i + 0.0174533) {

			//	double deltaX = cos(i);
			//	double deltaY = sin(i);

			//	//		std::cout<<"my angle : "<<i<<"\n";

			//	double pi_over_n = PI / n;

			//	// Floor operations
			//	double term1 = floor((i - r) / (2 * pi_over_n));
			//	double term2 = term1 + 1;

			//	// Cosine and Sine operations
			//	double cos1 = cos(term1 * 2 * pi_over_n + r);
			//	double cos2 = cos(term2 * 2 * pi_over_n + r);
			//	double sin1 = sin(term1 * 2 * pi_over_n + r);
			//	double sin2 = sin(term2 * 2 * pi_over_n + r);

			//	// Calculating the combined values
			//	double cos_sum = (cos1 + cos2);
			//	double sin_sum = (sin1 + sin2);

			//	// Calculate the square root term
			//	double sqrt_term = sqrt(pow(cos_sum, 2) + pow(sin_sum, 2));

			//	double prod = (cos_sum*deltaX + sin_sum * deltaY) / sqrt_term;

			//	//		double sqrt_term = prod;
			//	//		std::cout<< "prod : "<< prod<<"\n";
			//	//		std::cout<< "required projection : "<< sqrt_term/2<<"\n";

			//	//		double res = isInside((sqrt_term*0.5/prod)*cos(i),(sqrt_term*0.5/prod)*sin(i), 0, 0, r, 6);

			//	//		std::cout<< "the prod test : "<<(sqrt(pow(cos_sum, 2) + pow(sin_sum, 2))/2)<< " | "<<prod<<"\n";
			//	//		double res = isInside((sqrt_term*0.5/prod)*cos(i) +cx,(sqrt_term*0.5/prod)*sin(i) +cy, cx, cy, r, 6);
			//	//std::cout << (sqrt_term*0.5 / prod)*cos(i) + cx << " : " << (sqrt_term*0.5 / prod)*sin(i) + cy << " ==> " << res << "\n";
			//	gfx.PutPixel((sqrt_term*0.5 / prod)*cos(i)*radius + cx, (sqrt_term*0.5 / prod)*sin(i)*radius + cy, { 255,0,0 });
			//}


			// check if the pressed mouse in inside

			for (Circle &i : players) {
				if ((std::sqrt(std::pow((i.x - wnd.mouse.GetPosX()), 2) + std::pow((i.y - wnd.mouse.GetPosY()), 2)) < i.circleSize) || (holdenItem == &i)) {
					//if (holdenItem == nullptr) {
					/*if (true) {

					}*/
					double norm = std::sqrt(std::pow((i.x - wnd.mouse.GetPosX()), 2) + std::pow((i.y - wnd.mouse.GetPosY()), 2));
					mouseX_hold = wnd.mouse.GetPosX();
					mouseY_hold = wnd.mouse.GetPosY();
					i.rgb = { 255,255,0 };

					i.vx = -(i.x - wnd.mouse.GetPosX()) / norm;
					i.vy = -(i.y - wnd.mouse.GetPosY()) / norm;
					i.x = wnd.mouse.GetPosX();
					i.y = wnd.mouse.GetPosY();
					holdenItem = &i;
					break;
				}

			}

			if ((holdenItem == nullptr)&& (applySpringEffect) &&( isInside(wnd.mouse.GetPosX(),wnd.mouse.GetPosY() , cx, cy, r, n)|| isMouseHoldingShape)) {
				gfx.PutPixel(cx, cy, { 0,255,0 });
				double norm = std::sqrt(pow(wnd.mouse.GetPosX() - cx, 2)+ pow(wnd.mouse.GetPosY() - cy, 2));
				for (Circle &i : players) {
					i.vx +=2* (wnd.mouse.GetPosX() - cx)/norm;
					i.vy += 2*(wnd.mouse.GetPosY() - cy)/norm;
				}
				isMouseHoldingShape = true;
			}
		}
		else {

			if (holdenItem != nullptr) {

			holdenItem->rgb = { 255,255,0};
				(*holdenItem).vx = -((*holdenItem).x - wnd.mouse.GetPosX());
				(*holdenItem).vy = -((*holdenItem).y - wnd.mouse.GetPosY());
				holdenItem = nullptr;
			}
			else if (isMouseHoldingShape) {
				double norm = std::sqrt(pow(wnd.mouse.GetPosX() - cx, 2) + pow(wnd.mouse.GetPosY() - cy, 2));

				for (Circle &i : players) {
					i.vx += 2 * (wnd.mouse.GetPosX() - cx) / norm;
					i.vy += 2 * (wnd.mouse.GetPosY() - cy) / norm;
				}
			}

			isMouseHoldingShape = false;

		}

	//collision
	std::vector<Circle *> comb;
	collisionHandlerLoop(players, comb, 0, 2);

	//temp test
	//o.vx = 0;
	//o.vy = 0;
	for (Circle &i : players) {
		i.x += i.vx;
		i.y += i.vy;
	}


	if (applySpringEffect==true) {
		//applySpring
		std::vector<int> comb0;
		springHandlerLoop(players, comb0, 0, 2);
	}




	//stopcollision
	//std::vector<Circle *> comb0;
	//stopCollisionHandlerLoop(players, comb0, 0, 2);





	/*
		p.x += p.vx;
	p.y += p.vy;

	
	*/
	//ox += ovx;
	//oy += ovy;





	for (Circle &i : players) {
		i.Update();
	}

	//p.Update();

	//object model
	/*
	if (oy - ocircleSize <= 1) {
		oy = ocircleSize + 1;
		ovy *= -0.5;
	}
	else if (oy + ocircleSize >= gfx.ScreenHeight - 1) {
		oy = gfx.ScreenHeight - 1 - ocircleSize;
		ovy *= -0.5;
	}
	if (ox - ocircleSize <= 1) {
		ox = ocircleSize + 1;
		ovx *= -0.5;
	}
	else if (ox + ocircleSize >= gfx.ScreenWidth - 1) {
		ox = gfx.ScreenWidth - 1 - ocircleSize;
		ovx *= -0.5;
	}
	*/
	


		
//		y +=vy;
		/*
			if (buttonIsHold) {

	}
	else {
		vx = 0;
		vy = 0;

	}
		
		*/




}

void checkCollision(std::vector<Circle*>& comb) {
	Circle & p = *comb[0];
	Circle & o = *comb[1];
	if (std::sqrt(std::pow(p.x-(o.x), 2) + std::pow(p.y -(o.y), 2)) <= p.circleSize + o.circleSize +1) {


	

		double collisionPower = std::sqrt(std::pow(p.x  -(o.x), 2) + std::pow(p.y-(o.y), 2));
		double normSpeed = std::sqrt(std::pow(p.vx, 2) + std::pow(p.vy, 2));
		double onormSpeed = std::sqrt(std::pow(o.vx, 2) + std::pow(o.vy, 2));
		//double 

		double collisionX = (p.x  -(o.x))*(1 / collisionPower);
		double collisionY = (p.y -(o.y))*(1 / collisionPower);


		// taking coordinats to point of collision
			// rolling back to collision point 
		p.x = p.x + collisionX*((-collisionPower + p.circleSize + o.circleSize + 1) / 2);
		p.y = p.y + collisionY*((-collisionPower + p.circleSize + o.circleSize + 1) / 2);
								
		o.x = o.x - collisionX*((-collisionPower + p.circleSize + o.circleSize + 1) / 2);
		o.y = o.y - collisionY*((-collisionPower + p.circleSize + o.circleSize + 1) / 2);


		/*
				x = x + collisionX;
		y = y + collisionY;

		ox = ox - collisionX;
		oy = oy - collisionY;
		*/

		double diffX = p.vx - o.vx;
		double diffY = p.vy - o.vy;

		o.vx = (o.vx + collisionX *(diffX * collisionX + diffY * collisionY) );
		o.vy = (o.vy + collisionY * (diffX * collisionX + diffY * collisionY));

		p.vx = (p.vx - collisionX * (diffX * collisionX +diffY * collisionY));
		p.vy = (p.vy - collisionY * (diffX * collisionX + diffY * collisionY));



	}


}
void collisionHandlerLoop(std::vector<Circle> & players,  std::vector<Circle *>& combination,int start,int n ) {
	if (combination.size() == n) {
		checkCollision(combination);
		return;
	}

	for (int i = start; i < players.size(); ++i) {
		combination.push_back(&players[i]);
		//players[0].y = 2;
		//combination[0]->y = 2;
		collisionHandlerLoop(players, combination, i + 1, n);
		combination.pop_back();
	}
}


void applySpring(std::vector<Circle> & players,std::vector<int> &comb) {
	Circle & p = players[comb[0]];
	Circle & o = players[comb[1]];

	// let's create a sping
	// let's assume that p is tied to o
	// so there is a phisical connection between them
	// so there is a specific distance that should not be exceeded 
	// let's say = 40
	const double PI = 3.141592653589793238463;

			double normSpeed = std::sqrt(std::pow(p.vx, 2) + std::pow(p.vy, 2));
		double onormSpeed = std::sqrt(std::pow(o.vx, 2) + std::pow(o.vy, 2));

	double springLength = 100 * 2* std::sin(PI*(comb[1]-comb[0])/players.size());
	// dont forget to make it up there 

	double power = 0.5;
	double lpower = 0.9;

	if (std::sqrt(std::pow(p.x - (o.x), 2) + std::pow(p.y - (o.y), 2)) > springLength) {
		double distance = std::sqrt(std::pow(p.x - (o.x), 2) + std::pow(p.y - (o.y), 2));
		double dX = (p.x - (o.x))*(1 / distance);
		double dY = (p.y - (o.y))*(1 / distance);
		double maxSpeed = 5;
		// remember to flip to - for p when doing p - o ,and + for o , accourding to math


		if ((p.vx* dX + p.vy *dY>=0)) {
			p.vx -= dX * (distance / springLength >= 1.3 ? lpower : power);
			p.vy -= dY * (distance / springLength >= 1.3 ? lpower : power);
		}
		else {
			p.vx -= dX * power;
			p.vy -= dY * power;
		}
		if ( (o.vx* dX + o.vy *dY <= 0) ) {

			o.vx += dX * (distance / springLength >= 1.3 ? lpower : power);
			o.vy += dY * (distance / springLength >= 1.3 ? lpower : power);
		}
		else {
			o.vx += dX * (power);
			o.vy += dY * ( power);
		}



	}
	else if (std::sqrt(std::pow(p.x - (o.x), 2) + std::pow(p.y - (o.y), 2)) < springLength ) {

		double distance = std::sqrt(std::pow(p.x - (o.x), 2) + std::pow(p.y - (o.y), 2));
		double dX = (p.x - (o.x))*(1 / distance);
		double dY = (p.y - (o.y))*(1 / distance);
		//p.vx += dX * (springLength - distance)* 0.01 ;
		//p.vy += dY * (springLength - distance)* 0.01 ;

		//o.vx -= dX * (springLength - distance)* 0.01 ;
		//o.vy -= dY * (springLength - distance)* 0.01 ;
		if ((p.vx* dX + p.vy *dY <= 0)) {
			p.vx += dX* (distance / springLength <= 0.3 ? lpower : power);
			p.vy += dY* (distance / springLength <= 0.3 ? lpower : power);
		}
		else {
			p.vx += dX * power/2;
			p.vy += dY * power/2;
		}
		if ( (o.vx* dX + o.vy *dY >= 0) ) {

			o.vx -= dX * (distance / springLength <= 0.3 ? lpower : power);
			o.vy -= dY * (distance / springLength <= 0.3 ? lpower : power);
		}
		else {
			o.vx -= dX * ( power/2);
			o.vy -= dY * (power/2);
		}


	}




}
void springHandlerLoop(std::vector<Circle> & players, std::vector<int>& combination, int start, int n) {
	if (combination.size() == n) {
		applySpring(players,combination);
		return;
	}

	for (int i = start; i < players.size(); ++i) {
		combination.push_back(i);
		//players[0].y = 2;
		//combination[0]->y = 2;
		springHandlerLoop(players, combination, i + 1, n);
		combination.pop_back();
	}
}


void drawSpring(std::vector<Circle> & players, std::vector<int>& comb, Graphics &gfx) {
	Circle & p = players[comb[0]];
	Circle & o = players[comb[1]];

	if (!*TdisplayEdges && (std::abs(comb[0] - comb[1]) == 1 || std::abs(comb[0] - comb[1]) == players.size() - 1)) {
		return;
	}

	if (!*TdipslayConnections && !(std::abs(comb[0] - comb[1]) == 1 || std::abs(comb[0] - comb[1]) == players.size() - 1)) {
		return;
	}


	// let's draw the spring 
	// let's define the spring vector
	double distance = std::sqrt(std::pow(p.x - (o.x), 2) + std::pow(p.y - (o.y), 2));
	double sX = (p.x - o.x) / distance;
	double sY = (p.y - o.y) / distance;

	
	Color rgb = !(std::abs(comb[0] - comb[1]) == 1 || std::abs(comb[0] - comb[1]) == players.size()- 1 )? Colors::Red : Colors::White;
	for (int i = 0; i < distance; ++i) {

		gfx.PutPixel(o.x + i * sX, o.y + i * sY, rgb);
	}

}
void drawHandlerLoop(std::vector<Circle> & players, std::vector<int>& combination, int start, int n,Graphics &gfx) {
	if (combination.size() == n) {
		drawSpring(players,combination,gfx);
		return;
	}

	for (int i = start; i < players.size(); ++i) {
		combination.push_back(i);
		//players[0].y = 2;
		//combination[0]->y = 2;
		drawHandlerLoop(players, combination, i + 1, n , gfx);
		combination.pop_back();
	}
}

void Game::ComposeFrame()
{
	
	const double PI = 3.141592653589793238463;



	if (displayVertices==true) {
		for (Circle &i : players) {
			i.Draw(gfx);
		}
	}



	//drawSpring
	std::vector<int> comb0;
	drawHandlerLoop(players, comb0, 0, 2,gfx);


	//p.Draw(gfx);
	/*
	
		gfx.PutPixel(x, y, 255, 255, 255);

	for (double i = 0; i < 2*PI; i=i+ 0.0174533) {

		gfx.PutPixel(x + std::cos(i)*circleSize, y - std::sin(i)*circleSize, { 255, 255, 0 });

	}
	
	*/


	/*
	gfx.PutPixel(ox, oy, 255, 0, 0);

	for (double i = 0; i < 2 * PI; i = i + 0.0174533) {

		gfx.PutPixel(ox + std::cos(i)*10, oy - std::sin(i)*10, 255, 0, 0);

	}
	*/

	




}
