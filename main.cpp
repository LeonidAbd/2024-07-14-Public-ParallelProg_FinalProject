#include <iostream>
#include <vector>
#include "graphics.h"
#include "body.h"
#include <random>

using namespace std;

const double CENTRAL_BODY_MASS = 1e6;
const double GRAVITY_CONSTANT = 1.0;

vector<Body> generate_orbiting_bodies(int num_bodies)
{
    vector<Body> bodies;

    random_device rd;
    mt19937 generator(rd());

    uniform_real_distribution<double> radius_dist(50.0, 300.0);
    uniform_real_distribution<double> velocity_dist(10.0, 100.0);
    uniform_real_distribution<double> size_dist(1.0, 10.0);

    Body central_body(CENTRAL_BODY_MASS, 400, 400, 0, 0);
    central_body.set_size(30);
    bodies.push_back(central_body);

    for (int i = 0; i < num_bodies; ++i)
    {
        double radius = radius_dist(generator);
        double angle = uniform_real_distribution<double>(0.0, 2 * M_PI)(generator);

        double coord_x = 400 + radius * cos(angle);
        double coord_y = 400 + radius * sin(angle);

        double velocity = sqrt(GRAVITY_CONSTANT * CENTRAL_BODY_MASS / radius);
        double velocity_x = -velocity * sin(angle);
        double velocity_y = velocity * cos(angle);

        double size = size_dist(generator);

        Body body(1.0, coord_x, coord_y, velocity_x, velocity_y);
        body.set_size(size);

        bodies.push_back(body);
    }

    return bodies;
}

vector<Body> get_static_bodies()
{
    vector<Body> bodies;

    Body body1(1000000.0, 400, 400, 0, 0);
    body1.set_size(5);
    bodies.push_back(body1);

    Body body2(10000.0, 360, 400, 0, 100);
    bodies.push_back(body2);
    Body body3(10000.0, 470, 400, 0, -100);
    bodies.push_back(body3);
    Body body4(10000.0, 400, 510, 100, 0);
    bodies.push_back(body4);
    Body body5(10000.0, 400, 280, -100, 0);
    bodies.push_back(body5);

    return bodies;
}

vector<Body> get_bodies(int argc, char *argv[])
{
    if (argc > 1)
    {
        int num_bodies;
        try
        {
            num_bodies = stoi(argv[1]);
            if (num_bodies < 1)
            {
                throw invalid_argument("Number of bodies must be positive.");
            }
            return generate_orbiting_bodies(num_bodies);
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
            return {};
        }
    }
    else
    {
        return get_static_bodies();
    }
}

int main(int argc, char *argv[])
{
    vector<Body> bodies = get_bodies(argc, argv);

    if (bodies.empty())
    {
        cerr << "No bodies to display." << endl;
        return 1;
    }

    Graphics instance = *Graphics::get_instance(1.0, bodies);
    instance.mainloop();

    return 0;
}
