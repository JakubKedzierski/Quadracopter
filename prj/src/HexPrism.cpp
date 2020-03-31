#include "cuboid.hh"
#include "HexPrism.hh"
#include <cstdlib>

HexPrism::HexPrism(double x,double y,double z){

     Vector3D vec[kHexNodes+2]={
     {0+x,12+y,5+z},      {5+x,3.33975+y,5+z},
     {15+x,3.33975+y,5+z},{20+x,12+y,5+z},
     {15+x,20.6603+y,5+z},{5+x,20.6603+y,5+z},
     {5+x,20.6603+y,10+z},{0+x,12+y,10+z},
     {5+x,3.33975+y,10+z},{15+x,3.33975+y,10+z},
     {20+x,12+y,10+z},    {15+x,20.6603+y,10+z},
     {10+x,12+y,10+z},    {10+x,12+y,5+z}};

     for(int i=0;i<kHexNodes+2;i++)
          P.push_back(vec[i]);
}

std::ofstream& operator << (std::ofstream & output_ofstream, HexPrism & hex){
         
     output_ofstream << hex[12] << hex[7] << hex[0] << hex[13] << endl ;
     output_ofstream << hex[12] << hex[6] << hex[5] << hex[13] << endl ;
     
     for(int i=11;i>6;i--)
     output_ofstream << hex[12] << hex[i] << hex[i-7] << hex[13] << endl ; 


return output_ofstream;
}

Vector3D HexPrism::GetSymetryPoint()const{

     Vector3D vec;

     vec[0]=(P[0][0]+P[3][0])/2;
     vec[1]=(P[0][1]+P[3][1])/2;
     vec[2]=(P[7][2]+P[10][2])/2;     

return vec;
}

void HexPrism::rotor(bool side,Speed speed){

     Vector3D transVec;
     Matrix3x3 matrix;

     if(side)
     matrix.Type_In(speed,'z');
     else
     matrix.Type_In(-speed,'z');
     
     transVec=(*this).GetSymetryPoint();

     for(int i=0;i<14;i++)
          P[i]-=transVec;     
     
     (*this).rotate(matrix);
     
     for(int i=0;i<14;i++)
     P[i]+=transVec;
     
}

Speed LoadMode(bool RotorOrHull){
     Speed speed;
     unsigned int Mode=0;

     if(RotorOrHull)
     cout << "Wybierz szybkosc obrotu smigel [0-3]" <<endl;
     else 
     cout << "Wybierz szybkosc lotu [0-3]" << endl;
     
     cin >> Mode;
     
     while(cin.fail()||Mode>3){
          cin.clear();
          cin.ignore(10000,'\n');
          cout << "Niepoprawna szybkosc !!! Wybierz odpowiednia szybkosc [0-3]" <<endl;
          cin >> Mode;
     }

    switch(Mode){
     case 0:
         speed = Null;
     break;

     case 1:
          speed = Slow;
     break;

     case 2:
          speed = Medium;
     break;

     case 3:
          speed = Fast;
     break;           

     default:
     cout << "Niepoprawna szybkosc !!!";
    }

    
return speed;
}