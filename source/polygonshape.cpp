#include "polygonshape.h"
#include "body.h"

namespace cp
{
	PolygonShape::PolygonShape(Body* body, int numVertices, cpVect* vertices, cpTransform transform, cpFloat radius) : Shape(cpPolyShapeNew(*body, numVertices, vertices, transform, radius)) { }
	PolygonShape::PolygonShape(Body* body, cpFloat width, cpFloat height, cpFloat radius) : Shape(cpBoxShapeNew(*body, width, height, radius)) { }

	int PolygonShape::getCount() const { return cpPolyShapeGetCount(shape); }

	cpVect PolygonShape::getVertexLocal(int index) const { return cpPolyShapeGetVert(shape, index); }
	cpVect PolygonShape::getVertexWorld(int index) const { return cpBodyLocalToWorld(cpShapeGetBody(shape), cpPolyShapeGetVert(shape, index)); }

	cpFloat PolygonShape::getRadius() const { return cpPolyShapeGetRadius(shape); }

	void PolygonShape::draw(Color color) const
	{
		int count = getCount();
		for (int i = 0; i < count; i++)
		{
			cpVect current = getVertexWorld(i);
			cpVect next = getVertexWorld((i + 1) % count);
			DrawLineEx(Vector2{ current.x, current.y }, Vector2{ next.x, next.y }, 1, color);
		}
	}
}
