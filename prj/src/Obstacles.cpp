#include "Obstacles.hh"


Obstacles::Obstacles(Vector3D centre,Vector3D size){

    Cuboid ob1(centre,size);
    cub=ob1;

    symetry=centre;

}

ofstream& operator << (std::ofstream & output_ofstream, Obstacles &obs){

    Cuboid cube=obs.GetObstacle();
    output_ofstream << cube << endl;

    return output_ofstream;
}

bool Obstacles::IfCollision(Vector3D PhysicalPoint,double radius)const{
double height=7.5;

// zle numerki sa bo nowy konstuktor

            if(cub[0][0]-radius<PhysicalPoint[0] && PhysicalPoint[0] <cub[1][0]+radius){
                if(cub[0][1]-radius<PhysicalPoint[1] && PhysicalPoint[1]<cub[2][1]+radius){
                    if(cub[0][2]-height<PhysicalPoint[2] && PhysicalPoint[2] <cub[4][2]+height){
                                             cout << "Przeszkodo-";
                      return true;              
                    }
                }
            }

return false;           
}

bool Obstacles::WriteToFile(ofstream &stream){
     
     stream << (*this);
 
 return true;
}