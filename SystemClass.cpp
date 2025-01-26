#include"SystemClass.hpp"
#include "ParticleClasses.hpp"
#include "GUIClass.hpp"

using namespace particles;

void System::check_collisions()
{
    for (int i = 0; i < parts.size(); ++i)
    {
        parts[i]->wall_collision();
        for (int j = i+1; j < parts.size(); ++j) parts[i]->collision(*parts[j]);
    }
}

System::System(int seed, int lightParticles, int heavyParticles)
{
    gui = new GUI(this);
    srand(seed);
    for (int i = 0; i < lightParticles; i++) parts.push_back(new LightParticle());
    for (int i = 0; i < heavyParticles; i++) parts.push_back(new HeavyParticle());
    check_collisions();
    gui->show();
}

System::System(System& sys) {*this = sys;}

void System::operator=(System& sys)
{
    parts = sys.parts;
    steps = sys.steps;
    gui = sys.gui;
}

void System::step()
{
    check_collisions();
    for(auto x : parts) x->move();
}

void System::deleteParticle() 
{
    if (parts.size() > 0) 
    {
        delete parts[parts.size() - 1];
        parts.pop_back();
    }
}


std::vector<Particle*> System::get_parts() {return parts;}

void System::addParticle(Particle* part) { parts.push_back(part); }

int System::get_steps() const {return steps;}

void System::set_steps(int n) {steps = n;}

void System::draw()
{
    for (const Particle* p : parts) 
    {
        int x = p->get_x();
        int y = p->get_y();
        int r = p->get_r();
        if (r == 5) fl_color(FL_DARK_GREEN);
        else fl_color(FL_DARK_MAGENTA);
        fl_pie(x - r, y - r + yoffset, 2*r, 2*r, 0, 360);
    }
}

System::~System() { delete gui;}