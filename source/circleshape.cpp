#include "circleshape.h"
#include "body.h"

namespace cp
{
	CircleShape::CircleShape(Body* body, cpFloat radius, cpVect offset) : Shape(cpCircleShapeNew(*body, radius, offset)) { }

	cpVect CircleShape::getOffsetLocal() const { return cpCircleShapeGetOffset(shape); }
	cpVect CircleShape::getOffsetWorld() const { return cpBodyLocalToWorld(cpShapeGetBody(shape), cpCircleShapeGetOffset(shape)); }

	cpFloat CircleShape::getRadius() const { return cpCircleShapeGetRadius(shape); }

	void CircleShape::draw(Color color) const
	{
		cpVect position = getOffsetWorld();
		cpFloat radius = getRadius();
		DrawRing(Vector2{ static_cast<float>(position.x), static_cast<float>(position.y) }, radius - 1.5f, radius, 0, 360, 36, color);
	}
}