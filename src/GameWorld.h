#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>

#include <GL/gl.h>

#include "common.h"
#include "GameAssetManager.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "CubeAsset.h"

/**
 * GameWorld allows us to separate the management of the game world from the
 * nuts and bolts of game loop initialisation.  The GameWorld currently has
 * a very simplified scene graph consisiting of a single GameAssetManager.
 */
class GameWorld {
 public:
  /**
   * We thread the ApplicationMode through the GameWorld ss we want to read it
   * in from the user.  Threading the state through the various function calls
   * is preferable (in this case) to having some kind of global state.
   */
  GameWorld(ApplicationMode);
  void moveF();
  void moveB();
  void moveL();
  void moveR();
  void setCamera(GLfloat, GLfloat);

  /**
   * Calling Draw() will draw the entire world.
   */
  void Draw();
 private:
  std::shared_ptr<GameAssetManager> asset_manager;
  GLfloat speed = 0.1;
  GLfloat cameraX = 1.0;
  GLfloat cameraY = 1.0;
  glm::vec3 position = glm::vec3(1,1,1);
  glm::vec3 mdirection;
  glm::vec3 vright;
};
#endif // GAMEWORLD_H
