#ifndef PID_H
#define PID_H

class PID{
  private:
    float kP;
    float kI;
    float kD;
    int speed;
    int error = 0;
    double lastError = 0;
    int totalError = 0;;
    int rateError = 0;
    int cumError = 0;
    unsigned long currentTime;
    unsigned long previousTime;
   

  public:
    int target;
    int value;
    PID(float kP, float kI, float kD);
    int motorSpeed(int setpoint, int value);
    void updateTime();
    void setP(float val);
    void setI(float val);
    void setD(float val); 
    double elapsedTime;  
};

#endif
