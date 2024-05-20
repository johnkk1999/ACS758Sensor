typedef struct{
  float coeff[2];
  float out[2];
}RcLowPass;

typedef struct{
  float coeff;
  float out[2];
}RcHighPass;
class bandPassFilter{

 public:
   void RcFilterInit(float, float,float);
   float RcFilterUpdate(float);
  private:
  RcLowPass filtL;
  RcHighPass filtH;
    
};
void bandPassFilter::RcFilterInit(float sampTime, float lowFreq, float highFreq)
{
  //low pass filter
  float RC = 1/(6.2831853072f*lowFreq);
  filtL.coeff[0] = sampTime/(sampTime+RC);
  filtL.coeff[1] = RC /(sampTime + RC);
  
  //high pass filter
  float RC2 = 1/(6.2831853072f*highFreq);
  filtH.coeff = RC2/(sampTime+RC2);
  //initial outputs to zero
  filtL.out[0] = 0.0f;
  filtL.out[1] = 0.0f;
  filtH.out[0] = 0.0f;
  filtH.out[1] = 0.0f;

}
float bandPassFilter::RcFilterUpdate(float input)
{
  //low pass filter
  filtL.out[1] = filtL.out[0];
  filtL.out[0] = filtL.coeff[0] * input + filtL.coeff[1] * filtL.out[1];

  //high pass filter

  filtH.out[1] = filtH.out[0];
  filtH.out[0] = filtH.coeff* (filtL.out[0] - filtL.out[1]) + filtH.coeff*filtH.out[1];
  return filtH.out[0];
  }
