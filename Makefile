# test Makefile
#
# 


# Select appropriate compiler.
#CPP=g++
CPP=g++
CPPFLAGS=-std=c++0x -Wall -pedantic -O3    

ifdef DEBUG
CPPFLAGS=-g
endif

default: all

all: test

test: test.cpp Makefile
	$(CPP) $(CPPFLAGS) -o test source/box.cpp source/camera.cpp source/circle.cpp source/color.cpp source/cone.cpp source/cylinder.cpp source/graphic_exception.cpp source/intersection.cpp source/light.cpp source/material.cpp source/matrix.cpp source/pixel.cpp source/point.cpp source/ppmwriter.cpp source/ray.cpp source/raytracer.cpp source/scene.cpp source/scene_object.cpp source/sdf_parser.cpp source/shape.cpp source/sphere.cpp source/triangle.cpp source/vector.cpp test.cpp  

clean:
	-rm test


