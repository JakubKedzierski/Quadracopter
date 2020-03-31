#include "cuboid.hh"

Cuboid::Cuboid(){
     
     //stworzenie na stale prostopadloscianu

     Vector3D vec[kCubNodeNumber]={{-10,-12,-5},{10,-12,-5},{10,12,-5},{-10,12,-5},{-10,-12,5},{10,-12,5},{10,12,5},{-10,12,5}};
     Vector3D MiddleUp(0,0,5),MiddleDown(0,0,-5);

     for(int i=0;i<kCubNodeNumber;i++)
          P.push_back(vec[i]);

     P.push_back(MiddleUp);
     P.push_back(MiddleDown);
}


Cuboid::Cuboid(Vector3D centre,Vector3D size){
    
     Vector3D vec[kCubNodeNumber];
     Vector3D MiddleUp,MiddleDown;
     
     for(int i=0;i<3;i++)
     size[i]/=2;

          for(int i=0;i<kCubNodeNumber;i++){
               vec[i]=centre;
          }
          
          MiddleDown=centre;
          MiddleUp=centre;

          vec[0][0]-=size[0]; vec[0][1]+=size[1]; vec[0][2]-=size[2];
          vec[1][0]+=size[0]; vec[1][1]+=size[1]; vec[1][2]-=size[2];
          vec[2][0]+=size[0]; vec[2][1]-=size[1]; vec[2][2]-=size[2];
          vec[3][0]-=size[0]; vec[3][1]-=size[1]; vec[3][2]-=size[2];
          MiddleDown[2]-=size[2];
          vec[4][0]-=size[0]; vec[4][1]+=size[1]; vec[4][2]+=size[2];
          vec[5][0]+=size[0]; vec[5][1]+=size[1]; vec[5][2]+=size[2];
          vec[6][0]+=size[0]; vec[6][1]-=size[1]; vec[6][2]+=size[2];
          vec[7][0]-=size[0]; vec[7][1]-=size[1]; vec[7][2]+=size[2];
          MiddleUp[2]+=size[2];

     for(int i=0;i<kCubNodeNumber;i++)
          P.push_back(vec[i]);

     P.push_back(MiddleUp);
     P.push_back(MiddleDown);

}

Cuboid::Cuboid(double *change){

     Vector3D vec[kCubNodeNumber]={{-10,-12,-5},{10,-12,-5},
     {10,12,-5},{-10,12,-5},{-10,-12,5},
     {10,-12,5},{10,12,5},{-10,12,5}};
     Vector3D MiddleUp(0,0,5),MiddleDown(0,0,-5);

     for(int i=0;i<kCubNodeNumber;i++){
          for(int j=0;j<3;j++){
               vec[i][j]+=change[j];
               vec[i][j]*=change[j+3];
          }
     }

     for(int i=0;i<3;i++){
     MiddleDown[i]+=change[i];
     MiddleUp[i]+=change[i];
     MiddleDown[i]*=change[i+3];
     MiddleUp[i]*=change[i+3];
     }

     for(int i=0;i<kCubNodeNumber;i++)
          P.push_back(vec[i]);

     P.push_back(MiddleUp);
     P.push_back(MiddleDown);

}

/*! Przeciazenie operatora wypisujacego wierzcholki prostokata na ostream*/
std::ostream& operator << (std::ostream & output_ostream, Cuboid & cube){
     
     output_ostream << endl << "Wierzcholki prostopadloscianu:" << endl;

     for(int i=0;i<kCubNodeNumber;i++){
     output_ostream << cube[i];

     output_ostream << endl ;
     }

return output_ostream;
}

/*! Przeciazenie operatora zapisujacego wierzcholki do pliku*/
std::ofstream& operator << (std::ofstream & output_ofstream, Cuboid & cube){

          for(int i=0;i<kCubNodeNumber/2;i++)
          output_ofstream << cube[8] << cube[i+4] << cube[i]<< cube[9] << endl;

          output_ofstream << cube[8] << cube[4] << cube[0]<< cube[9] << endl ;

return output_ofstream;
}

Vector3D Cuboid::GetSymetryPoint()const{

     Vector3D SymetryPoint;
     SymetryPoint[0]=(P[0][0]+P[1][0])/2;
     SymetryPoint[1]=(P[0][1]+P[2][1])/2;
     SymetryPoint[2]=(P[0][2]+P[4][2])/2;

return SymetryPoint;
}