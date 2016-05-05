#include "GameWorld.h"

GameWorld::GameWorld (ApplicationMode mode) {
  asset_manager = std::make_shared<GameAssetManager>(mode);

  

  //generate 20x20 grid
  for(int i = 0; i < 25; i++){
     for(int ii = 0; ii<25; ii++){
	addCube(0.0 + i, -1.0, 0.0+ii);
  }
  }

	for(int i = 0; i < 10; i++){
		addCube(5.0 + i, 0.0 + i, 0.0 + 1);
	}

  player = std::make_shared<Player>(asset_manager->return_token());
}

void GameWorld::addCube(GLfloat x, GLfloat y, GLfloat z){
       
        if(player!= nullptr){
	  asset_manager->AddAsset(std::make_shared<CubeAsset>(0.0 + x, 0.0 + y, 0.0+z), player->getMin(), player->getMax());
	}else{
	  asset_manager->AddAsset(std::make_shared<CubeAsset>(0.0 + x, 0.0 + y, 0.0+z));
	}
}

bool GameWorld::checkPlayerCollisions(){
    if(asset_manager->checkPlayerCollisions(player->getMin(), player->getMax())){

      return true;
    }
 	return false;
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
 addCube((int)temp.x, (int)temp.y, (int)temp.z);
 
 
}

void GameWorld::removeBlock(){
 asset_manager->removeBlock(player->getPosDir());

}

void GameWorld::setCamera(GLfloat x, GLfloat y){
  player->setCamera(x,y);

}

void GameWorld::Draw() {
  player->Draw();
  asset_manager->Draw();
}
