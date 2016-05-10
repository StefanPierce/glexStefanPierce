#include "GameWorld.h"

Player::Player(GLuint program_token){

  mod_loc = glGetUniformLocation(program_token, "Model");
  pro_loc = glGetUniformLocation(program_token, "Projection");
  view_loc = glGetUniformLocation(program_token, "View");


}

void Player::moveU(){
  position+=glm::vec3(0, 0.1, 0);
  updateMinMax();
}

void Player::moveD(){
    position-=glm::vec3(0, 0.1, 0);
  updateMinMax();
}
//basic move functions
void Player::moveF(){
  position+=mdirection*speed;
  updateMinMax();
}

void Player::moveB(){
  position-=mdirection*speed;
  updateMinMax();
}

void Player::moveL(){
 position-=vright*speed;
 updateMinMax();
}

void Player::moveR(){
 position+=vright*speed;
 updateMinMax();
}

void Player::updateMinMax(){
   min = position - glm::vec3(0.3,height,0.3);
   max = position + glm::vec3(0.3,0.5,0.3);
}

glm::vec3 Player::getMin(){
  return min;
}

glm::vec3 Player::getMax(){
  return max;
}

glm::vec3 Player::getPosDir(){
 return (position + direction * glm::vec3(blockDistance,blockDistance,blockDistance));
}

void Player::increaseDist(){
 blockDistance += 0.5;
}
 
void Player::decreaseDist(){
 blockDistance -= 0.5;
 if(blockDistance < 2){
 	blockDistance = 2;
 }
}

void Player::setCamera(GLfloat x, GLfloat y){
cameraX-= x;
cameraY-= y;

//used just to make sure camera doesnt flip when looking to far up/down
if(cameraY > 1.5){
		cameraY = 1.5;
        }

        if(cameraY < -1.5){
		cameraY = -1.5;
        }

}

void Player::Draw() {
   
   //would use this direction in movement if we wanted free cam, but we dont so i use
   //it to work out the direction of camera
   direction = glm::vec3(
      cos(cameraY) * sin(cameraX),
      sin(cameraY),
      cos(cameraY) * cos(cameraX)
   );

   //same as above but as the second value is 0, if we add or minus this from
   //position, the camera would never move up or down
    mdirection = glm::vec3(
      cos(cameraY) * sin(cameraX),
      0,
      cos(cameraX) * cos(cameraY)
   );

    //works out movement for moving right (and in turn left)
    vright = glm::vec3(
      sin(cameraX - 3.14f/2.0f),
      0,
      cos(cameraX - 3.14f/2.0f)
   );

		
    
  glm::vec3 vup = glm::cross( vright, direction );
  //set FOV etc
  glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

  //used as basically the camera view, 
  glm::mat4 View = glm::lookAt(
				position,		//position
				position + direction,	//position of center of
							//where we are looking at
				vup			//
        		      );


  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  glm::mat4 Model(1.0f);
  //send Projection, view and model to shader
  glUniformMatrix4fv(pro_loc, 1, GL_FALSE, &Projection[0][0]);
  glUniformMatrix4fv(view_loc, 1, GL_FALSE, &View[0][0]);
  glUniformMatrix4fv(mod_loc, 1, GL_FALSE, &Model[0][0]);
}
