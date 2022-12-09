#ifndef PID_H
#define PID_H

class PID {
  private:
    double kP;
    double kI;
    double kD;
    int speed;
    int totalError;
    int derivative;
    int prevError;
    int Pvalue;
    int Ivalue;
    int Dvalue;
    unsigned long currentTime;
    unsigned long previousTime;


  public:
    int target;
    int value;
    PID(double kP, double kI, double kD);
    int motorSpeed(int setpoint, int value);
    void updateTime();
    void setP(double val);
    void setI(double val);
    void setD(double val);
    double elapsedTime;
};

#endif
