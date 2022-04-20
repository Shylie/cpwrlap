#ifndef CPWRLAP_SEGMENTSHAPE_H
#define CPWRLAP_SEGMENTSHAPE_H

#include "shape.h"

namespace cp
{
	class SegmentShape : public Shape
	{
	public:
		SegmentShape(Body*, cpVect, cpVect, cpFloat);

		cpVect getEndpointALocal() const;
		cpVect getEndpointBLocal() const;

		cpVect getEndpointAWorld() const;
		cpVect getEndpointBWorld() const;

		cpVect getNormal() const;

		cpFloat getRadius() const;

		virtual void draw(Color) const override;
	};
}

#endif//CPWRLAP_SEGMENTSHAPE_H
