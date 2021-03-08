/**
  \file samples/physX/source/SpawnerEntity.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/

#pragma once

/** \brief Derived from a GhostEntity
 * This is basically a triggerable object, any MarkerEntity is. Here, the
 * trigger is time based and user can set the shape/type of the desired
 * PhysicsEntity to be spawned.
 */

#include "G3D-app/G3D-app.h"
#include "G3D-base/G3D-base.h"
#include "G3D-gfx/G3D-gfx.h"

#include "G3D-app/GhostEntity.h"
#include "G3D-app/PhysicsScene.h"

namespace G3D {

class PhysicsScene;

class SpawnerEntity : public GhostEntity {
    float m_time = 0;
    float m_timer = 0;
    bool m_spawn = false;
    int id;
    Any prototype;

    std::vector<shared_ptr<Entity>> m_spawnedEntities;

public:
    SpawnerEntity();

    /** update the pose of object here by querying the physics engine */
    virtual void onSimulation(SimTime absoluteTime, SimTime deltaTime) override;

    /** For deserialization from Any / loading from file */
    static shared_ptr<Entity> create(const String &name, Scene *scene,
                                     AnyTableReader &propertyTable,
                                     const ModelTable &modelTable,
                                     const Scene::LoadOptions &loadOptions);

    void init(AnyTableReader &propertyTable);

    virtual Any toAny(const bool forceAll) const override;

    virtual void makeGUI(class GuiPane *pane, class GApp *app) override;

protected:
    class GuiDropDownList *m_propertyDropDownList;

    void onPropertyDropDownAction();
};
} // namespace G3D
