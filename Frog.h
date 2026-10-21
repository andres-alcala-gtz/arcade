#ifndef FROG_H
#define FROG_H

#include "Entity.h"

class Frog : public Entity
{
    public:
        Frog(int x, int y, Texture* tex);
        void update();

    private:
        const int W = 26;
        const int H = 32;
};

#endif // FROG_H

