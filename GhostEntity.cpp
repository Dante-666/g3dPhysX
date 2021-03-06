/**
  \file G3D-app.lib/source/GhostEntity.cpp

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/
#include "G3D-app/GhostEntity.h"
#include "G3D-gfx/Profiler.h"
#include "G3D-app/PhysicsScene.h"
#include "G3D-app/PChain.h"

namespace G3D {
GhostEntity::GhostEntity() : MarkerEntity(){};

// Initialize all behaviors
void GhostEntity::init(AnyTableReader &propertyTable) {
    AShape ashape;
    if (propertyTable.getIfPresent("ashape", ashape)) {
        // copy the object using new keyword as this one will be gone
        this->addProperty(new AShape(ashape));
    }

    Array<Box> boxArray;
    Color3 color = Color3::white();
    propertyTable.getIfPresent("color", color);

    const G3D::PropertyChain *link =
        dynamic_cast<const G3D::PropertyChain *>(this);

    for (auto it = link->begin(); !it.isOver(); it.advance()) {
        if (it->getName() == "AShape") {
            const AShape *cshape = dynamic_cast<const G3D::AShape *>(*it);
            shared_ptr<G3D::Shape> gShape = cshape->getShape();
            if (gShape->type() == G3D::Shape::Type::BOX) {
                boxArray.push_back(gShape->box());
            } else {
                debugAssertM(false,
                             "Adding a non-box like shape for GhostEntity");
            }
            break;
        }
    }

    MarkerEntity::init(boxArray, color);

    // Hold a pointer to this for ez behavior modification
    m_physicsScene = dynamic_cast<PhysicsScene *>(m_scene);
    debugAssertM(m_physicsScene, "Scene is not a PhysicsScene");

}

Any GhostEntity::toAny(const bool forceAll) const {
    Any a = Entity::toAny(forceAll);
    a.setName("GhostEntity");
    a["color"] = m_color;
    // No need for a massive GhostEntity, initialize it to 0 all the time
    a.remove("mass");

    const G3D::PropertyChain *link =
        dynamic_cast<const G3D::PropertyChain *>(this);
    for (auto it = link->begin(); !it.isOver(); it.advance()) {
        if (it->getName() == "AShape") {
            const AShape *ashape = dynamic_cast<const G3D::AShape *>(*it);
            a.set("ashape", *ashape);
        }
    }
    
    return a;
}

} // namespace G3D
