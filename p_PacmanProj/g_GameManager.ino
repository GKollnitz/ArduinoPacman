class GameManager
{
  public:
  bool right[4], left[4], up[4], down[4], aggressive[4]= {true, true, true, true}, scared[4]={false,false,false,false};
  float timer = 0;
  float PUTimer = 0;
  Pacman pacman;
  Ghost ghosts[4];
  
  void Update();
  void setupMap();
  void gameOverCheck();
  void pelletsF();
  vector2d calcGhostPath(Ghost, int) __attribute__((__optimize__("O2")));
  bool validMove(vector2d, vector2d);
};

void GameManager::gameOverCheck()
{
  int indxpx = pacman.pos.x/12.3636;
  int indxpy = pacman.pos.y/12.3636;
  for(int i = 0; i<4; i++)
  {
    int indxx = ghosts[i].pos.x/12.3636;
    int indxy = ghosts[i].pos.y/12.3636;
    if(indxpx == indxx && indxpy == indxy)
    {
      if(aggressive[i] && !scared[i])
      {
        gameOver = true;
        GD.sample(PACMAN_DEATH, PACMAN_DEATH_LENGTH, PACMAN_DEATH_FREQ, ADPCM_SAMPLES); 

      }
      else if(!aggressive[i] && !scared[i])
      {
        ghosts[i].scareTimer = millis();
        GD.sample(PACMAN_EATGHOST, PACMAN_EATGHOST_LENGTH, PACMAN_EATGHOST_FREQ, ADPCM_SAMPLES); 
        scared[i]=true;
      }
    }
  }
}

void GameManager::pelletsF()
{
  for(int i = 0; i<22; i++)
  {
    for(int j = 0; j<74; j++)
    {
      if(mapPW[i*74+j]=='.')
      {
        GD.PointSize(16 * 2); // means 30 pixels
        GD.Begin(POINTS);
        GD.ColorRGB(0xffff00); 
        GD.Vertex2ii(j*6.5, i*12.9);
      }
      else if(mapPW[i*74+j]=='C')
      {
        GD.Begin(BITMAPS);
        GD.Vertex2ii(j*6.5-5, i*12.9-5, POWERP_HANDLE);
      }
    }
  }
}

vector2d GameManager::calcGhostPath(Ghost ghost, int ind)
{
  int indxx = ghost.pos.x/6.48648;
  int indxy = ghost.pos.y/12.3636;
  if(mapP[indxy*74+indxx]=='X' && abs(ghost.pos.x-indxx*6.5)<1 && abs(ghost.pos.y-(indxy*12.9))<1)
  {
    bool rightPossible = false, leftPossible = false, upPossible = false, downPossible = false;
    if(mapP[(indxy+1)*74+indxx]!='0')
      downPossible = true;
    if(mapP[(indxy-1)*74+indxx]!='0')
      upPossible = true;
    if(mapP[indxy*74+indxx+1]!='0')
      rightPossible = true;
    if(mapP[indxy*74+indxx-1]!='0')
      leftPossible = true;
    
    float dDif, uDif, lDif, rDif;
    if(aggressive[ind])
    {
      dDif = 999, uDif = 999, lDif = 999, rDif = 999;
      if(downPossible && up[ind] == false)
        dDif = sqrt(pow(abs(ghost.pos.x-pacman.pos.x),2) + pow(abs(ghost.pos.y+1-pacman.pos.y),2));
      if(upPossible && down[ind] == false)
        uDif = sqrt(pow(abs(ghost.pos.x-pacman.pos.x),2) + pow(abs(ghost.pos.y-1-pacman.pos.y),2));
      if(leftPossible && right[ind] == false)
        lDif = sqrt(pow(abs(ghost.pos.x-1-pacman.pos.x),2) + pow(abs(ghost.pos.y-pacman.pos.y),2));
      if(rightPossible && left[ind] == false)
        rDif = sqrt(pow(abs(ghost.pos.x+1-pacman.pos.x),2) + pow(abs(ghost.pos.y-pacman.pos.y),2));
        if(lDif < rDif && lDif < uDif && lDif < dDif)
      {
        left[ind] = true;
        right[ind] = false;
        up[ind] = false;
        down[ind] = false;
      }
      else if(rDif < lDif && rDif < uDif && rDif < dDif)
      {
        left[ind] = false;
        right[ind] = true;
        up[ind] = false;
        down[ind] = false;
      }
      else if(uDif < lDif && uDif < rDif && uDif < dDif)
      {
        left[ind] = false;
        right[ind] = false;
        up[ind] = true;
        down[ind] = false;
      }
      else if(dDif < lDif && dDif < uDif && dDif < rDif)
      {
        left[ind] = false;
        right[ind] = false;
        up[ind] = false;
        down[ind] = true;
      }
    }
    else if(!aggressive[ind])
    {
      dDif = 0, uDif = 0, lDif = 0, rDif = 0;
      if(downPossible && up[ind] == false)
        dDif = sqrt(pow(abs(ghost.pos.x-pacman.pos.x),2) + pow(abs(ghost.pos.y+1-pacman.pos.y),2));
      if(upPossible && down[ind] == false)
        uDif = sqrt(pow(abs(ghost.pos.x-pacman.pos.x),2) + pow(abs(ghost.pos.y-1-pacman.pos.y),2));
      if(leftPossible && right[ind] == false)
        lDif = sqrt(pow(abs(ghost.pos.x-1-pacman.pos.x),2) + pow(abs(ghost.pos.y-pacman.pos.y),2));
      if(rightPossible && left[ind] == false)
        rDif = sqrt(pow(abs(ghost.pos.x+1-pacman.pos.x),2) + pow(abs(ghost.pos.y-pacman.pos.y),2));
      if(lDif > rDif && lDif > uDif && lDif > dDif)
      {
        left[ind] = true;
        right[ind] = false;
        up[ind] = false;
        down[ind] = false;
      }
      else if(rDif > lDif && rDif > uDif && rDif > dDif)
      {
        left[ind] = false;
        right[ind] = true;
        up[ind] = false;
        down[ind] = false;
      }
      else if(uDif > lDif && uDif > rDif && uDif > dDif)
      {
        left[ind] = false;
        right[ind] = false;
        up[ind] = true;
        down[ind] = false;
      }
      else if(dDif > lDif && dDif > uDif && dDif > rDif)
      {
        left[ind] = false;
        right[ind] = false;
        up[ind] = false;
        down[ind] = true;
      }
    }
  }
  vector2d newTar = ghost.pos;
  if(ghost.pos.x > 478)
  {
    newTar.x = 2;
  }
  else if(ghost.pos.x < 2)
  {
    newTar.x = 478;
  }
  else if(right[ind])
  {
    newTar.x = ghost.pos.x+1;
    newTar.y = ghost.pos.y;   
  }
  else if(left[ind])
  {
    newTar.x = ghost.pos.x-1;
    newTar.y = ghost.pos.y;    
  }
  else if(up[ind])
  {
    newTar.x = ghost.pos.x;
    newTar.y = ghost.pos.y-1;    
  }
  else if(down[ind])
  {
    newTar.x = ghost.pos.x;
    newTar.y = ghost.pos.y+1;    
  }
   return newTar;
}

void GameManager::Update()
{
  if(!aggressive[0])
  {
    if(PUTimer+15000 < timer)
    {
      for(int i = 0; i<4; i++)
      {
        aggressive[i] = true;
      }
    }
  }
  for(int i = 0; i<4; i++)
  {
    if(scared[i])
    {
      if(ghosts[i].scareTimer+30000 < timer)
      {
        scared[i]=false;
      }
    }
  }
  gameOverCheck();
  pacman.Update();
  if(validMove(pacman.pos, pacman.target))
  {
    GD.Begin(BITMAPS);
    GD.cmd_setmatrix();
    pacman.pos = pacman.target;
    GD.Vertex2ii(pacman.pos.x-4.5, pacman.pos.y-4.5, PCMSP_HANDLE, pacman.handle2);
    
    int indxx = pacman.pos.x/6.48648;
    int indxy = pacman.pos.y/12.3636;
    
    if(mapPW[indxy*74+indxx]=='.')
    {
      score+=1;
      GD.sample(PACMAN_CHOMP, PACMAN_CHOMP_LENGTH, PACMAN_CHOMP_FREQ, ADPCM_SAMPLES); 
      mapPW[indxy*74+indxx]='E';
    }
    else if(mapPW[indxy*74+indxx]=='C')
    {
      PUTimer = millis();
      mapPW[indxy*74+indxx]='H';
      GD.sample(PACMAN_EATFRUIT, PACMAN_EATFRUIT_LENGTH, PACMAN_EATFRUIT_FREQ, ADPCM_SAMPLES); 
      for(int i = 0; i<4; i++)
      {
        aggressive[i] = false;
      }
    }
  }
  else
  {
    GD.Begin(BITMAPS);
    GD.cmd_setmatrix();
    GD.Vertex2ii(pacman.pos.x-4.5, pacman.pos.y-4.5, PCMSP_HANDLE, pacman.handle2);
  }

  for(int i = 0; i<4; i++)
  {
    if(scared[i])
    {
      ghosts[i].scareUpdate();
    }
    else if(!scared[i] && !aggressive[i])
    {
      ghosts[i].target = calcGhostPath(ghosts[i], i);
      ghosts[i].runUpdate();
    }
    else if(aggressive[i])
    {
      ghosts[i].target = calcGhostPath(ghosts[i], i);
      ghosts[i].Update(); 
    }
  }
};


 
bool GameManager::validMove(vector2d pos, vector2d target)
{
  if(!aggressive[0])
    pacman.speedPM = 2;
  else
    pacman.speedPM = 1;
  int indxx = pos.x/6.48648;
  int indxy = pos.y/12.3636;
  if(mapP[indxy*74+indxx]=='X')
  {
    if(pacman.rightW)
    {
      pacman.right = true;
      pacman.left = false;
      pacman.up = false;
      pacman.down = false;
 
    }
    else if(pacman.leftW)
    {
      pacman.right = false;
      pacman.left = true;
      pacman.up = false;
      pacman.down = false;
    }
    else if(pacman.upW)
    {
      pacman.right = false;
      pacman.left = false;
      pacman.up = true;
      pacman.down = false;
    }
    else if(pacman.downW)
    {
      pacman.right = false;
      pacman.left = false;
      pacman.up = false;
      pacman.down = true;
    }
  }
  else
  {
    if(pacman.rightW && pacman.left)
    {
      pacman.right = true;
      pacman.left = false;
      pacman.up = false;
      pacman.down = false;
  
    }
    else if(pacman.leftW && pacman.right)
    {
      pacman.right = false;
      pacman.left = true;
      pacman.up = false;
      pacman.down = false;
    }
    else if(pacman.upW && pacman.down)
    {
      pacman.right = false;
      pacman.left = false;
      pacman.up = true;
      pacman.down = false;

    }
    else if(pacman.downW && pacman.up)
    {
      pacman.right = false;
      pacman.left = false;
      pacman.up = false;
      pacman.down = true;
    }
  }

  if(pacman.pos.x > 478)
  {
    pacman.target.x = 2;
  }
  else if(pacman.pos.x < 2)
  {
    pacman.target.x = 478;
  }
  else if(pacman.right)
  {
    pacman.target.x = pacman.pos.x+pacman.speedPM;
    pacman.target.y = pacman.pos.y;   
  }
  else if(pacman.left)
  {
    pacman.target.x = pacman.pos.x-pacman.speedPM;
    pacman.target.y = pacman.pos.y;    
  }
  else if(pacman.up)
  {
    pacman.target.x = pacman.pos.x;
    pacman.target.y = pacman.pos.y-pacman.speedPM;    
  }
  else if(pacman.down)
  {
    pacman.target.x = pacman.pos.x;
    pacman.target.y = pacman.pos.y+pacman.speedPM;    
  }

  int yInd = pacman.target.x/6.48648;
  int xInd = pacman.target.y/12.3636;
  return (mapP[xInd*74+yInd]!='0');
};
