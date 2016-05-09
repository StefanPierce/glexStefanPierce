#include "GameWorld.h"

GameWorld::GameWorld (ApplicationMode mode) {
  asset_manager = std::make_shared<GameAssetManager>(mode);

  

  //generate 20x20 grid
  for(int i = 0; i < 50; i++){
     for(int ii = 0; ii<50; ii++){
	addCube(0.0 + i, -1.0, 0.0+ii);
  }
  }

	for(int i = 0; i < 10; i++){
		addCube(5.0 + i, 0.0 + i, 0.0 + 1);
	}

  player = std::make_shared<Player>(asset_manager->return_token());
  cube = std::make_shared<CubeAsset>(0,0,0);
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

}

void GameWorld::decreaseDist(){
player->decreaseDist();
}

void GameWorld::moveU(){
//player->moveU();
//player->moveU();
//if(checkPlayerCollisions()){
//player->moveD();
//}
}

void GameWorld::moveD(){
//player->moveD();
//if(checkPlayerCollisions()){
//player->moveU();
//}
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
  cube->ChangePos((int)(temp.x + 0.5), (int)(temp.y + 0.5), (int)(temp.z + 0.5));

}

void GameWorld::Draw() {
  moveD();
  player->Draw();
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  cube->Draw(asset_manager->return_token());
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  asset_manager->Draw();
  //removeBlock();
}
