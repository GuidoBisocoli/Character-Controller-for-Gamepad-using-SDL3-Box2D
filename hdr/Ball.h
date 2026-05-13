#pragma once

#include "box2d/id.h"
#include "box2d/types.h"

#include "Texture.h"

class Ball
{
	public:
		Ball();
		~Ball();

		enum kickType { tap, soft, strong };
		void kick(kickType t, b2Vec2 direction);

		b2Vec2 getPosition();
		void update();
		void draw();
	private:
		const float RADIUS = 0.2f;

		Texture texture;
		b2BodyId bodyId;

		float cooldownTimer = 1.f; // one kick per second
};