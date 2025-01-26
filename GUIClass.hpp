#ifndef GUIClass_h
#define GUIClass_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include "ParticleClasses.hpp"

namespace particles
{
    class System;
    
    class ParticleDrawer: public Fl_Widget 
    {
        System* system;
        public:
        ParticleDrawer(int X, int Y, int W, int H, const char* L, System* system);
        void draw();
    };

    class GUI 
    {
        Fl_Window* window;
        Fl_Int_Input* stepscount;
        Fl_Button* do_stepsButton;
        Fl_Button* addButton;
        Fl_Button* removeButton;
        ParticleDrawer* drawer;
        System* system;
        public:
        GUI(System *system);
        GUI(GUI& g);
        void operator= (GUI& g);
        static void do_stepButtonCallback(Fl_Widget* w, void* v);
        static void addButtonCallback(Fl_Widget* w, void* v);
        static void addLightParticleCallback(Fl_Widget* w, void* v);
        static void addHeavyParticleCallback(Fl_Widget* w, void* v);
        static void removeButtonCallback(Fl_Widget* w, void* v);
        static void steps_TO(void* v);
        void addParticle(Particle* part);
        void deleteParticle();
        void doSteps();
        void show();
        void drawParticle(Particle* particle);
        ~GUI();

        const static int width = 945;
        const static int height = 795;
        const static int yoffset = 55;
    };
}
#endif 