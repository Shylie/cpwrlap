#ifndef CPWRLAP_CIRCLESHAPE_H
#define CPWRLAP_CIRCLESHAPE_H

#include "shape.h"

namespace cp
{
	class Body;

	class CircleShape : public Shape
	{
	public:
		CircleShape(Body*, cpFloat, cpVect);

		CircleShape(const CircleShape&) = delete;
		CircleShape& operator=(const CircleShape&) = delete;

		virtual ~CircleShape() = default;

		cpVect getOffsetLocal() const;
		cpVect getOffsetWorld() const;

		cpFloat getRadius() const;

		virtual void draw(Color) const override;
	};
}

#endif//CPWRLAP_CIRCLESHAPE_H
