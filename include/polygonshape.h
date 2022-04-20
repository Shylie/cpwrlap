#ifndef CPWRLAP_POLYGONSHAPE_H
#define CPWRLAP_POLYGONSHAPE_H

#include "shape.h"

namespace cp
{
	class PolygonShape : public Shape
	{
	public:
		PolygonShape(Body*, int, cpVect*, cpTransform = cpTransformIdentity, cpFloat = 0);
		PolygonShape(Body*, cpFloat, cpFloat, cpFloat = 0);

		int getCount() const;

		cpVect getVertexLocal(int) const;
		cpVect getVertexWorld(int) const;

		cpFloat getRadius() const;

		virtual void draw(Color) const override;
	};
}

#endif//CPWRLAP_POLYGONSHAPE_H
