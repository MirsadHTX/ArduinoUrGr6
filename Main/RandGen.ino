int RandGenerator(int lower, int upper)
{
  randomSeed(analogRead(0));
  int randNumber = random(lower, upper);
  return randNumber;
}

char classState()
{
  const char *classList[] = {"Anders", "Emil", "Fahmi", "Freja", "Gustav W", "Gustav E", "Haris", "Ismail", "Jabriil", "Jacob", "Ludvig", "Jeppe", "Jonatan", "Kasper", "Lovro", "Mathias", "Mie", "Mohammad", "Nelisa", "Nikhil", "Rasmus", "Robert", "Pernille", "Sarah", "Silas", "Simon", "Thøger", "Tobias", "Taaha", "William"};
  int pupilNumber = RandGenerator(0,29);
  char pupil = *classList[pupilNumber];
  return pupil;
}
