const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A8; // analog pin connected to X output
const int Y_pin = A10; // analog pin connected to Y output

class Pacman
{
public:
  int pFrame = 0;
  int speedPM = 1;
  bool right = false, left = false, up = false, down = false;
  bool rightW = false, leftW = false, upW = false, downW = false;
  int handle2 = 0;
  bool powerUp = false;
  vector2d pos;
  vector2d target;
  void setupPM();
  void setDir();
  void setHandle();
  void Update()
  {
    setHandle();
    setDir();
  };
};

void Pacman::setupPM()
{
  pos.x = 158;
  pos.y = 135;
  target.x = 158;
  target.y = 135;
  right = false, left = false, up = false, down = true;
  rightW = false, leftW = false, upW = false, downW = false;
  speedPM = 1;
};

void Pacman::setHandle()
{
  pFrame++;
  if(right)
  {
    if(pFrame>6/speedPM)
      handle2 = 1;
    else
      handle2 = 5;
  }
  else if(left)
  {
    if(pFrame>6/speedPM)
      handle2 = 0;
    else
      handle2 = 4;
    
  }
  else if(up)
  {
    if(pFrame>6/speedPM)
      handle2 = 2;
    else
      handle2 = 6;    
  }
  else if(down)
  {
    if(pFrame>6/speedPM)
      handle2 = 3;
    else
      handle2 = 7;    
  }
  if(pFrame>12/speedPM)
    pFrame = 0;    
};

void Pacman::setDir()
{
    if(analogRead(X_pin)==1023)
    {
      rightW = true;
      leftW = false, upW = false, downW = false;
    }
    else if(analogRead(X_pin)==0)
    {
      leftW = true;
      rightW = false, upW = false, downW = false;
    }
      if(analogRead(Y_pin)==1023)
    {
      upW = true;
      rightW = false, downW = false, leftW = false;
    }
    else if(analogRead(Y_pin)==0)
    {
      downW = true;
      rightW = false, leftW = false, upW = false;
    }
};


