/**
  \file G3D-app.lib/include/G3D-app/AShape.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/
#pragma once

#include "G3D-app/GuiDropDownList.h"
#include "PChain.h"

#include "G3D-app/ArticulatedModel.h"
#include "G3D-app/GuiControl.h"
#include "G3D-app/Shape.h"
#include "G3D-base/G3D-base.h"

/** \brief This behavior enables the Opaqueness of the object in the Physics
    engine. It means if the object reacts to collisions or not. 
    Also requires a collision shape to hold that data.

    \see G3D::PhysicsEntity, G3D::GhostEntity
*/

namespace G3D {
class AShape : public PropertyChain {
    shared_ptr<Shape> m_shape;
    //GuiDropDownList *m_shapeDropDownList;
    String m_anySpec;

    void assignShape(const Any &);

public:
    AShape() = default;

    AShape(const AShape &);

    explicit AShape(const Any &);

    AShape &operator=(const Any &);

    Any toAny() const;


    const virtual String getName() const override;

    void setShape(shared_ptr<Shape>);

    const shared_ptr<Shape> getShape() const;

    void shapeSetterCallBack();

    virtual void makeGUI(class GuiPane *pane, class GApp *app) override;
};
} // namespace G3D
