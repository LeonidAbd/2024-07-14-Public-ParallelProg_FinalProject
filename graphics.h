#pragma once
#include <raylib.h>

class Graphics {
private:
    static Graphics* instance;
    Graphics();
public:
    static Graphics* get_instance();
    void mainloop();
};
