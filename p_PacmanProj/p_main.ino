GameManager GM;


void reset()
{
  for(int i = 0; i<1628; i++)
  {
    if(mapPW[i]=='E')
    {
      mapPW[i] = '.';
    }
    else if(mapPW[i]=='H')
    {
      mapPW[i] = 'C';
    }
  }
  GM.ghosts[0].setupG(6.48648*71+0.4, 12.9);
  GM.ghosts[0].handleId = PINK_HANDLE;
  GM.ghosts[1].setupG(6.48648*2+0.4, 12.9);
  GM.ghosts[1].handleId = YELLOW_HANDLE;
  GM.ghosts[2].setupG(6.48648*2+0.4, 258.9);
  GM.ghosts[2].handleId = RED_HANDLE;
  GM.ghosts[3].setupG(6.48648*71+0.4, 258.9);
  GM.ghosts[3].handleId = BLUE_HANDLE;
  GM.pacman.setupPM();
  gameOver=false;
  score = 0;
  for(int i = 0; i<4; i++)
  {
    GM.scared[i]=false;
    GM.aggressive[i]=true;
  }
}

void setup()
{
  randomSeed(analogRead(0));
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  GD.begin();
  LOAD_ASSETS();
  GD.BitmapHandle(SADMAP_HANDLE); //Map
  
  GD.BitmapHandle(PCMSP_HANDLE); //Pacman
  GD.BitmapLayout(ARGB4, 2 * 13, 13);
  GD.BitmapHandle(RED_HANDLE); //Ghost1
  GD.BitmapHandle(YELLOW_HANDLE); //Ghost2
  GD.BitmapHandle(PINK_HANDLE); //Ghost3
  GD.BitmapHandle(BLUE_HANDLE); //Ghost4
  GD.BitmapHandle(WHITEGHOST_HANDLE); //whiteGhost
  GD.BitmapHandle(BLUEGHOST_HANDLE); //blueGhost
  GD.BitmapHandle(POWERP_HANDLE); //PowerPellet
  
  GM.ghosts[0].setupG(6.48648*71+0.4, 12.9);
  GM.ghosts[0].handleId = PINK_HANDLE;
  GM.ghosts[1].setupG(6.48648*2+0.4, 12.9);
  GM.ghosts[1].handleId = YELLOW_HANDLE;
  GM.ghosts[2].setupG(6.48648*2+0.4, 258.9);
  GM.ghosts[2].handleId = RED_HANDLE;
  GM.ghosts[3].setupG(6.48648*71+0.4, 258.9);
  GM.ghosts[3].handleId = BLUE_HANDLE;
  GM.pacman.setupPM();

  Serial.begin(9600);
}

void loop()
{
  float start = millis();
  GD.ClearColorRGB(0x103000);
  GD.Clear();
  GD.get_inputs();
  GD.Begin(BITMAPS);
  GD.cmd_setmatrix();
  GD.Vertex2ii(0, 0, SADMAP_HANDLE);
  GD.Vertex2ii(240, 0, SADMAP_HANDLE);
  GM.timer = millis();
  GM.pelletsF();
  if(!gameOver)
    GM.Update();
  else
  {
    if (GD.inputs.x != -32768) 
    {
      reset();
    }
  }
  //Serial.println(score);
  char k = char(score);
  GD.ColorRGB(0xffffff);
  GD.cmd_text(230, 103.5, 18, OPT_CENTER, "score: ");
  GD.cmd_number(263, 103.5, 18, OPT_CENTER, score);
  GD.swap();
  float endT = millis() - start;
  if(endT>34)
    endT = 34;
  delay(34-endT);
}
