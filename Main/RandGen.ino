int RandGenerator(int lower, int upper)
{
  randomSeed(analogRead(0));
  int randNumber = random(lower, upper);
  return randNumber;
}
