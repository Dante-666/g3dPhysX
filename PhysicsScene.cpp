/**
  \file G3D-app.lib/source/PhysicsScene.cpp

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/
#include "G3D-app/PhysicsScene.h"

namespace G3D {
PhysicsScene::PhysicsScene(const shared_ptr<AmbientOcclusion> &ao)
    : Scene(ao), m_physics(std::make_shared<PhysXPhysics>()) {}

shared_ptr<PhysicsScene>
PhysicsScene::create(const shared_ptr<AmbientOcclusion> &ao) {
    return createShared<PhysicsScene>(ao);
}

shared_ptr<Entity> PhysicsScene::insert(const shared_ptr<Entity> &entity) {
    m_physics->insertEntity(entity.get());
    if (entity->name() == "player") {
        m_player = entity;
        m_playerMotion = entity->frame();
    }
    Scene::insert(entity);
    return entity;
}

Any PhysicsScene::load(const String &sceneName,
                       const LoadOptions &loadOptions) {
    auto any = Scene::load(sceneName);
    return any;
}

void PhysicsScene::clear() { Scene::clear(); };

void PhysicsScene::onSimulation(SimTime deltaTime) {
    if (!isNaN(deltaTime) && !(deltaTime == 0.0)) {
        m_physics->simulate(deltaTime);
    }

    /** The scene graph calls the onSimulation method on attached entities.
	The methodology was used here to update physical entities as well.

	Seems like a good design choice to me as it removes the responsibility
	of physical interaction from the PhysicsScene.
    */
    Scene::onSimulation(deltaTime);
};

shared_ptr<PurePhysics> PhysicsScene::getPhysicsEngine() { return m_physics; }

shared_ptr<Entity> PhysicsScene::getPlayer() { return m_player; }

void PhysicsScene::addBoxArray(String name, Vector2 grid, Vector3 position,
                               Vector3 direction) {
    /*Scene::LoadOptions options;
    for (int j = 0; j < grid.y; j++) {
        for (int i = 0; i < grid.x; i++) {
            Any box(Any::TABLE, "PhysicsEntity");
            box["model"] = "boxModel";
            box["frame"] = CFrame::fromXYZYPRDegrees(position.x + i * (2 + 0.1),
                                                     position.y + j * (2 + 0.1),
                                                     0, 0, 0, 0);
            box["mass"] = 0.125;
	    Any ashape(Any::TABLE, "AShape");
	    ashape["box"] = Box(Point3(-1, -1, -1), Point3(1, 1, 1));
            box["ashape"] = ashape;
	    AnyTableReader propertyTable(box);
            auto sz = m_modelTable.size();
            shared_ptr<Entity> entity =
                PhysicsEntity::create(name + String(std::to_string(numSphere++)),
                                    this, propertyTable, m_modelTable, options);
            insert(entity);
        }
    }*/
}

} // namespace G3D
