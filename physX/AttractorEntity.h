/**
  \file samples/physX/source/AttractorEntity.h

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

#include "G3D-app/Constraint.h"
#include "G3D-app/GhostEntity.h"
#include "G3D-app/PhysicsEntity.h"
#include "G3D-app/PhysicsScene.h"

#include <memory>

namespace G3D {

class PhysicsScene;

/** \brief Derived from a GhostEntity
*/
class AttractorEntity : public GhostEntity {
    static shared_ptr<PhysicsEntity> m_invisAnchor;
    std::vector<Constraint*> m_constraints;

public:
    AttractorEntity();

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
