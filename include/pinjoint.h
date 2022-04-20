#ifndef CPWRLAP_PINJOINT_H
#define CPWRLAP_PINJOINT_H

#include "constraint.h"

namespace cp
{
	class Body;

	class PinJoint : public Constraint
	{
	public:
		PinJoint(Body*, Body*, cpVect, cpVect);
		PinJoint(Body*, Body*, cpFloat);

		cpVect getAnchorALocal() const;
		cpVect getAnchorBLocal() const;

		void setAnchorALocal(cpVect);
		void setAnchorBLocal(cpVect);

		cpVect getAnchorAWorld() const;
		cpVect getAnchorBWorld() const;

		void setAnchorAWorld(cpVect);
		void setAnchorBWorld(cpVect);

		cpFloat getDistance() const;
		void setDistance(cpFloat);

		virtual void draw(Color) const override;
	};
}

#endif//CPWRLAP_PINJOINT_H
