#include <lib.h>

#include "font.c"
#include "res.c"
#include "game.c"

// #define const

unsigned char copyright[] = "rax@sofia2022";

unsigned char i;
unsigned int l;

void main()
{

  text();
  paper(0);
  ink(7);
  cls();

  poke(0x26a, 10);
  poke(0x24e, 1);
  poke(0x24f, 1);

  memcpy((void *)0xb900, ALTSET, sizeof(ALTSET));

  lores1();

  printLoresText(1, 26, LORES_TEXT_NORMAL, "SCORE:2000");
  printLoresText(26, 26, LORES_TEXT_NORMAL, "LIVES:2");

  printLoresText(10, 12, LORES_TEXT_NORMAL, "GET READY");

  // fix sprites
  for (l = 0; l < sizeof(sprites); l++)
  {
    sprites[l] += 32;
  }

  game();
}
