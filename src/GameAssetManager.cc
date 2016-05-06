#include "GameAssetManager.h"

/**
 * Creates a GameAssetManager to load the correct shaders based on the
 * ApplicationMode.
 */
GameAssetManager::GameAssetManager(ApplicationMode mode) {
  std::string vertex_shader("shaders/translate.vs");
  std::string fragment_shader("shaders/fragment.fs");
  
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

  for(int i = 0; i < 3; i++){
      for(int ii = 0; ii < 3; ii++){
	chunkPosx[i][ii] = i;
        chunkPosz[i][ii] = ii;	
	GenCubes(i, ii);
      }
   }

  program_token = CreateGLProgram(vertex_shader, fragment_shader);
}

void GameAssetManager::GenCubes(int x, int z){
   draw_list[x][z].clear();
   for(int i = 0; i < chunkSize; i ++){
	for(int ii = 0; ii < chunkSize; ii++){
		addCube(x, z, glm::vec3(i + 1, -1, ii + 1));
	}
   }

}
void GameAssetManager::addCube(int x, int z, glm::vec3 pos){
  GLfloat xt = (chunkPosx[x][z]) * chunkSize + pos.x;
  GLfloat zt = (chunkPosz[x][z]) * chunkSize + pos.z;
  draw_list[x][z].push_back(std::make_shared<CubeAsset>(xt, pos.y, zt));

}

bool GameAssetManager::checkPlayerCollisions(glm::vec3 pmin, glm::vec3 pmax){
	for(auto ga: draw_list[1][1]) {
          if(ga->collision(pmin, pmax)){
		return true;
	  }
        }

	for(auto ga: create_list){
		if(ga->collision(pmin, pmax)){
		return true;
	}
	}
	return false;
}

void GameAssetManager::updateActiveChunk(int x, int z){
     if(ACX < (x / chunkSize)){
	for (int i = 0; i < 3; i++){
              chunkPosx[0][i] = chunkPosx[1][i];
	      draw_list[0][i] = draw_list[1][i];
	      chunkPosx[1][i] = chunkPosx[2][i];
	      draw_list[1][i] = draw_list[2][i];
	      chunkPosx[2][i] = chunkPosx[2][i] + 1;
	      GenCubes(2, i);
	}
     }

     if(ACX > (x / chunkSize)){
	for (int i = 0; i < 3; i++){
              chunkPosx[2][i] = chunkPosx[1][i];
	      draw_list[2][i] = draw_list[1][i];
	      chunkPosx[1][i] = chunkPosx[0][i];
	      draw_list[1][i] = draw_list[0][i];
	      chunkPosx[0][i] = chunkPosx[0][i] - 1;
	      GenCubes(0, i);
	}
     }

     if(ACZ < (z / chunkSize)){
	for (int i = 0; i < 3; i++){
              chunkPosz[i][0] = chunkPosz[i][1];
	      draw_list[i][0] = draw_list[i][1];
	      chunkPosz[i][1] = chunkPosz[i][2];
	      draw_list[i][1] = draw_list[i][2];
	      chunkPosz[i][2] = chunkPosz[i][2] + 1;
	      GenCubes(i, 2);
	}
     }

    if(ACZ > (z / chunkSize)){
	for (int i = 0; i < 3; i++){
              chunkPosz[i][2] = chunkPosz[i][1];
	      draw_list[i][2] = draw_list[i][1];
	      chunkPosz[i][1] = chunkPosz[i][0];
	      draw_list[i][1] = draw_list[i][0];
	      chunkPosz[i][0] = chunkPosz[i][0] - 1;
	      GenCubes(i, 0);
	}
     }

     ACX = (int)(x / chunkSize);
     ACZ = (int)(z / chunkSize);
	std::cout << ACX << " : " << ACZ << std::endl;
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
void GameAssetManager::AddAsset(std::shared_ptr<GameAsset> the_asset) {
  for(auto ga: create_list){
     if (ga->collision(*the_asset)){
     return;
   }
  }
  create_list.push_back(the_asset);
}

void GameAssetManager::AddAsset(std::shared_ptr<GameAsset> the_asset, glm::vec3 min, glm::vec3 max) {
  if(the_asset->collision(min, max)==false){
  AddAsset(the_asset);
  }
}

void GameAssetManager::removeBlock(glm::vec3 posdir){

  int i = 0;

  for(auto ga: create_list){
    if(ga->collision(posdir, posdir)){
	create_list.erase(create_list.begin()+i);
	break;
    }
    i++;
  }
}

/**
 * Draws each GameAsset in the scene graph.
 */
void GameAssetManager::Draw(glm::vec3 pos) {

  for(int i = 0; i < 3; i++){
  for(int ii = 0; ii < 3; ii++){
  for(auto ga: draw_list[i][ii]) {
  //just checking collision passes back properly before tackling the maths!
     ga->Draw(program_token);
    }
  }
 }

  for(auto ga: create_list){
	ga->Draw(program_token);
  }

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
