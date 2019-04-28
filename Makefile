SFML = -lsfml-window -lsfml-system -lsfml-graphics
GL = -lGL

all:
	g++ *.cpp $(SFML) $(GL) -o softbody