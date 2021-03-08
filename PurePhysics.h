/**
  \file G3D-app.lib/include/G3D-app/PurePhysics.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(dsiddharthjsingh@protonmail.com)
*/

#pragma once

#include "Constraint.h"
#include "G3D-app/Entity.h"
#include "G3D-app/G3D-app.h"
#include "G3D-base/G3D-base.h"
#include "G3D-base/Matrix3x4.h"
#include "G3D-base/Vector3.h"
#include "G3D-gfx/G3D-gfx.h"

/** \brief Physics Abstraction Layer

    This is the abstraction layer for physics and the general idea is that it
    can be inherited to make different implementations work for different
   physics engines.

    Almost all of them work in a similar fashion, in which a certain
    timestep has to be provided by the user, or in this case, the renderer and
    the physics simulation undergoes the time evolution.

    List of objects supported:
    1. StaticMatter : Is immovable and doesn't deform (ground)
    2. RigidMatter  : It may move around and collide but won't change shape
    3. Contraints   : It entangles objects and imposes constraints

*/

class PurePhysics {

  public:
    enum FieldType { DIRECTIONAL, RADIAL };

    PurePhysics() = default;
    virtual ~PurePhysics() = default;
    /** Insertion routine for different objects. Since G3D provides the m_pose
        as a protected member for VisibleEntity, we cannot create a generic
        CollisionEntity from it.
    */
    virtual void insertEntity(const G3D::Entity *entity) = 0;

    virtual void removeEntity(const G3D::Entity *entity) = 0;

    virtual void applyForceField(const G3D::Entity *field,
                                 const G3D::Vector3 force,
                                 const FieldType type = DIRECTIONAL) = 0;

    virtual const G3D::Constraint *const
    addConstraint(const G3D::Entity *entityA, const G3D::Entity *entityB) = 0;

    virtual void removeConstraint(const G3D::Constraint *const constraint) = 0;

    /** This may return nullptr when we don't have any colliders, take care of
        this in the client.
    */
    virtual const G3D::Entity *const
    getPrimaryCollider(const G3D::Entity *trigger) = 0;

    virtual void ignoreCollisionCheck(const G3D::Entity *trigger,
                                      const G3D::Entity *collider) = 0;

    /** Extract the CoordinateFrame information from whatever RT datatypes the
	underlying physics engine supports so that G3D can make the
	corresponding updates to the entity. This should be a generic method and
	we should dynamically cast it for all possible cases to determine the
	type of object.
    */
    virtual G3D::CoordinateFrame getFrame(const G3D::Entity *entity) = 0;
    // TODO: to be solved as a wider problem of object management after
    // behavioral entity is in action
    virtual void reconstructRigidBody(const G3D::Entity *entity) = 0;

    /** Apply a force to the object */
    virtual void applyForce(G3D::Entity *entity, G3D::Point3 force) = 0;

    /** Override this method in the implementation to update the underlying
	physics world
    */
    virtual void simulate(float deltaTime) = 0;
};
