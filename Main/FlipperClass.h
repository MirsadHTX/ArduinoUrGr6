class Flipper 
{ 
  public:
  float currentState = 0;
  float lastState = 0;
  bool before = false;
  bool now = false;
  float limit = 0.8;  
  int onFlip(float input)
  {
    lastState = currentState;
    if(input > limit) 
    {
      currentState = 1;
      now = true;
    } 
    else if (input < -limit) 
    {
      currentState = -1; 
      now = true;
    }
    else
    {
      currentState = 0;
      now = false;
    }
    if(lastState != currentState && before == false && now == true) 
    {
      return currentState;
      before = true;
    }
    else
    {
      return 0;
    }
  }
};
