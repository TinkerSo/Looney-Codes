import de.voidplus.leapmotion.*;
import processing.serial.*;

float INTERACTION_SPACE_WIDTH = 200; // left-right from user
float INTERACTION_SPACE_DEPTH = 150; // away-and-toward user
float FINGER_DOT = 30;

float initPosY;
float initPosX;
float initPosYIndex;
float initPosYPinky;
float difPosY;
float difPosX;
float difPosYIndex;
float difPosYPinky;
   // float directionX;
    //float directionY;
    float yawdir;
    float initialyaw;
    float thresholdyaw = 10;
    
int flag = 1;
int handleColor = 20;

int STOP = 200;
int FORWARD = 201;
int BACKWARD = 202;
int LEFTTURN = 203;
int RIGHTTURN = 204;
int count = 0;
int totalError;

int handCount;

int send= 0;
int command = STOP;
int oldCommand = command;
int flagCommand = 0;

float threshold = 10;

Serial myPort;
LeapMotion leap;
PImage photo;
PImage handGrab_pic;

void setup() {
  size(1920, 1000, OPENGL);
  leap = new LeapMotion(this);
  photo = loadImage("logo.jpg");
  handGrab_pic = loadImage("grabbed_hand.png");
  textAlign(CENTER);
  myPort = new Serial(this, "COM4", 9600);
  myPort.bufferUntil('n');
}

void draw() {
  background(60,74,80);
  
  rotate(0);
  
  handCount = 0;
  
  /*rectMode(CENTER);
  textSize(12);
  fill(handleColor);
  rect(960, 400, 1920, 100);*/
  
  photo.resize(900, 600);
  image(photo, 450, 400);
  
  handleColor = 20;

  // FPS
  textSize(12);
  int fps = leap.getFrameRate();
  fill(#00E310);
  text(fps + " fps", 20, 20);
  
  command = STOP;

  for (Hand hand : leap.getHands ()) {
    handCount++;
    
    PVector middleTip = hand.getMiddleFinger().getRawPositionOfJointTip();
    PVector indexTip = hand.getIndexFinger().getRawPositionOfJointTip();
    PVector pinkyTip = hand.getPinkyFinger().getRawPositionOfJointTip();
    PVector handCenter = hand.getPosition();
    float handGrab = hand.getGrabStrength();
    //PVector palmDirection = hand.getRawDirection();
    //directionX = handXPosition(palmDirection);
    //directionY = handYPosition(palmDirection);
    //yawdir = hand.getYaw();
    
    
    if(handGrab>=0.9 && flag==1){
      initPosY = handYPosition(handCenter);
      initialyaw = hand.getYaw();
      flag = 0;
    }
    else if(handGrab<0.9 && flag==0){
      flag = 1;
    }
    
    handleFinger(middleTip, "mdl");
    handleFinger(indexTip,"indx");
    handleFinger(pinkyTip,"pinky");
    
    if (handGrab >= 0.9) {
      difPosY = initPosY - handYPosition(handCenter);
      //text(difPosY + " Y difference", 100, 40);
      send = int(difPosY);   
      yawdir = hand.getYaw() - initialyaw;

      handleColor = 255; 
      
      
    }
    
    
    
    if(difPosY<-threshold && handGrab >= 0.9){
      command = FORWARD;
    }
    else if(difPosY>threshold && handGrab >= 0.9){
      command = BACKWARD;
    }
    else{
      command = STOP;
    }
    
    if(abs(yawdir)>thresholdyaw &&  handGrab>= 0.9){
      if (yawdir < 0 ){
        command = LEFTTURN;
      }
      else{
        command = RIGHTTURN;
      }
    }
    
    textSize(12);
    hand.draw();
  
  }
  
  if(command == LEFTTURN || command == RIGHTTURN){
    send = abs(int(yawdir))+20;
  }
  
  if(command != oldCommand){
    myPort.write(command);
    oldCommand = command;
    send = command;
    count = 0;
  }
  /*if(count <=10){
    count++;
    send = command;
  }*/

   myPort.write(abs(send));
   
   //text(command + " :command", 100, 10);
   if(send<200){
     totalError += abs(send);
   }
   else{
     totalError = 0;
   }
   textSize(12);
   text(initialyaw + " : initial yaw", 100, 130);
   text(yawdir + " :yaw", 100, 110);
   text(totalError + " :total", 100, 90);
   text(command + " :command", 100, 70);
   text(send + " :sent", 100, 150);
   text(command + " :command", 100, 70);
   text(handCount + " :hand count", 100, 170);
   //text(directionX +" :xdirection", 100, 50);
   //text(directionY +" :ydirection", 100, 30);
   
   if(send<200){
     rectMode(CENTER);
     fill(handleColor);
     //rotate(HALF_PI/3);
     //rotate(yawdir/100);
     rect(960, send*3+400, 1920, 100);
   }
   else{
     rectMode(CENTER);
     fill(handleColor);
     //rotate(HALF_PI/3);
     rect(960, 400, 1920, 100);
   }
   
   if(flag == 0 && handCount == 1){
     textSize(60);
     fill(0, 408, 612);
     text("GRABBED", 900, 300); 
     if(send<200){
       //rotate(yawdir/100);
       image(handGrab_pic, 780, send*3+300);
     }
     else{
       image(handGrab_pic, 780, 300);
     }
   }
   
   if(command == STOP){
     textSize(30);
     fill(0, 408, 612);
     text("STOPPED", 900, 100); 
   }
   else if(command == FORWARD){
     textSize(30);
     fill(0, 408, 612);
     text("MOVING FORWARD", 900, 100); 
   }
   else if(command == BACKWARD){
     textSize(30);
     fill(0, 408, 612);
     text("MOVING BACKWARD", 900, 100); 
   }
   else if(command == LEFTTURN){
     textSize(30);
     fill(0, 408, 612);
     text("TURNING LEFT", 900, 100); 
   }
   else if(command == RIGHTTURN){
     textSize(30);
     fill(0, 408, 612);
     text("TURNING RIGHT", 900, 100); 
   }
   
   
   
   
   
}

void handleFinger(PVector pos, String id) {

  // map finger tip position to 2D surface
  float x = map(pos.x, -INTERACTION_SPACE_WIDTH,INTERACTION_SPACE_WIDTH, 0, width);
  float y = map(pos.z, -INTERACTION_SPACE_DEPTH,INTERACTION_SPACE_DEPTH, 0, height);

  fill(#00E310);
  noStroke();
  ellipse(x, y, FINGER_DOT, FINGER_DOT);

  // ID
  fill(0);
  textSize(12);
  text(id, x, y + 5);
  fill(#00E310);
  text("y: " + y, 100, 20);
}

float handYPosition(PVector pos) {

  // map finger tip position to 2D surface
  float y = map(pos.z, -INTERACTION_SPACE_DEPTH,INTERACTION_SPACE_DEPTH, 0, height);

  return y;
}
float handXPosition(PVector pos) {

  // map finger tip position to 2D surface
  float x = map(pos.x, -INTERACTION_SPACE_WIDTH,INTERACTION_SPACE_WIDTH, 0, width);

  return x;
}
