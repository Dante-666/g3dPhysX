/**
  \file G3D-app.lib/include/G3D-app/PSceneEditorWindow.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/

#pragma once

#include "G3D/G3D.h"

class PhysicsSceneEditorWindow : public SceneEditorWindow {
protected:
    friend class EntitySelectWidget;
    PhysicsSceneEditorWindow(GApp *app, shared_ptr<Scene> scene,
                             shared_ptr<GuiTheme> theme);

public:
    //virtual void onSelectEntity() override;
    static shared_ptr<PhysicsSceneEditorWindow>
    create(GApp *app, shared_ptr<Scene> scene, shared_ptr<GuiTheme> theme);

    // Hack to make it work
    GApp *getApp();

    shared_ptr<Scene> getScene();

    SceneVisualizationSettings& getVisSettings();

    shared_ptr<Entity> getSelectedEntity();

    Model::HitInfo& getSelectionInfo();
};

namespace {
class EntitySelectWidget : public Widget {
protected:
    //shared_ptr<RigidEntity> m_lastSelectedRigidEntity;
    PhysicsSceneEditorWindow *m_sceneEditor;
    mutable EventCoordinateMapper m_mapper;

public:
    EntitySelectWidget(PhysicsSceneEditorWindow *s);

    virtual void render(RenderDevice *rd) const override;

    virtual float positionalEventZ(const Point2 &pixel) const override;

    bool onEvent(const GEvent &event) override;
};
} // namespace
