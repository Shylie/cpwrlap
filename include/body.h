#ifndef CPWRLAP_BODY_H
#define CPWRLAP_BODY_H

#include <chipmunk.h>

namespace cp
{
	class Body
	{
	private:
		cpBody* body;
		void* userData;

	public:
		Body(cpFloat, cpFloat);
		explicit Body(cpBody*);

		Body(const Body&) = delete;
		Body& operator=(const Body&) = delete;

		operator cpBody*() const;

		cpBodyType getType() const;
		void setType(cpBodyType);

		cpFloat getMass() const;
		void setMass(cpFloat);

		cpFloat getMoment() const;
		void setMoment(cpFloat);

		cpVect getPosition() const;
		void setPosition(cpVect);

		cpVect getCenterOfGravity() const;
		void setCenterOfGravity(cpVect);

		cpVect getVelocity() const;
		void setVelocity(cpVect);

		cpVect getForce() const;
		void setForce(cpVect);

		cpFloat getAngle() const;
		void setAngle(cpFloat);

		cpFloat getAngularVelocity() const;
		void setAngularVelocity(cpFloat);

		cpFloat getTorque() const;
		void setTorque(cpFloat);

		cpVect getRotation() const;

		void applyForce(cpVect);
		void applyImpulse(cpVect);

		void applyForceWorld(cpVect, cpVect);
		void applyForceLocal(cpVect, cpVect);
		void applyImpulseWorld(cpVect, cpVect);
		void applyImpulseLocal(cpVect, cpVect);

		void* getUserData() const;
		void setUserData(void*);
	};
}

#endif//CPWRLAP_BODY_H
