#include "Physics.h"
#include "BulletCollision/CollisionDispatch/btCollisionObject.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletCollision/CollisionShapes/btCapsuleShape.h"
#include "BulletCollision/CollisionShapes/btConvexShape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btVector3.h"
#include <spdlog/spdlog.h>

Physics::Physics()
    : collisionConfig(nullptr), dispatcher(nullptr), broadphase(nullptr),
      solver(nullptr), dynamicsWorld(nullptr), capsule(nullptr),
      ghostObject(nullptr), character(nullptr) {}

const btVector3 Physics::DEFAULT_GRAVITY(0.0f, -9.8f, 0.0f);

Physics *Physics::getInstance() {
  static Physics instance;
  return &instance;
}

bool Physics::init(const btVector3 &gravity) {
  spdlog::info("Initializing Bullet Physics...");

  collisionConfig = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfig);
  broadphase = new btDbvtBroadphase();
  solver = new btSequentialImpulseConstraintSolver;
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver,
                                              collisionConfig);

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

void Physics::initCharacter() {
  spdlog::info("Initializing bullet physics character...");
  capsule = new btCapsuleShape(0.5f, 1.6f);
  ghostObject = new btPairCachingGhostObject();
  ghostObject->setCollisionShape(capsule);
  ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

  btTransform startTransform;
  startTransform.setIdentity();
  startTransform.setOrigin(btVector3(0, 5, 0));
  ghostObject->setWorldTransform(startTransform);

  dynamicsWorld->addCollisionObject(
      ghostObject, btBroadphaseProxy::CharacterFilter,
      btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);

  spdlog::info("MEOW4");
  character = new btKinematicCharacterController(ghostObject, capsule, 0.35f);

  spdlog::info("MEOW5");
  dynamicsWorld->addCharacter(character);
  spdlog::info("Bullet physics character initialized successfully.");
}

void Physics::initShapes() {
  spdlog::info("Initializing bullet physics shapes...");
  capsule = new btSphereShape(btScalar(10.0f));

  btScalar mass = 5515.0f;
  btVector3 inertia(0, 0, 0);

  capsule->calculateLocalInertia(mass, inertia);

  btTransform startTransform;
  startTransform.setIdentity();
  startTransform.setOrigin(btVector3(0, 5, 0)); // place at y=5

  btDefaultMotionState *motionState = new btDefaultMotionState(startTransform);

  btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, capsule,
                                                inertia);
  sphereBody = new btRigidBody(info);

  dynamicsWorld->addRigidBody(sphereBody);
  spdlog::info("Bullet physics shapes initialized successfully.");
}

void Physics::free() {
  spdlog::info("Destroying Bullet physics resources...");
  delete dynamicsWorld;
  delete solver;
  delete broadphase;
  delete dispatcher;
  delete collisionConfig;
  spdlog::info("Bullet physics resources destroyed sucessfully.");
}
