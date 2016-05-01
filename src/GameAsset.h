#ifndef GAMEASSET_H
#define GAMEASSET_H

#include <iostream>

#include <GL/gl.h>

class GameAsset {
 public:
  virtual void Draw(GLuint) = 0;
  virtual bool collision(GameAsset &a){};

};

#endif
