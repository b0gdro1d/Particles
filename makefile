all: 
	g++ particlemain.cpp ParticleClasses.cpp SystemClass.cpp GUIClass.cpp `fltk-config --ldflags`

clean:
	rm a.out