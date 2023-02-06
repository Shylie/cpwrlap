#include "segmentshape.h"
#include "body.h"

namespace cp
{
	SegmentShape::SegmentShape(Body* body, cpVect endA, cpVect endB, cpFloat radius) : Shape(cpSegmentShapeNew(*body, endA, endB, radius)) { }

	cpVect SegmentShape::getEndpointALocal() const { return cpSegmentShapeGetA(shape); }
	cpVect SegmentShape::getEndpointBLocal() const { return cpSegmentShapeGetB(shape); }

	cpVect SegmentShape::getEndpointAWorld() const { return cpBodyLocalToWorld(cpShapeGetBody(shape), cpSegmentShapeGetA(shape)); }
	cpVect SegmentShape::getEndpointBWorld() const { return cpBodyLocalToWorld(cpShapeGetBody(shape), cpSegmentShapeGetB(shape)); }

	cpVect SegmentShape::getNormal() const { return cpSegmentShapeGetNormal(shape); }

	cpFloat SegmentShape::getRadius() const { return cpSegmentShapeGetRadius(shape); }

	void SegmentShape::draw(Color color) const
	{
		cpVect a = getEndpointAWorld();
		cpVect b = getEndpointBWorld();
		cpFloat thickness = getRadius();
		DrawLineEx(
			Vector2{ static_cast<float>(a.x), static_cast<float>(a.y) },
			Vector2{ static_cast<float>(b.x), static_cast<float>(b.y) },
			thickness + 1, color
		);
	}
}
