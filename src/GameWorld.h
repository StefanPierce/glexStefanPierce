#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>

#include <GL/gl.h>

#include "common.h"
#include "GameAssetManager.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Player.h"
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
  void addBlock();
  void removeBlock();

  /**
   * Calling Draw() will draw the entire world.
   */
  void Draw();
 private:
  std::shared_ptr<GameAssetManager> asset_manager;
  std::shared_ptr<Player> player;
  std::shared_ptr<CubeAsset> cube;
  bool checkPlayerCollisions();
  int count;
  int asset_position[25][25][25];
  void addCube(GLfloat, GLfloat, GLfloat);
  
};
#endif // GAMEWORLD_H
