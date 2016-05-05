#ifndef CUBEASSET_H
#define CUBEASSET_H

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

class CubeAsset : public GameAsset {
 public:
  CubeAsset(GLfloat x, GLfloat y, GLfloat z);
  ~CubeAsset();
  virtual void Draw(GLuint);
  void ChangePos(GLfloat x, GLfloat y, GLfloat z);
 private:
  GLuint element_buffer_length;
  GLuint vertex_buffer_token, element_buffer_token;
  GLuint colorbuffer;
  float angle = 0;
  GLfloat tX = 0;
  GLfloat tY = 0;
  GLfloat tZ = 0;
  glm::mat4 anim;




};

#endif // CUBEASSET_H
