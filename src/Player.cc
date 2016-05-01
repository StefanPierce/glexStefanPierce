#include "GameWorld.h"

Player::Player(){

}


//basic move functions
void Player::moveF(){
  position+=mdirection*speed;
}

void Player::moveB(){
  position-=mdirection*speed;
}

void Player::moveL(){
 position-=vright*speed;
}

void Player::moveR(){
 position+=vright*speed;
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
   glm::vec3 direction(
      cos(cameraY) * sin(cameraX),
      sin(cameraY),
      cos(cameraY) * cos(cameraX)
   );

   //same as above but as the second value is 0, if we add or minus this from
   //position, the camera would never move up or down
   glm::vec3 mdirection1(
      cos(cameraY) * sin(cameraX),
      0,
      cos(cameraX) * cos(cameraY)
   );
   //store into the global direction(possibly a better way to do this)
   mdirection = mdirection1;

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

  glm::mat4 Model(1.0f);
  //send Projection, view and model to shader
  glUniformMatrix4fv(0, 1, GL_FALSE, &Projection[0][0]);
  glUniformMatrix4fv(1, 1, GL_FALSE, &View[0][0]);
  glUniformMatrix4fv(2, 1, GL_FALSE, &Model[0][0]);
}
