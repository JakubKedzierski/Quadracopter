#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++17 

__start__: Quadracopter
	./Quadracopter

Quadracopter: obj obj/main.o obj/cuboid.o obj/gnuplot_link.o obj/Quadracopter.o obj/figures3D.o obj/HexPrism.o obj/scene.o\
	obj/ObjectOfScene.o obj/Obstacles.o obj/PlantOfObstacles.o
	g++ -Wall -pedantic -std=c++0x -o Quadracopter obj/main.o\
	           obj/cuboid.o obj/gnuplot_link.o obj/Quadracopter.o obj/figures3D.o obj/HexPrism.o\
			   obj/scene.o obj/ObjectOfScene.o obj/Obstacles.o obj/PlantOfObstacles.o -lpanel -lcurses

obj:
	mkdir obj

obj/figures3D.o: inc/figures3D.hh src/figures3D.cpp\
			inc/vector3D.hh inc/vector.hh 
	g++ -c ${CXXFLAGS} -o obj/figures3D.o src/figures3D.cpp

obj/HexPrism.o: inc/HexPrism.hh src/HexPrism.cpp\
			inc/vector3D.hh inc/vector.hh 
	g++ -c ${CXXFLAGS} -o obj/HexPrism.o src/HexPrism.cpp	

obj/gnuplot_link.o: inc/gnuplot_link.hh src/gnuplot_link.cpp
	g++ -c ${CXXFLAGS} -o obj/gnuplot_link.o src/gnuplot_link.cpp

obj/main.o: src/main.cpp inc/cuboid.hh inc/matrix3x3.hh inc/matrix.hh\
           inc/vector3D.hh inc/vector.hh
	g++ -c ${CXXFLAGS}-o obj/main.o src/main.cpp 

obj/cuboid.o: src/cuboid.cpp inc/cuboid.hh\
         inc/vector3D.hh inc/vector.hh inc/figures3D.hh
	g++ -c ${CXXFLAGS} -o obj/cuboid.o src/cuboid.cpp

obj/Quadracopter.o: src/Quadracopter.cpp inc/Quadracopter.hh\
         inc/vector3D.hh inc/vector.hh inc/cuboid.hh inc/figures3D.hh
	g++ -c ${CXXFLAGS} -o obj/Quadracopter.o src/Quadracopter.cpp	

obj/scene.o: inc/scene.hh src/scene.cpp\
			inc/vector3D.hh inc/vector.hh inc/Quadracopter.hh
	g++ -c ${CXXFLAGS} -o obj/scene.o src/scene.cpp	

obj/ObjectOfScene.o: inc/ObjectOfScene.hh src/ObjectOfScene.cpp\
			inc/vector3D.hh inc/vector.hh 
	g++ -c ${CXXFLAGS} -o obj/ObjectOfScene.o src/ObjectOfScene.cpp	

obj/Obstacles.o: inc/Obstacles.hh src/Obstacles.cpp\
			inc/vector3D.hh inc/vector.hh inc/cuboid.hh
	g++ -c ${CXXFLAGS} -o obj/Obstacles.o src/Obstacles.cpp	

obj/PlantOfObstacles.o: inc/PlantOfObstacles.hh src/PlantOfObstacles.cpp\
			inc/Quadracopter.hh inc/Obstacles.hh
	g++ -c ${CXXFLAGS} -o obj/PlantOfObstacles.o src/PlantOfObstacles.cpp	

clean:
	rm -f obj/*.o rotations_3D
