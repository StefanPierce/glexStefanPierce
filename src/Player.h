#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include <GL/gl.h>


#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Player.h"

/**
 * The Player class is used to handle all thing relating to the cameras/characters position
 * and movement in the game.
 */
class Player {
 public:
  Player();	
  void Draw();
  void moveF();
  void moveB();
  void moveL();
  void moveR();
  void setCamera(GLfloat, GLfloat);
 private:
  GLfloat speed = 0.1;
  GLfloat cameraX = 1.0;
  GLfloat cameraY = 1.0;
  glm::vec3 position = glm::vec3(1,1,1);
  glm::vec3 mdirection;
  glm::vec3 vright;

};

#endif // PLAYER_H
