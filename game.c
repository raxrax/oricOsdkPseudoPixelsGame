unsigned int levelH = 25;
unsigned int levelLen = sizeof(levelmap) - 13;

unsigned char x, y;

#define SCREEN_BUFFER_LEN (26 * 40)
unsigned char scrbuffer1[SCREEN_BUFFER_LEN];

#define MAX_SHOT 4
unsigned char shotDataX[MAX_SHOT] = {0};
unsigned char shotDataY[MAX_SHOT] = {0};

#define ENEMIES_MAX 5

unsigned char enemiesX[ENEMIES_MAX] = {0};
unsigned char enemiesY[ENEMIES_MAX] = {0};
unsigned char enemiesType[ENEMIES_MAX] = {0};

unsigned char explosionX[ENEMIES_MAX] = {0};
unsigned char explosionY[ENEMIES_MAX] = {0};

void updateMap()
{
    static unsigned char state = 0;
    unsigned char i;

    for (i = 24; i < 250; --i)
    {
        memcpy(scrbuffer1 + 40 + i * 40, scrbuffer1 + i * 40, 40);
    }
    poke(scrbuffer1, 0);
    poke(scrbuffer1 + 80, 9);
    ++state;

    if (state == 3)
    {
        state = 0;
        for (i = 0; i < 13; ++i)
        {
            unsigned int sprId = levelmap[levelLen + i];
            unsigned int spraddr = 0;

            if (sprId > 25)
            {

                spraddr = (sprId - 26) * 3 + 6 * 39;
            }
            else if (sprId > 12)
            {
                spraddr = (sprId - 13) * 3 + 3 * 39;
            }
            else
            {
                spraddr = sprId * 3;
            }

            memcpy((scrbuffer1 + 1 + i * 3), (&sprites[spraddr]), 3);
            memcpy((scrbuffer1 + 1 + 40 + i * 3), (&sprites[spraddr + 39]), 3);
            memcpy((scrbuffer1 + 1 + 80 + i * 3), (&sprites[spraddr + 39 * 2]), 3);

            // sprintf(0xbb80, "%d ",spraddr);

            // get();
        }
        if (levelLen != 0)
            levelLen -= 13;
        else
            levelLen = sizeof(levelmap) - 13;
        // while(1);
    }
}

void fire()
{
    unsigned char i;
    for (i = 0; i < MAX_SHOT; ++i)
    {
        if (shotDataY[i] == 0)
        {
            shotDataX[i] = x + 1;
            shotDataY[i] = y;
            return;
        }
    }
}

void bullets()
{

    unsigned char i;

    for (i = 0; i < MAX_SHOT; ++i)
    {
        if (shotDataY[i] > 0)
        {
            --shotDataY[i];
            poke(0xbb80 + shotDataY[i] * 40 + shotDataX[i], 42);
        }
    }
}

void player()
{
    static unsigned char state = 0;
    unsigned int addr = 0xbb80 + x + y * 40;
    unsigned int spraddr = (unsigned int)&sprites[state];
    unsigned char key1 = key();

    state = state ? 0 : 3;

    poke(addr++, peek(spraddr++));
    poke(addr++, peek(spraddr++));
    poke(addr, peek(spraddr));

    addr += 38;
    spraddr += 37;

    poke(addr++, peek(spraddr++));
    poke(addr++, peek(spraddr++));
    poke(addr, peek(spraddr));

    addr += 38;
    spraddr += 37;

    poke(addr++, peek(spraddr++));
    poke(addr++, peek(spraddr++));
    poke(addr, peek(spraddr));

    if (key1 == 11 && y > 5)
        y--;

    if (key1 == 10 && y < 23)
        y++;

    if (key1 == 8 && x > 1)
        x--;

    if (key1 == 9 && x < 37)
        x++;

    if (key1 == 32)
    {
        fire();
    }
}

void game()
{
    x = 10;
    y = 20;
    memset(shotDataY, 0, MAX_SHOT);

    while (1)
    {
        updateMap();

        memcpy((void *)0xbb80, scrbuffer1, sizeof(scrbuffer1));
        player();
        bullets();
    }
}