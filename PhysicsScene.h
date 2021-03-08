/**
  \file G3D-app.lib/include/G3D-app/PhysicsScene.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/
#pragma once

#include "G3D-app/G3D-app.h"
#include "G3D-base/G3D-base.h"
#include "G3D-gfx/G3D-gfx.h"

#include "G3D-app/PhysXPhysics.h"
#include "G3D-app/PurePhysics.h"

namespace G3D {

/** \brief An inherited Scene with support for Physics
 
    This is the PhysicsScene which inherits from the G3D::Scene and has extended
    the former by accomodating for a custom onSimulate method that runs a Physics
    simulation from an external Physics engine and updates the G3D objects
    accordingly. 

    Right now, this implementation only supports PhysX for easier integration
    with %G3D but there is nothing stopping one from implementing another physics
    world and initializing the scene graph with the custom engine.

    \see G3D::Scene, G3D::PhysicsEntity, G3D::GhostEntity
*/
class PhysicsScene : public Scene {
    shared_ptr<PurePhysics> m_physics;
    shared_ptr<Entity> m_player;
    //shared_ptr<Entity> m_forceField;
    int numSphere = 1;

public:
    CoordinateFrame m_playerMotion;

protected:
    PhysicsScene(const shared_ptr<AmbientOcclusion> &ao);

public:
    static shared_ptr<PhysicsScene>
    create(const shared_ptr<AmbientOcclusion> &ao);
    /** This should be overriden to support the physics entities, models don't
     * have to be since they are decorated instances of the entity themselves
     */
    virtual shared_ptr<Entity>
    insert(const shared_ptr<Entity> &entity) override;

    virtual Any load(const String& sceneName, const LoadOptions& loadOptions = LoadOptions()) override;

    /** Remove all original Scene objects alone with the custom Physics objects
     */
    virtual void clear() override;

    /** This is the crux method which needs to be run, using both the existing
     * simple animations and the Physics based natural animation may be needed
     * in a few instances, so best idea would be to use both. Either case, run
     * the external Physics engine simulation in this method.
     */
    virtual void onSimulation(SimTime deltaTime) override;

    shared_ptr<PurePhysics> getPhysicsEngine();

    shared_ptr<Entity> getPlayer();

    void addBoxArray(String name, Vector2 grid, Vector3 position,
                     Vector3 direction);
};
} // namespace G3D
