#ifndef GAMEASSET_H
#define GAMEASSET_H

#include <iostream>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class GameAsset {
 public:
  virtual void Draw(GLuint) = 0;
  private:
};

#endif
