#include "GameAssetManager.h"

/**
 * Creates a GameAssetManager to load the correct shaders based on the
 * ApplicationMode.
 */
GameAssetManager::GameAssetManager(ApplicationMode mode) {
  std::string vertex_shader("shaders/translate.vs");
  std::string fragment_shader("shaders/fragment.fs");
  cube = std::make_shared<CubeAsset>(0,0,0);
  Cubes = std::make_shared<CubeAsset>(0,0,0);

  switch(mode) {
  case ROTATE:
    vertex_shader = "shaders/rotate.vs";
    break;
  case SCALE:
    vertex_shader = "shaders/scale.vs";
    break;
  case TRANSFORM:
  default:
    break;
  };

  program_token = CreateGLProgram(vertex_shader, fragment_shader);
}

void GameAssetManager::ChangeCubePos(int x, int y, int z){
  playerCubePos = glm::vec3(x,y,z);

}

bool GameAssetManager::checkPlayerCollisions(glm::vec3 min, glm::vec3 max){

 for(auto cp: CubePositions){
 

     
    glm::vec3 min1 = cp - glm::vec3(0.5,0.5,0.5);
    glm::vec3 max1 = cp + glm::vec3(0.5,0.5,0.5);
    if(max.x > min1.x && min.x < max1.x &&
     max.y > min1.y && min.y < max1.y &&
     max.z > min1.z && min.z < max1.z){
    return true;
     }
  }

  return false;
}

GLuint GameAssetManager::return_token(){
	return program_token;
}

/**
 * Deletes a GameAssetManager, in particular it will clean up any modifications
 * to the OpenGL state.
 */
GameAssetManager::~GameAssetManager() {
  glDeleteProgram(program_token);
}

/**
 * Unimplemented copy constructor -- this means that the GameAssetManager
 * may not work as you'd expect when being copied.
 */
GameAssetManager::GameAssetManager(GameAssetManager const& the_manager) {
  // TODO: implement this
}

/**
 * Unimplemented move constructor -- this unimplemented method violates the
 * C++11 move semantics for GameAssetManager.
 */
GameAssetManager::GameAssetManager(GameAssetManager const&& the_manager) {
  // TODO: implement this
}

/**
 * Unimplemented assisgnment operator -- violates the expected semantics for
 * assignment in C++11.
 */
void GameAssetManager::operator=(GameAssetManager const& the_manager) {
  // TODO: implement this
}

/**
 * Adds a GameAsset to the scene graph.
 */

void GameAssetManager::AddAsset(glm::vec3 position){

  CubePositions.push_back(position);

}

bool GameAssetManager::collisions(glm::vec3 min, glm::vec3 max, glm::vec3 min1, glm::vec3 max1){
  if(max.x > min1.x && min.x < max1.x &&
     max.y > min1.y && min.y < max1.y &&
     max.z > min1.z && min.z < max1.z){
    return true;
  }

  return false;

}

void GameAssetManager::removeBlock(glm::vec3 posdir){

  int i = 0;

  for(auto cp: CubePositions){
   
    glm::vec3 min1 = cp - glm::vec3(0.5,0.5,0.5);
    glm::vec3 max1 = cp + glm::vec3(0.5,0.5,0.5);

    if(collisions(posdir, posdir, min1, max1)){
	CubePositions.erase(CubePositions.begin()+i);
	break;
    }
    i++;
  }
}

/**
 * Draws each GameAsset in the scene graph.
 */
void GameAssetManager::Draw() {

  /*
  for(auto ga: draw_list) {
  //just checking collision passes back properly before tackling the maths!
    ga->Draw(program_token);
  }*/
  GLuint anim_loc = glGetUniformLocation(program_token, "anim");


  for(auto cubes: CubePositions){
  glm::mat4 anim = glm::translate(cubes);
  glUniformMatrix4fv(anim_loc, 1, GL_FALSE, &anim[0][0]);
  Cubes->Draw(program_token); 
  }
  glm::mat4 anim = glm::translate(playerCubePos);
   glUniformMatrix4fv(anim_loc, 1, GL_FALSE, &anim[0][0]);
   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  cube->Draw(program_token);
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

}

/**
 * When given the contents of a vertex shader and fragment shader
 * GameAssetManager::CreateGLProgram will compile and link them.  This
 * implementation will exit with -1 error if an error is detected.
 *
 * @return the GL "token" referring to the gl program.
 */
GLuint GameAssetManager::CreateGLProgram(std::string & vertex_shader
                                         , std::string & fragment_shader) {
  auto v_shader_token = CreateGLESShader(GL_VERTEX_SHADER, vertex_shader);
  auto f_shader_token = CreateGLESShader(GL_FRAGMENT_SHADER, fragment_shader);

  GLint program_ok;

  GLuint program = glCreateProgram();

  glAttachShader(program, v_shader_token);
  glAttachShader(program, f_shader_token);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
  if (!program_ok) {
    std::cerr << "Failed to link shader program:" << std::endl;
    glDeleteProgram(program);
    exit(-1);
  }
  return program;
}

/**
 * When given a type of shader to construct and the contents of a shader,
 * GameAssetManager::CreateGLESShader will create the shader or exit with
 * error -1.
 *
 * @return the GL "token" for the requested shader.
 */
GLuint GameAssetManager::CreateGLESShader(GLenum type, std::string & shader) {
  GLuint shader_token;
  GLint shader_ok;
  auto source = ReadShader(shader);

  if (!source.first)
    return 0;

  shader_token = glCreateShader(type);
  glShaderSource(shader_token, 1, (const GLchar**)&source.first, &source.second);
  glCompileShader(shader_token);
  delete(source.first);

  glGetShaderiv(shader_token, GL_COMPILE_STATUS, &shader_ok);
  if (!shader_ok) {
    GLint maxLength = 0;
    glGetShaderiv(shader_token, GL_INFO_LOG_LENGTH, &maxLength);

    //The maxLength includes the NULL character
    std::vector<char> errorLog(maxLength);
    glGetShaderInfoLog(shader_token, maxLength, &maxLength, &errorLog[0]);

    //Provide the infolog in whatever manor you deem best.
    std::cerr << "Failed to compile " << shader << " with error code " << shader_ok << std::endl;
    for(auto c: errorLog) {
      std::cerr << c;
    }

    glDeleteShader(shader_token); //Don't leak the shader.
    exit(-1);
  }
  return shader_token;
}

/**
 * ReadShader reads the contents of a file and packs it into a null termintated
 * GLchar * which is suitable for sending to OpenGL.
 *
 * @return a pair consisting of the shader file contents and a holder for the
 *         OpenGL "token".
 */
std::pair<GLchar *, GLint> GameAssetManager::ReadShader(std::string & shader) {
  std::ifstream input_file;
  GLint length;
  input_file.open(shader, std::ios::in);

  input_file.seekg(0, std::ios::end);  // go to the end of the file
  length = input_file.tellg();    // get length of the file
  input_file.seekg(0, std::ios::beg);  // go to beginning of the file

  GLchar * buffer = new GLchar[length+1];
  input_file.read(buffer, length);
  buffer[length+1]='\0';  // Ensure null terminated

  input_file.close();
  return std::make_pair(buffer, length);
}
