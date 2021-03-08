/**
  \file samples/physX/source/AttractorEntity.cpp

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/

#include "AttractorEntity.h"

namespace G3D {

shared_ptr<PhysicsEntity> AttractorEntity::m_invisAnchor = nullptr;

AttractorEntity::AttractorEntity() : GhostEntity(){};

void AttractorEntity::onSimulation(SimTime absoluteTime, SimTime deltaTime) {
    // add behavior over here and remove chaining?
    // isolate behavior to a new class as that's a limitation now
    auto pEngine = GhostEntity::m_physicsScene->getPhysicsEngine();
    if (auto physEntity = pEngine->getPrimaryCollider(this)) {
        // add this to the collisionFilter
        pEngine->ignoreCollisionCheck(this, physEntity);
        // add the constraint
        m_constraints.push_back(
            pEngine->addConstraint(m_invisAnchor.get(), physEntity));
    }
}

shared_ptr<Entity> AttractorEntity::create(
    const String &name, Scene *scene, AnyTableReader &propertyTable,
    const ModelTable &modelTable, const Scene::LoadOptions &loadOptions) {
    // Don't initialize in the constructor, where it is unsafe to throw Any
    // parse exceptions
    shared_ptr<AttractorEntity> attrEntity(new AttractorEntity());

    CFrame anchorFrame;
    propertyTable.getIfPresent("frame", anchorFrame);
    propertyTable.setReadStatus("frame", false);

    Any box(Any::TABLE, "PhysicsEntity");
    // box["model"] = "boxModel";
    box["frame"] = anchorFrame;
    box["mass"] = 0.;
    Any ashape(Any::TABLE, "AShape");
    ashape["box"] = Box(Point3(-1, -1, -1), Point3(1, 1, 1));
    box["ashape"] = ashape;
    AnyTableReader propTable(box);
    shared_ptr<Entity> entity = PhysicsEntity::create(
        name + String("Anchor"), scene, propTable, modelTable, loadOptions);
    entity->setShouldBeSaved(false);
    // Should insert this for physics interactions
    scene->insert(entity);

    m_invisAnchor = dynamic_pointer_cast<PhysicsEntity>(entity);

    attrEntity->Entity::init(name, scene, propertyTable);
    attrEntity->GhostEntity::init(propertyTable);

    propertyTable.verifyDone();

    return attrEntity;
}
void AttractorEntity::init(AnyTableReader &propertyTable) {}

Any AttractorEntity::toAny(const bool forceAll) const {
    Any a = GhostEntity::toAny(forceAll);
    a.setName("AttractorEntity");

    return a;
}
void AttractorEntity::makeGUI(class GuiPane *pane, class GApp *app) {}
} // namespace G3D
