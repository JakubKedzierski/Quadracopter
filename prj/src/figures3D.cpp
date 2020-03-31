#include <iostream>
#include <fstream>
#include "figures3D.hh"


void figures3D::rotate(Matrix3x3 matrix){
  for(Vector3D &Node : P)
    Node=matrix*Node;
}

void figures3D::Translate(Vector3D offset){
     for(Vector3D &Node : P)
          Node+=offset;
}