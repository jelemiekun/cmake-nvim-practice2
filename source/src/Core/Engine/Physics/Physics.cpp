#include "Physics.h"
#include <spdlog/spdlog.h>

Physics::Physics() {}

const btVector3 Physics::DEFAULT_GRAVITY(0.0f, -9.8f, 0.0f);

Physics *Physics::getInstance() {
  static Physics instance;
  return &instance;
}

bool Physics::init(const btVector3 &gravity) {
  spdlog::info("Initializing Bullet Physics...");

  btDefaultCollisionConfiguration *collisionConfig =
      new btDefaultCollisionConfiguration();
  btCollisionDispatcher *dispatcher =
      new btCollisionDispatcher(collisionConfig);
  btBroadphaseInterface *broadphase = new btDbvtBroadphase();
  btSequentialImpulseConstraintSolver *solver =
      new btSequentialImpulseConstraintSolver;
  btDiscreteDynamicsWorld *dynamicsWorld = new btDiscreteDynamicsWorld(
      dispatcher, broadphase, solver, collisionConfig);

  if (gravity == DEFAULT_GRAVITY) {
    spdlog::info("No gravity value passed. Will use deafult earth gravity...");
    dynamicsWorld->setGravity(DEFAULT_GRAVITY);
  } else {
    spdlog::info("Gravity set to {}, {}, {}.", gravity.x(), gravity.y(),
                 gravity.z());
  }

  if (!collisionConfig || !dispatcher || !broadphase || !solver ||
      !dynamicsWorld) {
    spdlog::warn("Bullet Physics failed to inifialize.");
    return false;
  }

  spdlog::info("Bullet Physics initiated successfully.");
  return true;
}
