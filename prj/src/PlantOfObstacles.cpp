#include "PlantOfObstacles.hh"


shared_ptr<ObjectOfScene>PlantOfObstacles::AddObject(ID id,Users users) const { 

Vector3D location,size;

      switch (id) 
      {
        case Drone:
          switch (users){
            case User :{
                cout << "Podaj lokalizacje srodka symetrii drona [x,y,z]"<< endl;
                cin >>location[0] >> location[1] >> location[2];
            }break;
        
            case Root:
            location[0]=rand()%120;
            location[1]=rand()%120;
            location[2]=rand()%120;    
            break;
          
          }
       return make_shared<Quadracopter>(location[0],location[1],location[2]);
       

       case Obstacle: 
          switch (users){
            case User :{
                cout << "Podaj lokalizacje srodka symetrii przeszkody [x,y,z]"<< endl;
                cin >>location;
                cout << "oraz wymiary [x,y,z]" << endl;
                cin >> size;
            }break;
        
            case Root:
            location[0]=30;location[1]=-50;location[2]=80;size[0]=30;size[1]=20;size[2]=30;  
            break;
          }
      
       return make_shared<Obstacles>(location,size);
      }

    return nullptr;
    }