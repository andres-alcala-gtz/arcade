#ifndef RACOON_H
#define RACOON_H

#include "Entity.h"

class Racoon : public Entity
{
    public:
        Racoon(int x, int y, Texture* tex);
        void update();

    private:
        const int W = 26;
        const int H = 30;
};

#endif // RACOON_H
