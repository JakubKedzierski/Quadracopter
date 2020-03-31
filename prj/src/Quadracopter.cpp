#include "Quadracopter.hh"



void Quadracopter::ChangeOrientation(Matrix3x3 matrix,Vector3D symetry){

    ////////////////////////////////////////////////////////////////
    /* przesuniecie ukladu wspolrzednych do ukladu wobec prostopadloscianu*/
        for(int i=0;i<kCubNodeNumber+2;i++)
            hull[i]-=symetry;
    
        hull.rotate(matrix);
    
        for(int i=0;i<kCubNodeNumber+2;i++)
            hull[i]+=symetry;  
    //////////////////////////////////////////////////////////////////  
    

    for(int i=0;i<4;i++){      
        for(int j=0;j<14;j++){
        disc[i][j]-=symetry;
        }
    }

    for(int i=0;i<4;i++)
    disc[i].rotate(matrix);

    for(int i=0;i<4;i++){
        for(int j=0;j<14;j++){
        disc[i][j]+=symetry;
        }
    }

}

std::ofstream& operator << (std::ofstream & stream, Quadracopter & quad){

    stream << quad.GetHull() << endl;

    for(int i=0;i<kNumberOfDisc;i++)
        stream << quad[i] << endl;

return stream;
}

Quadracopter::Quadracopter(){
     
     HexPrism disc1, disc2(-20,0),disc3(-20,-24),disc4(0,-24);
     RotationAngle=90;
     symetry={0,0,0};
     radius=0;
     height=0;

    disc[0]=disc1;
    disc[1]=disc2;
    disc[2]=disc3;
    disc[3]=disc4;

    symetry[0]=hull.GetSymetryPoint()[0];
    symetry[1]=hull.GetSymetryPoint()[1];
    symetry[2]=(hull[9][2]+disc[0][12][2])/2;

    radius=sqrt(pow(hull.GetSymetryPoint()[0]-disc[0][5][0],2)+pow(hull.GetSymetryPoint()[1]-disc[0][5][1],2))+0.5;
    height=7.5;
    track.push_back(symetry);
    track.push_back(symetry);
}

Vector3D Quadracopter::MoveUpDown(double angle)const{
     
     Vector3D MoveVector;
     double road=0;
     double sigma=0;

     cout << "Na jaka odleglosc chcesz przemiescic drona ? :" ;
     cin >> road;

     cout << endl << "Podaj kat wznoszenia/opadania: ";
     cin >> sigma;

     while(cin.fail()){
          cerr << endl << "Cos poszlo nie tak. Sprobuj jeszcze raz." << endl;
          cin.clear();
          cin.ignore(10000,'\n');
          cout << "Na jaka odleglosc chcesz przemiescic drona ? :" ;
          cin >> road;
          cout << endl << "Podaj kat wznoszenia/opadania: ";
          cin >> sigma;  
     }

     sigma=M_PI*sigma/180; // zamiana stopni na radiany
     angle=M_PI*angle/180; // zamiana stopni na radiany

     MoveVector[0]=road*cos(sigma)*cos(angle);
     MoveVector[1]=road*cos(sigma)*sin(angle);
     MoveVector[2]=road*sin(sigma);

return MoveVector;

}

Quadracopter::Quadracopter(double x,double y,double z){


     HexPrism disc1(x,y,z), disc2(-20+x,0+y,z),disc3(-20+x,-24+y,z),disc4(0+x,-24+y,z);
     double a[]{x,y,z,1,1,1};
     Cuboid cub(a);
     RotationAngle=90;

    hull=cub;
    disc[0]=disc1;
    disc[1]=disc2;
    disc[2]=disc3;
    disc[3]=disc4;

    symetry[0]=hull.GetSymetryPoint()[0];
    symetry[1]=hull.GetSymetryPoint()[1];
    symetry[2]=(hull[9][2]+disc[0][12][2])/2;

    radius=sqrt(pow(hull.GetSymetryPoint()[0]-disc[0][5][0],2)+pow(hull.GetSymetryPoint()[1]-disc[0][5][1],2))+0.3; //disc[0][3][0] i disc[0][4][1]
    height=7.5;


    track.push_back(symetry);
    track.push_back(symetry);
}

Vector3D Quadracopter::MoveSymetry(){

    symetry[0]=hull.GetSymetryPoint()[0];
    symetry[1]=hull.GetSymetryPoint()[1];
    symetry[2]=(hull[0][2]+disc[0][11][2])/2;
    
    track.pop_back();
    track.push_back(symetry);

return symetry;    
}

bool Quadracopter::IfCollision(Vector3D PhysicalPoint,double radius)const{
    
    double difference=0;

    difference=sqrt(pow(PhysicalPoint[0]-symetry[0],2)+pow(PhysicalPoint[1]-symetry[1],2));

    if(0==difference)
    return false;


    if(difference<= (2*radius) ){
            if((abs(PhysicalPoint[2]-symetry[2])-2.5) <= (2*height) ){
                return true;
            }
        }

return false;
}

 bool Quadracopter::WriteToFile(ofstream &stream){

     stream << (*this);
 
 return true;
 }