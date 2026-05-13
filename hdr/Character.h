#pragma once

#include "box2d/id.h"
#include "box2d/types.h"

#include "Texture.h"

class Gamepad;
class Ball;

class Character
{
	public:
		Character(b2Vec2 position);
		~Character();

		void update(Gamepad* gp, Ball* b);
		void draw();
	private:
		const int MAXSPEED = 120;
		const float RUN_MULTIPLIER = 1.4f;
		const float RADIUS = 0.3f;

		Texture texture;
		b2BodyId bodyId;

		b2Vec2 movement;
		float angle;
		void calculateAngle(b2Vec2 pos, b2Vec2 target);
};