#ifndef GAMEASSETMANAGER_H
#define GAMEASSETMANAGER_H

#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>

#include <GL/gl.h>

#include "common.h"
#include "GameAsset.h"
#include "CubeAsset.h"

/**
 * GameAssetManager is a container for GameAssets.  It also provides utility
 * functions to to create a simple OpenGL program that can be used to draw a
 * simple GameAsset.
 */
class GameAssetManager {
 public:
  explicit GameAssetManager(ApplicationMode); // constructor
  virtual ~GameAssetManager();
  GameAssetManager(GameAssetManager const&); // copy constructor
  GameAssetManager(GameAssetManager const&&); // move constructor
  void operator=(GameAssetManager const&); // assignment
  void AddAsset(std::shared_ptr<GameAsset>);
  void AddAsset(std::shared_ptr<GameAsset>, glm::vec3, glm::vec3);
  void AddAsset(glm::vec3);
  void Draw();
  void removeBlock(glm::vec3);
  void ChangeCubePos(int,int,int);
  GLuint return_token();
  bool checkPlayerCollisions(glm::vec3, glm::vec3);
  bool collisions(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
 private:
  GLuint CreateGLProgram(std::string &, std::string &);
  GLuint CreateGLESShader(GLenum, std::string &);
  // As this is private and we're writing to the GPU, we will use raw pointers.
  std::pair<GLchar *, GLint>  ReadShader(std::string &);
    std::shared_ptr<CubeAsset> cube;
  // The internal scene graph is a simple list.
  std::vector<std::shared_ptr<GameAsset>> draw_list;
  std::shared_ptr<GameAsset> Cubes;
  std::vector<glm::vec3> CubePositions;
  GLuint program_token;
  glm::vec3 playerCubePos;
};

#endif // GAMEASSETMANAGER_H
