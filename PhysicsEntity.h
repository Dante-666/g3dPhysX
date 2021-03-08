/**
  \file G3D-app.lib/include/G3D-app/PhysicsEntity.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/
#pragma once

/** \brief Derived from a VisibleEntity
    Designed to be the interface the the physics object and must be able to add
    runtime behavior which could also be captured by the Any specification. This
    is important because ultimately the objects are being constructed initially
    from a Scene. So it's much better to take in the features of Scene and mould
    custom classes around it.

    The SceneEditor revealed a problem with ongoing simulation, if an object is
    grabbed while editing and when it is unselected, the rigid entity has to be
    reitialized with a new rigid object at least for bullet. Seems like a dirty
    way of doing it but also makes sense. This also let's us thing about
    lifecycle management by another object or by a behavior.

    A Physics based object has certain properties, like the collision shape
    associated with it, likewise, if it is a solid object that describes rigid
    body behavior or ghost object behavior.

    \see G3D::VisibleEntity
*/

#include "G3D-app/G3D-app.h"
#include "G3D-base/G3D-base.h"
#include "G3D-gfx/G3D-gfx.h"

#include "G3D-app/PChain.h"

#include "G3D-app/AShape.h"
#include "G3D-app/Solid.h"

#include <memory>

namespace G3D {

class PhysicsScene;

class PhysicsEntity : public VisibleEntity, public PropertyChain {
    PhysicsScene *m_physicsScene;

  public:
    PhysicsEntity();

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
