#include "space.h"
#include "body.h"
#include "constraint.h"
#include "shape.h"
#include "arbiter.h"

#include <algorithm>

static void ShapeFreeWrap(cpSpace* space, cpShape* shape, void*)
{
	cpSpaceRemoveShape(space, shape);
	cpShapeFree(shape);
}

static void PostShapeFree(cpShape* shape, cpSpace* space)
{
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)ShapeFreeWrap, shape, nullptr);
}

static void ConstraintFreeWrap(cpSpace* space, cpConstraint* constraint, void*)
{
	cpSpaceRemoveConstraint(space, constraint);
	cpConstraintFree(constraint);
}

static void PostConstraintFree(cpConstraint* constraint, cpSpace* space)
{
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)ConstraintFreeWrap, constraint, nullptr);
}

static void BodyFreeWrap(cpSpace* space, cpBody* body, void*)
{
	cpSpaceRemoveBody(space, body);
	cpBodyFree(body);
}

static void PostBodyFree(cpBody* body, cpSpace* space)
{
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)BodyFreeWrap, body, nullptr);
}

namespace cp
{
	Space::CallbackData& Space::setupCallbackData(cpCollisionHandler* key)
	{
		if (collisionCallbackData.find(key) == collisionCallbackData.end())
		{	
			CallbackData& cbd = collisionCallbackData[key];
			cbd.begin = nullptr;
			cbd.preSolve = nullptr;
			cbd.postSolve = nullptr;
			cbd.separate = nullptr;
			cbd.data = nullptr;
		}

		return collisionCallbackData[key];
	}

	int Space::collisionBeginFuncHelper(cpArbiter* arb, cpSpace* space, CallbackData* data)
	{
		if (data->begin)
		{
			return data->begin(arb, *reinterpret_cast<Space*>(cpSpaceGetUserData(space)), data->data);
		}
		else
		{
			return true;
		}
	}

	int Space::collisionPreSolveFuncHelper(cpArbiter* arb, cpSpace* space, CallbackData* data)
	{
		if (data->preSolve)
		{
			return data->preSolve(arb, *reinterpret_cast<Space*>(cpSpaceGetUserData(space)), data->data);
		}
		else
		{
			return true;
		}
	}

	void Space::collisionPostSolveFuncHelper(cpArbiter* arb, cpSpace* space, CallbackData* data)
	{
		if (data->postSolve) { data->postSolve(arb, *reinterpret_cast<Space*>(cpSpaceGetUserData(space)), data->data); }
	}

	void Space::collisionSeparateFuncHelper(cpArbiter* arb, cpSpace* space, CallbackData* data)
	{
		if (data->separate) { data->separate(arb, *reinterpret_cast<Space*>(cpSpaceGetUserData(space)), data->data); }
	}

	Space::Space() : space(cpSpaceNew()), staticBody(new Body(cpSpaceGetStaticBody(space))), data(nullptr)
	{
		cpSpaceSetUserData(space, this);
	}

	Space::~Space()
	{
		cpSpaceEachShape(space, (cpSpaceShapeIteratorFunc)PostShapeFree, space);
		cpSpaceEachConstraint(space, (cpSpaceConstraintIteratorFunc)PostConstraintFree, space);
		cpSpaceEachBody(space, (cpSpaceBodyIteratorFunc)PostBodyFree, space);


		for (Shape* shape : shapes)
		{
			delete shape;
		}
		shapes.clear();

		for (Constraint* constraint : constraints)
		{
			delete constraint;
		}
		constraints.clear();

		for (Body* body : bodies)
		{
			delete body;
		}

		delete staticBody;

		cpSpaceFree(space);
	}

	Space::operator cpSpace*() const { return space; }

	void* Space::getUserData() const { return data; }
	void Space::setUserData(void* data) { this->data = data; }

	Shape* Space::add(Shape* shape)
	{
		cpSpaceAddShape(space, *shape);
		shapes.push_back(shape);
		return shape;
	}

	Body* Space::add(Body* body)
	{
		cpSpaceAddBody(space, *body);
		bodies.push_back(body);
		return body;
	}

	Constraint* Space::add(Constraint* constraint)
	{
		cpSpaceAddConstraint(space, *constraint);
		constraints.push_back(constraint);
		return constraint;
	}

	void Space::remove(Shape* shape)
	{
		cpSpaceRemoveShape(space, *shape);
		delete shape;
		shapes.erase(std::find(shapes.begin(), shapes.end(), shape));
	}

	void Space::remove(Body* body)
	{
		cpSpaceRemoveBody(space, *body);
		delete body;
		bodies.erase(std::find(bodies.begin(), bodies.end(), body));
	}

	void Space::remove(Constraint* constraint)
	{
		cpSpaceRemoveConstraint(space, *constraint);
		delete constraint;
		constraints.erase(std::find(constraints.begin(), constraints.end(), constraint));
	}

	Body* Space::getStaticBody()
	{
		return staticBody;
	}

	cpVect Space::getGravity() const
	{
		return cpSpaceGetGravity(space);
	}

	void Space::setGravity(cpVect gravity)
	{
		cpSpaceSetGravity(space, gravity);
	}

	void Space::step(cpFloat timestep)
	{
		cpSpaceStep(space, timestep);
	}

	void Space::draw(Color shapesColor, Color constraintsColor) const
	{
		for (Constraint* constraint : constraints)
		{
			constraint->draw(constraintsColor);
		}

		for (Shape* shape : shapes)
		{
			shape->draw(shapesColor);
		}
	}

	void Space::setCollisionBeginFunc(cpCollisionType a, cpCollisionType b, CollisionBeginFunc begin)
	{
		cpCollisionHandler* h = cpSpaceAddCollisionHandler(space, a, b);
		CallbackData& cbd = setupCallbackData(h);
		cbd.begin = begin;
	}

	void Space::setCollisionPreSolveFunc(cpCollisionType a, cpCollisionType b, CollisionPreSolveFunc preSolve)
	{
		cpCollisionHandler* h = cpSpaceAddCollisionHandler(space, a, b);
		CallbackData& cbd = setupCallbackData(h);
		cbd.preSolve = preSolve;
	}

	void Space::setCollisionPostSolveFunc(cpCollisionType a, cpCollisionType b, CollisionPostSolveFunc postSolve)
	{
		cpCollisionHandler* h = cpSpaceAddCollisionHandler(space, a, b);
		CallbackData& cbd = setupCallbackData(h);
		cbd.postSolve = postSolve;
	}

	void Space::setCollisionSeparateFunc(cpCollisionType a, cpCollisionType b, CollisionSeparateFunc separate)
	{
		cpCollisionHandler* h = cpSpaceAddCollisionHandler(space, a, b);
		CallbackData& cbd = setupCallbackData(h);
		cbd.separate = separate;
	}

	void Space::setCollisionUserData(cpCollisionType a, cpCollisionType b, void* data)
	{
		cpCollisionHandler* h = cpSpaceAddCollisionHandler(space, a, b);
		CallbackData& cbd = setupCallbackData(h);
		cbd.data = data;
	}

	void Space::setWildcardCollisionBeginFunc(cpCollisionType a, CollisionBeginFunc begin)
	{
		cpCollisionHandler* h = cpSpaceAddWildcardHandler(space, a);
		CallbackData& cbd = setupCallbackData(h);
		cbd.begin = begin;
	}

	void Space::setWildcardCollisionPreSolveFunc(cpCollisionType a, CollisionPreSolveFunc preSolve)
	{
		cpCollisionHandler* h = cpSpaceAddWildcardHandler(space, a);
		CallbackData& cbd = setupCallbackData(h);
		cbd.preSolve = preSolve;
	}

	void Space::setWildcardCollisionPostSolveFunc(cpCollisionType a, CollisionPostSolveFunc postSolve)
	{
		cpCollisionHandler* h = cpSpaceAddWildcardHandler(space, a);
		CallbackData& cbd = setupCallbackData(h);
		cbd.postSolve = postSolve;
	}

	void Space::setWildcardCollisionSeparateFunc(cpCollisionType a, CollisionSeparateFunc separate)
	{
		cpCollisionHandler* h = cpSpaceAddWildcardHandler(space, a);
		CallbackData& cbd = setupCallbackData(h);
		cbd.separate = separate;
	}

	void Space::setWildcardCollisionUserData(cpCollisionType a, void* data)
	{
		cpCollisionHandler* h = cpSpaceAddWildcardHandler(space, a);
		CallbackData& cbd = setupCallbackData(h);
		cbd.data = data;
	}

	void Space::setDefaultCollisionBeginFunc(CollisionBeginFunc begin)
	{
		cpCollisionHandler* h = cpSpaceAddDefaultCollisionHandler(space);
		CallbackData& cbd = setupCallbackData(h);
		cbd.begin = begin;
	}

	void Space::setDefaultCollisionPreSolveFunc(CollisionPreSolveFunc preSolve)
	{
		cpCollisionHandler* h = cpSpaceAddDefaultCollisionHandler(space);
		CallbackData& cbd = setupCallbackData(h);
		cbd.preSolve = preSolve;
	}

	void Space::setDefaultCollisionPostSolveFunc(CollisionPostSolveFunc postSolve)
	{
		cpCollisionHandler* h = cpSpaceAddDefaultCollisionHandler(space);
		CallbackData& cbd = setupCallbackData(h);
		cbd.postSolve = postSolve;
	}

	void Space::setDefaultCollisionSeparateFunc(CollisionSeparateFunc separate)
	{
		cpCollisionHandler* h = cpSpaceAddDefaultCollisionHandler(space);
		CallbackData& cbd = setupCallbackData(h);
		cbd.separate = separate;
	}

	void Space::setDefaultCollisionUserData(void* data)
	{
		cpCollisionHandler* h = cpSpaceAddDefaultCollisionHandler(space);
		CallbackData& cbd = setupCallbackData(h);
		cbd.data = data;
	}
}
