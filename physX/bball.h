/**
  \file samples/physX/source/bball.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/

#pragma once

#include "G3D-app/G3D-app.h"
#include "G3D-base/FileSystem.h"
#include "G3D-base/G3D-base.h"
#include "G3D-gfx/G3D-gfx.h"

#include "G3D-app/PhysicsEntity.h"
#include "G3D-app/PhysicsScene.h"
#include "AttractorEntity.h"
#include "SpawnerEntity.h"

#include "PSceneEditorWindow.h"

namespace G3D {
class BallApp : public GApp {
    shared_ptr<PhysicsScene> m_scene;
    bool m_debugCam = false;
    bool m_editMode = false;
    bool m_isPlayerMoving = false;

    /** This is needed for a lot of things like calculating the heading and
     * bearing information for the player and also for updating the camera
     * follower motion TODO: make this constraint based and get the frame from
     * physics engine
     */
    const CFrame computePlayerMotionFrame(const shared_ptr<Entity> player);

protected:
    /** Called from onInit */
    void makeGUI();

public:
    BallApp(const GApp::Settings &settings = GApp::Settings());

    virtual void onInit() override;
    virtual void onPose(Array<shared_ptr<Surface>> &posed3D,
                        Array<shared_ptr<Surface2D>> &posed2D) override;

    virtual bool onEvent(const GEvent &e) override;
    virtual void onUserInput(UserInput *ui) override;
};
} // namespace G3D
