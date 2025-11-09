#include "LinearMath/btVector3.h"
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

public:
  Physics(const Physics &) = delete;
  Physics &operator=(const Physics &) = delete;
  Physics(Physics &&) = delete;
  Physics &operator=(Physics &&) = delete;

  static Physics *getInstance();

  bool init(const btVector3 &gravity = btVector3(0.0f, -9.8f, 0.0f));
};
