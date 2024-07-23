#ifndef BODYMANAGER_H
#define BODYMANAGER_H

#include <vector>
#include "body.h"

class BodyManager
{
public:
    static std::vector<Body> generate_orbiting_bodies(int num_bodies, double central_mass);
    static std::vector<Body> create_static_bodies();
    static std::vector<Body> get_bodies(int argc, char *argv[]);
};

#endif
