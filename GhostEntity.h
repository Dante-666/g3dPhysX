/**
  \file G3D-app.lib/include/G3D-app/GhostEntity.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/
#pragma once

#include "G3D-app/ArticulatedModel.h"
#include "G3D-app/G3D-app.h"
#include "G3D-base/G3D-base.h"
#include "G3D-gfx/G3D-gfx.h"

#include "PChain.h"

#include "AShape.h"

#include <memory>

namespace G3D {

class PhysicsScene;

/** \brief Derived from a MarkerEntity
    
    Designed to behave like a trigger sort of entity which can be used to obtain
    the entities overlapping this bounding box.

    \see G3D::MarkerEntity, G3D::PhysicsScene
*/
class GhostEntity : public MarkerEntity, public PropertyChain {

  protected:
    PhysicsScene *m_physicsScene;

  public:
    GhostEntity();

    void init(AnyTableReader &propertyTable);

    virtual Any toAny(const bool forceAll) const override;
};
} // namespace G3D
