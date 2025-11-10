#include "BulletCollision/CollisionShapes/btConvexShape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "LinearMath/btVector3.h"
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

class Physics {
private:
  Physics();

private:
  static const btVector3 DEFAULT_GRAVITY;

public:
  btDefaultCollisionConfiguration *collisionConfig;
  btCollisionDispatcher *dispatcher;
  btBroadphaseInterface *broadphase;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld *dynamicsWorld;

  btSphereShape *sphere;
  btRigidBody *sphereBody;

  btConvexShape *capsule;
  btPairCachingGhostObject *ghostObject;
  btKinematicCharacterController *character;

public:
  Physics(const Physics &) = delete;
  Physics &operator=(const Physics &) = delete;
  Physics(Physics &&) = delete;
  Physics &operator=(Physics &&) = delete;

  static Physics *getInstance();

  bool init(const btVector3 &gravity = btVector3(0.0f, -9.8f, 0.0f));
  void initCharacter();
  void initShapes();
  void free();
};
