/**
  \file G3D-app.lib/source/PhysicsEntity.h

  G3D Innovation Engine http://casual-effects.com/g3d
  Copyright 2000-2021, Morgan McGuire
  All rights reserved
  Available under the BSD License

  Contributed by : Siddharth J Singh(siddharthjsingh@protonmail.com)
*/

#include "G3D-app/PhysicsEntity.h"
#include "G3D-app/PhysicsScene.h"

namespace G3D {
PhysicsEntity::PhysicsEntity() : VisibleEntity(){};

void PhysicsEntity::onSimulation(SimTime absoluteTime, SimTime deltaTime) {
    //TODO: this->apply(this);
}

shared_ptr<Entity> PhysicsEntity::create(
    const String &name, Scene *scene, AnyTableReader &propertyTable,
    const ModelTable &modelTable, const Scene::LoadOptions &loadOptions) {
    // Don't initialize in the constructor, where it is unsafe to throw Any
    // parse exceptions
    shared_ptr<PhysicsEntity> physEntity(new PhysicsEntity());

    // Initialize each base class, which parses its own fields
    physEntity->Entity::init(name, scene, propertyTable);
    physEntity->VisibleEntity::init(propertyTable, modelTable);
    physEntity->PhysicsEntity::init(propertyTable);

    // Verify that all fields were read by the base classes
    propertyTable.verifyDone();

    return physEntity;
}

// Initialize all behaviors
void PhysicsEntity::init(AnyTableReader &propertyTable) {
    AShape ashape;
    if (propertyTable.getIfPresent("ashape", ashape)) {
        // Empty generic shape means user wants it constructed from mesh
        if (!ashape.getShape()) {
            PhysicsEntity *entity = dynamic_cast<PhysicsEntity *>(this);
            const shared_ptr<ArticulatedModel> model =
                dynamic_pointer_cast<G3D::ArticulatedModel>(entity->model());
            debugAssertM(model->meshArray().size() == 1,
                         "Attempt to add a model with multiple Meshes");
            ArticulatedModel::Mesh *firstMesh = model->meshArray()[0];
            CPUVertexArray &fullVertex = firstMesh->geometry->cpuVertexArray;

            Array<int> index = firstMesh->cpuIndexArray;
            Array<Point3> vertex;
            for (int i = 0; i < fullVertex.vertex.size(); i++) {
                vertex.push_back(fullVertex.vertex[i].position);
            }
            ashape.setShape(std::make_shared<MeshShape>(vertex, index));
        }
        // copy the object using new keyword as this one will be gone
        this->addProperty(new AShape(ashape));
    }
    Solid solid;
    if (propertyTable.getIfPresent("solid", solid)) {
        // copy the object using new keyword as this one will be gone
        this->addProperty(new Solid(solid));
    }
    // Hold a pointer to this for ez behavior modification
    m_physicsScene = dynamic_cast<PhysicsScene *>(m_scene);
    debugAssertM(m_physicsScene, "Scene is not a PhysicsScene");

}

Any PhysicsEntity::toAny(const bool forceAll) const {
    Any a = VisibleEntity::toAny(forceAll);
    a.setName("PhysicsEntity");

    const G3D::PropertyChain *link =
        dynamic_cast<const G3D::PropertyChain *>(this);

    for (auto it = link->begin(); !it.isOver(); it.advance()) {
        if (it->getName() == "AShape") {
            const AShape *ashape = dynamic_cast<const G3D::AShape *>(*it);
            a.set("ashape", *ashape);
        } else if (it->getName() == "Solid") {
            const Solid *solid = dynamic_cast<const G3D::Solid *>(*it);
            a.set("solid", *solid);
        }
    }
    // Model and pose must already have been set, so no need to change anything
    return a;
}

void PhysicsEntity::makeGUI(class GuiPane *pane, class GApp *app) {
    VisibleEntity::makeGUI(pane, app);

    const PropertyChain *link = dynamic_cast<const PropertyChain *>(this);
	
    auto tabPane = pane->addTabPane();
    for (auto it = link->begin(); !it.isOver(); it.advance()) {
	String property = it->getName();
	auto childPane = tabPane->addTab(property);
	it->makeGUI(childPane, app);
    }

}

void PhysicsEntity::onPropertyDropDownAction() {
    //cant do anything here, needs pane objects
    /*const String &choice = m_propertyDropDownList->selectedValue().text();

    const PropertyChain *link = dynamic_cast<const PropertyChain *>(this);
    auto it = link->begin();
    auto derived = it.getByName(choice);

    derived->makeGUI(
    if (choice == "AShape") {
	auto ashape = dynamic_cast<const AShape *>(it.getByName("AShape"));
    } else if (choice == "Solid") {
	auto solid = dynamic_cast<const Solid *>(it.getByName("Solid"));
    }*/
}

} // namespace G3D
