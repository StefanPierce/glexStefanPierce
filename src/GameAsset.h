#ifndef GAMEASSET_H
#define GAMEASSET_H

#include <iostream>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class GameAsset {
 public:
  GameAsset();
  virtual void Draw(GLuint) = 0;
  bool collision(glm::vec3 min1, glm::vec3 max1);
  bool collision(GameAsset &a);
  bool closeToDraw(glm::vec3);
  void genMinMax(GLfloat, GLfloat, GLfloat);
  glm::vec3 getAssetPos();
  glm::vec3 getMin();
  glm::vec3 getMax();
  private:
  glm::vec3 max;
  glm::vec3 min;
  glm::vec3 pos;
};

#endif
