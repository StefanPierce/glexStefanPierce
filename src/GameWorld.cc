#include "GameWorld.h"

GameWorld::GameWorld (ApplicationMode mode) {
  asset_manager = std::make_shared<GameAssetManager>(mode);

  
  genHeightMap();
  //generate 20x20 grid
  for(int i = 0; i < 50; i++){
     for(int ii = 0; ii<50; ii++){

	addCube(0.0 + i, -1.0 + heightMap[i][ii], 0.0+ii);

  }
  }

  player = std::make_shared<Player>(asset_manager->return_token());

}

void GameWorld::genHeightMap(){

for(int i = 0; i < 50; i++){
  for(int ii = 0; ii < 50; ii++){
        if(i < 2|| i > 47 || ii < 2|| ii > 47){
           heightMap[i][ii] = 0;
        }else{
	heightMap[i][ii] = rand() % 13;
        }
}
}

for(int i = 2; i < 48; i ++){
 for(int ii = 2; ii < 48; ii ++){
    int temp = 0;
    for(int t = -2; t < 2; t++){
       for(int tt = -2; tt < 2; tt++){
         temp += heightMap[t+i][tt+ii];
     }
    }
    heightMap[i][ii] = temp / 25;

 }
}

}

void GameWorld::addCube(GLfloat x, GLfloat y, GLfloat z){
       glm::vec3 temp = glm::vec3(x,y,z);

        if(player!= nullptr){
	  asset_manager->AddAsset(temp);
	}else{
	  asset_manager->AddAsset(temp);
	}

       
}

bool GameWorld::checkPlayerCollisions(){
    if(asset_manager->checkPlayerCollisions(player->getMin(), player->getMax())){

      return true;
    }
 	return false;
}

void GameWorld::increaseDist(){
player->increaseDist();
  glm::vec3 temp = player->getPosDir();
  asset_manager->ChangeCubePos((int)(temp.x + 0.5), (int)(temp.y + 0.5), (int)(temp.z + 0.5));

}

void GameWorld::decreaseDist(){
player->decreaseDist();
  glm::vec3 temp = player->getPosDir();
  asset_manager->ChangeCubePos((int)(temp.x + 0.5), (int)(temp.y + 0.5), (int)(temp.z + 0.5));
}

void GameWorld::moveU(){
player->moveU();
player->moveU();
if(checkPlayerCollisions()){
player->moveD();
}
}

void GameWorld::moveD(){
player->moveD();
if(checkPlayerCollisions()){
player->moveU();
}
}

//basic move functions
void GameWorld::moveF(){
player->moveF();
if(checkPlayerCollisions()){
player->moveB();
}
}

void GameWorld::moveB(){
player->moveB();
if(checkPlayerCollisions()){
player->moveF();
}
}

void GameWorld::moveL(){
player->moveL();
if(checkPlayerCollisions()){
player->moveR();
}
}

void GameWorld::moveR(){
 player->moveR();
if(checkPlayerCollisions()){
player->moveL();
}
}

void GameWorld::addBlock(){
 glm::vec3 temp = player->getPosDir();
 addCube((int)(temp.x + 0.5), (int)(temp.y + 0.5), (int)(temp.z  + 0.5));
 
 
}

void GameWorld::removeBlock(){
  glm::vec3 temp = player->getPosDir();
 asset_manager->removeBlock(glm::vec3((int)(temp.x + 0.5), (int)(temp.y + 0.5), (int)(temp.z + 0.5)));

}

void GameWorld::setCamera(GLfloat x, GLfloat y){
  player->setCamera(x,y);
  glm::vec3 temp = player->getPosDir();
  asset_manager->ChangeCubePos((int)(temp.x + 0.5), (int)(temp.y + 0.5), (int)(temp.z + 0.5));

}

void GameWorld::Draw() {
  moveD();
  player->Draw();
  asset_manager->Draw();
  //removeBlock();
}
