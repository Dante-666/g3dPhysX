/**
  \file G3D-app.lib/include/G3D-app/Solid.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/
#pragma once

#include "G3D-app/PChain.h"

#include "G3D-app/ArticulatedModel.h"
#include "G3D-app/Shape.h"
#include "G3D-base/G3D-base.h"

/** \brief This behavior enables the Opaqueness of the object in the Physics
 * engine. It means if the object reacts to collisions or not. Also requires a
 * collision shape to hold that data.
 */

namespace G3D {
class Solid : public PropertyChain {
    float m_rollingFriction = 0.3;
    bool m_phased = false;
public:
    Solid() = default;

    Solid(const Solid &opq);

    explicit Solid(const Any &any);

    Solid &operator=(const Any &a) { return *this = Solid(a); }

    Any toAny() const;

    const virtual String getName() const override;

    virtual void makeGUI(GuiPane* pane, GApp* app) override;

    const float getRollingFriction() const;
};
} // namespace G3D
