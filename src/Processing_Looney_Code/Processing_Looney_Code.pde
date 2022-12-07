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
int flag = 1;
int handleColor = 20;

int STOP = 300;
int FORWARD = 301;
int BACKWARD = 302;
int count = 0;

int send= 0;
int command = STOP;
int oldCommand = command;
int flagCommand = 0;

float threshold = 15;

Serial myPort;
LeapMotion leap;

void setup() {
  size(1920, 800, OPENGL);
  leap = new LeapMotion(this);
  textAlign(CENTER);
  myPort = new Serial(this, "COM4", 9600);
  myPort.bufferUntil('n');
}

void draw() {
  background(100);
  rectMode(CENTER);
  fill(handleColor);
  rect(960, 400, 1920, 100);
  
  handleColor = 20;

  // FPS
  int fps = leap.getFrameRate();
  fill(#00E310);
  text(fps + " fps", 20, 20);
  
  command = STOP;

  for (Hand hand : leap.getHands ()) {
    
    PVector middleTip = hand.getMiddleFinger().getRawPositionOfJointTip();
    PVector indexTip = hand.getIndexFinger().getRawPositionOfJointTip();
    PVector pinkyTip = hand.getPinkyFinger().getRawPositionOfJointTip();
    PVector handCenter = hand.getPosition();
    float handGrab = hand.getGrabStrength();
    
    if(handGrab>=0.9 && flag==1){
      initPosY = handYPosition(handCenter);;
      flag = 0;
    }
    else if(handGrab<0.9 && flag==0){
      flag = 1;
    }
    
    handleFinger(middleTip, "mdl");
    handleFinger(indexTip,"indx");
    handleFinger(pinkyTip,"pinky");
    
    if (handGrab >= 0.9) {
      handleColor = 255;
      difPosY = initPosY - handYPosition(handCenter);
      text(difPosY + " Y difference", 100, 40);
      send = int(difPosY);   
      
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
    
    hand.draw();
  
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
   text(send + " :command", 100, 70);
   rectMode(CENTER);
   fill(handleColor);
   rect(960, 400, 1920, 100);
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
