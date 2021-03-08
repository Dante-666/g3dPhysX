/**
  \file G3D-app.lib/source/Solid.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/

#include "G3D-app/Solid.h"

#include "G3D-app/PhysicsEntity.h"
#include "G3D-app/PhysicsScene.h"

namespace G3D {

Solid::Solid(const Solid &opq) {
    m_phased = opq.m_phased;
    m_rollingFriction = opq.m_rollingFriction;
}

Solid::Solid(const Any &any) {
    *this = Solid();
    any.verifyName("Solid");
    AnyTableReader r(any);
    r.getIfPresent("phased", m_phased);
    r.getIfPresent("rollingFriction", m_rollingFriction);
}

Any Solid::toAny() const {
    Any any(Any::TABLE, "Solid");
    any["phased"] = m_phased;
    any["rollingFriction"] = m_rollingFriction;
    return any;
}

const String Solid::getName() const { return "Solid"; }

void Solid::makeGUI(GuiPane *pane, GApp *app) {
    pane->addNumberBox<float>("rollingFriction", &m_rollingFriction);
}

const float Solid::getRollingFriction() const { return m_rollingFriction; }
} // namespace G3D
