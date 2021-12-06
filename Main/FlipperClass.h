class Flipper 
{ 
  public:
  float currentState = 0;
  float lastState = 0;
  float lastinput = 0.0;
  bool before = false;
  bool now = false;
  float limit = 0.8;  
  int onFlip(float input)
  {
    
    if(input > lastinput + limit) 
    {
      lastinput = input;
      return 1;
    } 
    else if (input < lastinput - limit) 
    {
      lastinput = input;
      return -1;
    }
    else
    {
      lastinput = input;
      return 0;
    }
    return 0;
  }
};
