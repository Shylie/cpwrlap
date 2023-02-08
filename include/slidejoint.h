#ifndef CPWRLAP_SLIDEJOINT_H
#define CPWRLAP_SLIDEJOINT_H

#include "constraint.h"

namespace cp
{
	class Body;

	class SlideJoint : public Constraint
	{
	public:
		SlideJoint(Body*, Body*, cpVect anchorA, cpVect anchorB, cpFloat min, cpFloat max);
		SlideJoint(Body*, Body*, cpFloat min, cpFloat max);

		cpVect getAnchorALocal() const;
		cpVect getAnchorBLocal() const;

		void setAnchorALocal(cpVect);
		void setAnchorBLocal(cpVect);

		cpVect getAnchorAWorld() const;
		cpVect getAnchorBWorld() const;

		void setAnchorAWorld(cpVect);
		void setAnchorBWorld(cpVect);

		cpFloat getMin() const;
		void setMin(cpFloat);

		cpFloat getMax() const;
		void setMax(cpFloat);

		virtual void draw(Color) const override;
	};
}

#endif//CPWRLAP_SLIDEJOINT_H