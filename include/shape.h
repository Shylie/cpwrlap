#ifndef CPWRLAP_SHAPE_H
#define CPWRLAP_SHAPE_H

#include <chipmunk.h>
#include <raylib.h>

namespace cp
{
	class Body;

	class Shape
	{
	protected:
		Shape(cpShape*);

		cpShape* shape;
		void* userData;

	public:
		Shape(const Shape&) = delete;
		Shape& operator=(const Shape&) = delete;

		virtual ~Shape() = default;

		operator cpShape*() const;

		bool isSensor() const;
		void setSensor(bool);

		cpFloat getElasticity() const;
		void setElasticity(cpFloat);

		cpFloat getFriction() const;
		void setFriction(cpFloat);

		cpVect getSurfaceVelocity() const;
		void setSurfaceVelocity(cpVect);

		cpCollisionType getCollisionType() const;
		void setCollisionType(cpCollisionType);

		cpGroup getGroup() const;
		void setGroup(cpGroup);

		cpBitmask getCategories() const;
		void setCategories(cpBitmask);

		cpBitmask getMask() const;
		void setMask(cpBitmask);

		void* getUserData() const;
		void setUserData(void*);

		virtual void draw(Color) const = 0;
	};
}

#endif//CPWRLAP_SHAPE_H
