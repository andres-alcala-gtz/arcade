#include "Ring.h"

Ring::Ring()
{
    //ctor
}

size_t Ring::getSize() const
{
    return size;
}

void Ring::setSize(size_t value)
{
    size = value;
}

size_t Ring::getPosition() const
{
    return position;
}

void Ring::setPosition(size_t value)
{
    position = value;
}
