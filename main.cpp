#include <iostream>
#include <vector>
#include "graphics.h"
#include "body.h"
#include <random>
#include "bodymanager.h"

using namespace std;

const double CENTRAL_BODY_MASS = 1e6;
const double GRAVITY_CONSTANT = 1.0;

int main(int argc, char *argv[])
{
    vector<Body> bodies = BodyManager::get_bodies(argc, argv);

    if (bodies.empty())
    {
        cerr << "No bodies to display." << endl;
        return 1;
    }

    Graphics instance = *Graphics::get_instance(1.0, bodies);
    instance.mainloop();

    return 0;
}
