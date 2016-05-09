#include "GameAsset.h"

GameAsset::GameAsset(){

}

void GameAsset::genMinMax(GLfloat x, GLfloat y, GLfloat z){
 min = glm::vec3(x - 0.5, y - 0.5, z - 0.5);
 max = glm::vec3(x + 0.5, y + 0.5, z + 0.5);
 pos = glm::vec3(x, y, z);
}

/*bool GameAsset::closeToDraw(glm::vec3 pos1){
  if(pos.x > pos1.x - 20 && pos.x < pos1.x + 20
     && pos.z > pos1.z - 20 && pos.z < pos1.z + 20){
   return true;
  }
  return false;
}*/
glm::vec3 GameAsset::getAssetPos(){
 return pos;
}

glm::vec3 GameAsset::getMin(){
  return min;
}

glm::vec3 GameAsset::getMax(){
  return max;
}

bool GameAsset::collision(GameAsset &a){
  glm::vec3 min1 = a.getMin();
  glm::vec3 max1 = a.getMax();

  return collision(min1, max1);
}



bool GameAsset::collision(glm::vec3 min1, glm::vec3 max1){

  //if(closeToDraw(min1)){
  if(max.x > min1.x && min.x < max1.x &&
     max.y > min1.y && min.y < max1.y &&
     max.z > min1.z && min.z < max1.z){
  return true;
  
}
	
 return false;
}
