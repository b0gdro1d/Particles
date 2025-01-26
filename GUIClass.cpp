#include "GUIClass.hpp"
#include"SystemClass.hpp"
#include "ParticleClasses.hpp"
#include<iostream>
#include<random>
#include<cstdlib>

using namespace particles;

ParticleDrawer::ParticleDrawer(int x, int y, int w, int h, const char* l, System* system): Fl_Widget(x, y, w, h, l), system(system) {}

void ParticleDrawer::draw() 
{
    fl_color(FL_WHITE);
    fl_rectf(x(), y(), w(), h());
    system->draw();
}

GUI::GUI(System *sys) : system(sys)
{
    window = new Fl_Window(width, height+50, "Particle System");
    stepscount = new Fl_Int_Input(450, 10, 100, 30, "steps: ");
    stepscount->value("100");
    do_stepsButton = new Fl_Button(650, 10, 120, 30, "Do Steps");
    do_stepsButton->callback(do_stepButtonCallback, (void*)this);
    addButton = new Fl_Button(250, 10, 120, 30, "Add Particle");
    addButton->callback(addButtonCallback, (void*)this);
    removeButton = new Fl_Button(50, 10, 120, 30, "Remove Particle");
    removeButton->callback(removeButtonCallback, (void*)this);
    drawer = new ParticleDrawer(0, yoffset, width, height, "Drawer", sys);
    drawer->box(FL_DOWN_BOX);
    window->end();
}

GUI::GUI(GUI& g) { *this = g; }

void GUI::operator=(GUI& g)
{
    window = g.window;
    stepscount = g.stepscount;
    do_stepsButton = g.do_stepsButton;
    addButton = g.addButton;
    removeButton = g.removeButton;
    drawer = g.drawer;
    system = g.system;
}

GUI::~GUI() { delete window; }

void GUI::doSteps() 
{
    system->set_steps(atoi(stepscount->value()));
    if (system->get_steps() > 0) Fl::add_timeout(0, steps_TO, this);
}

void GUI::steps_TO(void* v) 
{
    GUI* gui = (GUI*)v;
    System* system = gui->system;
    system->set_steps(system->get_steps() - 1);
    system->step();
    gui->drawer->redraw();
    if (system->get_steps() <= 0) return;
    Fl::repeat_timeout(0.01, steps_TO, v);
}

void GUI::show() {window->show();}

void GUI::do_stepButtonCallback(Fl_Widget* w, void* v) 
{
    GUI* gui = (GUI*)v;
    gui->doSteps();
}

void GUI::addButtonCallback(Fl_Widget* butt, void* s) 
{
    Fl_Window *ad = new Fl_Window(450,150 , "Choose type");
    Fl_Button *light = new Fl_Button(50, 40, 150, 75, "Light Particle");
    light->callback(addLightParticleCallback, s);
    Fl_Button *heavy = new Fl_Button(250, 40, 150, 75, "Heavy Particle");
    heavy->callback(addHeavyParticleCallback, s);
    ad->show();
    Fl::run();
}

void GUI::addLightParticleCallback(Fl_Widget* w, void* v) 
{
    GUI* gui = (GUI*)v;
    gui->addParticle(new LightParticle());
}

void GUI::addHeavyParticleCallback(Fl_Widget* w, void* v) 
{
    GUI* gui = (GUI*)v;
    gui->addParticle(new HeavyParticle());
}

void GUI::addParticle(Particle* other) 
{
    system->addParticle(other);
    system->check_collisions();
    drawer->redraw();
}

void GUI::removeButtonCallback(Fl_Widget* w, void* v) 
{
    GUI* gui = (GUI*)v;
    gui->deleteParticle();
}

void GUI::deleteParticle() 
{
    system->deleteParticle();
    drawer->redraw();
}