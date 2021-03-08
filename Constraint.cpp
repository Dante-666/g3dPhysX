/**
  \file G3D-app.lib/source/Constraint.cpp

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/

#include "G3D-app/Constraint.h"

namespace G3D {
Constraint::TYPE Constraint::getType() { return m_type; }

void Constraint::setType(TYPE type) { m_type = type; }
} // namespace G3D
