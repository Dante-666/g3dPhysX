/**
  \file G3D-app.lib/include/G3D-app/PhysXPhysics.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/
#pragma once

#include <boost/bimap.hpp>

#include <set>

/*#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolverMt.h"

#include "BulletFactory.h"
#include "LinearMath/btDefaultMotionState.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorldMt.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"*/

#include "G3D-app/Constraint.h"

#include "G3D-app/ArticulatedModel.h"
#include "G3D-app/Shape.h"
#include "G3D-app/VisibleEntity.h"
#include "G3D-base/CoordinateFrame.h"
#include "G3D-base/Vector3.h"
#include "G3D-gfx/CPUVertexArray.h"

#include "G3D-app/PurePhysics.h"

/** \brief PhysX Physics implementation

    This attempts to implement the PurePhysics class via the shipped PhysX library.
    
    Users can refer to this and create their own custom physics implementation

    \see G3D::PhysicsScene

*/

class PhysXPhysics : public PurePhysics {
    /**
     * Bullet works best with raw pointers so take care with this class
     */
    /*btCollisionConfiguration *m_collisionConfig;
    btDispatcher *m_collisionDispatcher;
    btBroadphaseInterface *m_broadPhase;
    btConstraintSolverPoolMt *m_solverPool;
    btConstraintSolver *m_solver;
    btDynamicsWorld *m_dynamicsWorld;
    // TODO: How to handle the lifecycle management? Suppose a scenario in which
    // the RigidEntity is not visible anymore, then we don't need to simulate
    // that or if it goes out of scope, then also the simulation needs to be
    // filtered for collision detection only between relevant objects A map
    // might be the best option to update and track entities which were added
    // TODO: Lifecycle or Object Pool may be used inside the Factory itself and
    // have this class use it as a private member

    boost::bimap<G3D::Entity const *, btCollisionObject *> m_dynamicBodyMap;
    std::map<const G3D::Constraint* const, btTypedConstraint *> m_constraintMap;*/

public:
    PhysXPhysics();
    virtual ~PhysXPhysics() override;

    // TODO:Does the object need to be moved or copied? For now it seems no, so
    // delete the move and copy constructors if there is a need, then implement
    // these.
    PhysXPhysics(const PhysXPhysics &) = delete;
    PhysXPhysics &operator=(const PhysXPhysics &) = delete;

    PhysXPhysics(PhysXPhysics &&) = delete;
    PhysXPhysics &&operator=(PhysXPhysics &&) = delete;

    virtual void insertEntity(const G3D::Entity *entity) override;

    virtual void removeEntity(const G3D::Entity *entity) override;

    virtual void applyForceField(const G3D::Entity *field,
                                 const G3D::Vector3 force,
                                 const FieldType type) override;

    virtual const G3D::Constraint *const
    addConstraint(const G3D::Entity *entityA,
                  const G3D::Entity *entityB) override;

    virtual void
    removeConstraint(const G3D::Constraint *const constraint) override;

    virtual const G3D::Entity *const
    getPrimaryCollider(const G3D::Entity *field) override;

    virtual void ignoreCollisionCheck(const G3D::Entity *trigger,
                                      const G3D::Entity *collider) override;

    virtual G3D::CoordinateFrame getFrame(const G3D::Entity *entity) override;

    virtual void reconstructRigidBody(const G3D::Entity *entity) override;

    virtual void applyForce(G3D::Entity *entity, G3D::Point3 force) override;

    virtual void simulate(float deltaTime) override;
/*
private:
    // For creating the solver pool
    btConstraintSolverPoolMt *createSolverPool();*/
};
