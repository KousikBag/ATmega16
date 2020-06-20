/*
> In Sketch folder application is given to convert BMP data
> Circuit diagram is given in sketch folder

pin

LCD ----- ARDUINO
1--GND
2--VCC
3----\/\/\---- [vcc--res(3)--gnd]
4--A3
5--A2
6--A4
7--D8
8--D9
9--D10
10--D11
11--D4
12--D5
13--D6
14--D7
15--A0
16--A1
17--RESET
18--/\/\/\-
19-/\/\/\--VCC
20--GND

 */



#include <glcd.h>
#include "fonts/SystemFont5x7.h"   // font
#include "bitmap1.h"         // bitmap1

void setup(){
  GLCD.Init();
}

void  loop()
{
  //for(int x=0;x<127;x++)
  {
    for(int y=0;y<63;y++)
    {
  GLCD.DrawBitmap(harish,y , 0,BLACK);
  delay(200);
    }
  }
}
