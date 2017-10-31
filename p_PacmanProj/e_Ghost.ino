class Ghost
{
public:
  bool right = false, left = false, up = false, down = false;
  int handleId = 0;
  float scareTimer = 0;
  vector2d pos;
  vector2d target;
  void setDir();
  void setupG(float, float);
  void Update();
  void scareUpdate();
  void runUpdate();
};

void Ghost::Update()
{
  GD.Begin(BITMAPS);
  GD.cmd_setmatrix();
  pos = target;
  GD.Vertex2ii(pos.x-4.5, pos.y-4.5, handleId);
};

void Ghost::scareUpdate()
{
  GD.Begin(BITMAPS);
  GD.cmd_setmatrix();
  pos = target;
  GD.Vertex2ii(pos.x-4.5, pos.y-4.5, WHITEGHOST_HANDLE);
};

void Ghost::runUpdate()
{
  GD.Begin(BITMAPS);
  GD.cmd_setmatrix();
  pos = target;
  GD.Vertex2ii(pos.x-4.5, pos.y-4.5, BLUEGHOST_HANDLE);
};
  
void Ghost::setupG(float x, float y)
{
  pos.x = x;
  pos.y = y;
  target.x = x;
  target.y = y;
};

