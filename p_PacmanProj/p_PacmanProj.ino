//Copyright @Gunnar Kollnitz, gunkol-5@student.ltu.se
#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include "assets.h"
bool gameOver = false;
int score = 0;
int delayD = 17;
int bitmapHandleIndx = 0;
//480 * 272 -> 74*22

//480 * 272 -> 74*22
char mapP[1628] = "0000000000000000000000000000000000000000000000000000000000000000000000000000X     X       X000X       X     X0000X     X       X000X       X     X0000 00000 0000000 000 0000000 00000 0000 00000 0000000 000 0000000 00000 0000 00000 0000000 000 0000000 00000 0000 00000 0000000 000 0000000 00000 0000X     X   X   X   X   X   X     X0000X     X   X   X   X   X   X     X0000 00000 000 00000000000 000 00000 0000 00000 000 00000000000 000 00000 0000X     X000X   X000X   X000X     X0000X     X000X   X000X   X000X     X0000000000 0000000 000 0000000 0000000000000000 0000000 000 0000000 00000000      00 000X   X   X   X000 000          000 000X   X   X   X000 00      00000000 000 00000  0000 000 0000000000000000 000 0000  00000 000 00000000        X   X000     000X   X                X   X000     000X   X        00000000 000 00000000000 000 0000000000000000 000 00000000000 000 00000000      00 000X           X000 000          000 000X           X000 00      00000000 000 00000000000 000 0000000000000000 000 0000000000  000 0000000000X     X   X   X000X   X   X     X0000X     X   X   X000X   X   X     X0000 00000 0000000 000 0000000 00000 0000 00000 0000000 000 0000000 00000 0000X X000X   X   X   X   X   X000X X0000X X000X   X   X   X   X   X000X X000000 000 000 00000000000 000 000 00000000 000 000 00000000000 000 000 000000X X   X000X   X000X   X000X   X X0000X X   X000X   X000X   X000X   X X0000 0000000000000 000 0000000000000 0000 0000000000000 000 0000000000000 0000X             X   X             X0000X             X   X             X0000000000000000000000000000000000000000000000000000000000000000000000000000";
char mapPW[1628] = "0000000000000000000000000000000000000000000000000000000000000000000000000000. . . . . . . .000. . . . . . . .0000. . . . . . . .000. . . . . . . .0000.00000.0000000.000.0000000.00000.0000.00000.0000000.000.0000000.00000.0000.00000.0000000.000.0000000.00000.0000.00000.0000000.000.0000000.00000.0000. . . . . . . . . . . . . . . . .0000. . . . . . . . . . . . . . . . .0000.00000.000.00000000000.000.00000.0000.00000.000.00000000000 000.00000.0000. . . .000. . .000. . .000. . . .0000. . . .000. . .000. . .000. . . .0000000000.0000000 000 0000000.0000000000000000.0000000 000 0000000.00000000      00.000             000.000          000.000             000.00      00000000.000 00000  0000 000.0000000000000000.000 0000  00000 000.00000000        .    000     000    .                .    000     000    .        00000000.000 00000000000 000.0000000000000000.000 00000000000 000.00000000      00.000      C      000.000          000.000      C      000.00      00000000.000 00000000000 000.0000000000000000.000 00000000000 000.0000000000. . . . . . . .000. . . . . . . .0000. . . . . . . .000. . . . . . . .0000.00000.0000000.000.0000000.00000.0000.00000.0000000.000.0000000.00000.0000. .000. . . . . . . . . . .000. .0000. .000. . . . . . . . . . .000. .000000.000.000.00000000000.000.000.00000000.000.000.00000000000.000.000.000000. . . .000. . .000. . .000. . . .0000. . . .000. . .000. . .000. . . .0000.0000000000000.000.0000000000000.0000.0000000000000.000.0000000000000.0000. . . . . . . . . . . . . . . . .0000. . . . . . . . . . . . . . . . .0000000000000000000000000000000000000000000000000000000000000000000000000000";
/*"00000000000000000000000000000000000000000000000000000000000000000000000000
00X     X       X000X       X     X0000X     X       X000X       X     X00
00 00000 0000000 000 0000000 00000 0000 00000 0000000 000 0000000 00000 00
00 00000 0000000 000 0000000 00000 0000 00000 0000000 000 0000000 00000 00
00X     X   X   X   X   X   X     X0000X     X   X   X   X   X   X     X00
00 00000 000 00000000000 000 00000 0000 00000 000 00000000000 000 00000 00
00X     X000X   X000X   X000X     X0000X     X000X   X000X   X000X     X00
00000000 0000000 000 0000000 0000000000000000 0000000 000 0000000 00000000
      00 000X   X   X   X000 000          000 000X   X   X   X000 00      
00000000 000 00000  0000 000 0000000000000000 000 0000  00000 000 00000000
        X   X000     000X   X                X   X000     000X   X        
00000000 000 00000000000 000 0000000000000000 000 00000000000 000 00000000
      00 000X           X000 000          000 000X           X000 00      
00000000 000 00000000000 000 0000000000000000 000 0000000000  000 00000000
00X     X   X   X000X   X   X     X0000X     X       X000X   X   X     X00
00 00000 0000000 000 0000000 00000 0000 00000 0000000 000 0000000 00000 00
00X X000X   X   X   X   X   X000X X0000X X000X   X   X   X   X   X000X X00
0000 000 000 00000000000 000 000 00000000 000 000 00000000000 000 000 0000
00X X   X000X   X000X   X000X   X X0000X X   X000X   X000X   X000X   X X00
00 0000000000000 000 0000000000000 0000 0000000000000 000 0000000000000 00
00X             X   X             X0000X             X   X             X00
00000000000000000000000000000000000000000000000000000000000000000000000000";*/

struct vector2d
{
  float x = 0;
  float y = 0; 
};
