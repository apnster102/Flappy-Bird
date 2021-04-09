#include "Pipes.h"

Pipe::Pipe()
{
    pos = 0;
}

bool Pipe::loadImage(string path, SDL_Renderer* ren)
{
    bool load = Object::loadImage(path, ren);
    return load;
}

void Pipe::render(SDL_Renderer* ren, int pos)
{
    rect.x = pos;
    Object::render(ren, NULL);
}

void Pipe::setPos(int ypos)
{
    pos = ypos;
}

Pipe::~Pipe()
{
    free();
}

PipePair::PipePair()
{
    upperPipe.setPos(0);
    lowerPipe.setPos(0);
    posX = 0;
    offset = 0;
    moving = true;
}

bool PipePair::spawnPipes(SDL_Renderer* ren)
{
    bool load1 = upperPipe.loadImage("image/UpperPipe.png", ren);
    bool load2 = lowerPipe.loadImage("image/LowerPipe.png", ren);

    lowerPipe.setPos(rand()%210 +(SCREEN_HEIGHT - PIPE_HEIGHT));
    cout << lowerPipe.getPos() << endl;
    upperPipe.setPos(lowerPipe.getPos() - 450);
    lowerPipe.setRect(posX, lowerPipe.getPos());
    upperPipe.setRect(posX, upperPipe.getPos());

    return(load1 && load2);
}

void PipePair::render(SDL_Renderer* ren)
{
    lowerPipe.render(ren, posX);
    upperPipe.render(ren, posX);
}

void PipePair::roll(SDL_Renderer* ren)
{
    offset -= 5;
    posX = offset;
    if(posX + PIPE_WIDTH < 0)
    {
        spawnPipes(ren);

        offset = SCREEN_WIDTH;
    }
    render(ren);

}

bool PipePair::collided(SDL_Rect player)
{
    bool upper = Object::checkCollision(player, upperPipe.getRect());
    bool lower = Object::checkCollision(player, lowerPipe.getRect());
    if(upper || lower)
        return true;
    return false;
}

void PipePair::pause()
{
    offset -= 0;
}

PipePair::~PipePair()
{
    free();
}
