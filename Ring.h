#ifndef RING_H
#define RING_H

#include <iostream>

using namespace std;

class Ring
{
    public:
        Ring();

        size_t getSize() const;
        void setSize(size_t value);

        size_t getPosition() const;
        void setPosition(size_t value);


    private:
        size_t size;
        size_t position;
};

#endif // RING_H
