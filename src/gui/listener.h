#ifndef LISTENER_H_INCLUDED
#define LISTENER_H_INCLUDED

#include "gui.h"

class Gui;

class Listener
{
public:
    virtual void actionPerformed(const PlayerController &controller, Vec dim, Vec pos, Gui* gui) = 0;
};

#endif // LISTENER_H_INCLUDED
