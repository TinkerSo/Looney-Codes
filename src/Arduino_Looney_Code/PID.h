#ifndef PID_H
#define PID_H

class PID {
  private:
    double kP;
    double kI;
    double kD;
    int computed_speed;
    int prevError;
    int totalError;
    int derivative;
    int Pvalue;
    int Ivalue;
    int Dvalue;
    unsigned long currentTime;
    unsigned long previousTime;


  public:
    int target;
    int value;
    PID(double P, double I, double D);
    int ComputeMotorSpeed(int val);
    void updateTime();
    void setP(double val);
    void setI(double val);
    void setD(double val);
    double elapsedTime;
};

#endif
