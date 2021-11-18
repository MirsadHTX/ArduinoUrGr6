class Flipper 
{ 
  public:
    float currentState = 0;
    float lastState = 0;   
    float limit = 0.8;  
    int onFlip(int input)
    {
      lastState = currentState;
      if(input > limit) {
        currentState = 1;
      } 
      else if (input < -limit) 
      {
        currentState = -1;
      }
      else
      {
        currentState = 0;
      }
      if(lastState != currentState) 
      {
        currentState;
      }
      else
      {
        return 0;
      }
    }
    int RandGenerator(int lower, int upper)
    {
      randomSeed(analogRead(0));
      int randNumber = random(lower, upper);
      return randNumber;
    }
};
