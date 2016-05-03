#include "GameWorld.h"

GameWorld::GameWorld (ApplicationMode mode) {
  asset_manager = std::make_shared<GameAssetManager>(mode);

  player = std::make_shared<Player>(asset_manager->return_token());

  //generate 20x20 grid
  for(int i = 0; i < 25; i++){
     for(int ii = 0; ii<25; ii++){
	addCube(0.0 + i, -1.0, 0.0+ii);
  }
  }

	for(int i = 0; i < 10; i++){
		addCube(0.0 + i, 0.0, 0.0 + 1);
	}
}

void GameWorld::addCube(GLfloat x, GLfloat y, GLfloat z){
	asset_manager->AddAsset(std::make_shared<CubeAsset>(0.0 + x, 0.0 + y, 0.0+z));
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
checkPlayerCollisions();
}

void GameWorld::moveB(){
player->moveB();
}

void GameWorld::moveL(){
player->moveL();
}

void GameWorld::moveR(){
 player->moveR();
}



void GameWorld::setCamera(GLfloat x, GLfloat y){
player->setCamera(x,y);

}

void GameWorld::Draw() {
  player->Draw();
  asset_manager->Draw();
}
