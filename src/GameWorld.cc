#include "GameWorld.h"

GameWorld::GameWorld (ApplicationMode mode) {
  asset_manager = std::make_shared<GameAssetManager>(mode);

  player = std::make_shared<Player>(asset_manager->return_token());

  //generate 20x20 grid
  for(int i = 0; i < 20; i++){
     for(int ii = 0; ii<20; ii++){
	asset_manager->AddAsset(std::make_shared<CubeAsset>(0.0 + i, -1.0, 0.0+ii));
  }
  }
}


//basic move functions
void GameWorld::moveF(){
player->moveF();
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
