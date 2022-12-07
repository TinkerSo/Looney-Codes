#ifndef PID_H
#define PID_H

class PID{
  private:
    float kP;
    float kI;
    float kD;
    int error;
    int totalError;
    int derivative;
    int integral;

  public:
    int target;
    int value;
    PID(float kP, float kI, float kD);
    int motorSpeed(int target, int value);
    void setP(float kP);
    void setI(float kI);
    void setD(float kD);   
};

#endif
