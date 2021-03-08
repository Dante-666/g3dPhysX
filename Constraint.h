/**
  \file G3D-app.lib/include/G3D-app/Constraint.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/

#pragma once

namespace G3D {

class Constraint {
public:
    enum class TYPE { GENERIC6DOF, HINGE };

    TYPE getType();
    void setType(TYPE type);

private:
    TYPE m_type;
};
} // namespace G3D
