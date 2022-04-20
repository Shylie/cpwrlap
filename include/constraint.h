#ifndef CPWRLAP_CONSTRAINT_H
#define CPWRLAP_CONSTRAINT_H

#include <chipmunk.h>
#include <raylib.h>

namespace cp
{
	class Body;

	class Constraint
	{
	protected:
		Constraint(cpConstraint*);

		cpConstraint* constraint;
		void* userData;

	public:
		Constraint(const Constraint&) = delete;
		Constraint& operator=(const Constraint&) = delete;

		virtual ~Constraint() = default;

		operator cpConstraint*() const;

		Body* getBodyA() const;
		Body* getBodyB() const;

		cpFloat getMaxForce() const;
		void setMaxForce(cpFloat);

		cpFloat getErrorBias() const;
		void setErrorBias(cpFloat);

		cpFloat getMaxBias() const;
		void setMaxBias(cpFloat);

		bool shouldCollideBodies() const;
		void setShouldCollideBodies(bool);

		void* getUserData() const;
		void setUserData(void*);

		cpFloat getImpulse();

		virtual void draw(Color) const = 0;
	};
}

#endif//CPWRLAP_CONSTRAINT_H
