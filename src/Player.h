#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include <GL/gl.h>


#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

#include "Player.h"

/**
 * The Player class is used to handle all thing relating to the cameras/characters position
 * and movement in the game.
 */
class Player {
 public:
  Player(GLuint);	
  void Draw();
  void moveF();
  void moveB();
  void moveL();
  void moveR();
  void setCamera(GLfloat, GLfloat);
  bool collision(GameAsset &a);
  glm::vec3 getMin();
  glm::vec3 getMax();
  
 private:
  GLfloat speed = 0.1;
  void updateMinMax();
  GLfloat cameraX = 1.0;
  GLfloat cameraY = 1.0;
  GLfloat height = 1.0;
  GLfloat width = 1.0;
  glm::vec3 min;
  glm::vec3 max;
  glm::vec3 position = glm::vec3(1,1,1);
  glm::vec3 mdirection;
  glm::vec3 vright;
  GLuint mod_loc;
  GLuint pro_loc;
  GLuint view_loc;

};

#endif // PLAYER_H
