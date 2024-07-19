#pragma once
#include <raylib.h>
#include "system.h"

class Graphics {
private:
    static Graphics* instance;
    //System system;
    Graphics();
public:
    static Graphics* get_instance();
    void mainloop();
};
