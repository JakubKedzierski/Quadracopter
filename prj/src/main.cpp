#include <iostream>
#include <fstream>
#include <unistd.h>
#include "gnuplot_link.hh"
#include "PlantOfObstacles.hh"
#include <ncurses.h>

const int kFilmFrame = 300;
const char *mainbody= "./dat/cuboid.dat" ;


/**
 * @brief Zapis danych do pliku
 * 
 * @param quadro - dron 
 * @return true - udany zapis
 * @return false - nieudany zapis
 */
bool WriteToFile(scene WholeScene){

  ofstream  filestream;


  filestream.open(mainbody);

    if (!filestream.is_open())  {
      cerr << ":(  Operacja otwarcia do zapisu \"" << mainbody << "\"" << endl
	    << ":(  nie powiodla sie." << endl;
      return false;
    }

  for(shared_ptr<ObjectOfScene> &Elem: (WholeScene.GetScienceObject()))  
  (*Elem).WriteToFile(filestream);

  for(int i=0;i<1;i++){
    filestream    << endl << endl;
    for(Vector3D vec: WholeScene.GetDrone()[i]->GetTrack())
    filestream    << vec;
  }

  filestream.close();
 
  if(filestream.fail()) return false;
  else return true;

  return false;
}

/**
 * @brief Wypisanie menu
 * 
 */
void PrintMenu(){
  cout << endl << "Quadracopter Menu" << endl;
  cout << "r - zmiana orientacji drona" << endl;
  cout << "D - dodaj drona" << endl; 
  cout << "O - dodaj przeszkode" << endl;
  cout << "Q - usun wyselekcjonowanego drona" << endl;  
  cout << "t - ruch na wprost z zadanym katem opadania/wznoszenia" << endl;
  cout << "s - wybor drona" << endl;
  cout << "g - GAME MODE" << endl;
  cout << "q - usun sciezke" << endl;      
  cout << "m - wypisanie menu" << endl;
  cout << "d - narysowanie obecnego polozenia dronu" << endl;
  cout << "e - zakonczenie programiku" << endl << endl;
}

/**
 * @brief Policzenie sekund klatki
 * 
 * @param speed - szybkosc ruchu
 * @return int - czas trwania klatki ( dla wrazenia szykosci)
 */
int CountSecondsOfFrame(Speed speed){

      switch(speed){
     case 0:
         return 0;
     break;

     case 1:
          return 14000;
     break;

     case 2:
          return 8000;
     break;

     case 3:
          return 3000;
     break; 
      }

  return 0;
}

/**
 * @brief Zmiana orientacji drona
 * 
 * @param link - link Gnuplota
 * @param WholeScene - cala scena 
 * @param quadro - wybrany dron ktorym latamy
 * @return int - 0 - udalo sie 1- nie udalo sie
 */
int ChangeOrientation(PzG::GnuplotLink link,scene &WholeScene,Quadracopter &quadro){
  
    Speed speed,DiscRotor;
    double alpha;
    double AlphaAnimated;
    int FilmFrame=kFilmFrame;
      bool collision=false;

    cout << "O jaki kat chcesz zmienic orientacje drona ?: ";
    cin >> alpha;  // wczytanie katu obrotu 
    while(cin.fail()){
      cin.clear();
      cin.ignore(10000,'\n');   
      cout << endl << "Zly kat !!! O jaki kat chcesz zmienic orientacje drona ?: ";
      cin >> alpha; 
    }

    quadro.AddAngle(alpha);

    DiscRotor = LoadMode(true);
    speed=LoadMode(false);

    Matrix3x3 matrixR;
    AlphaAnimated=(alpha/kFilmFrame);
    
    matrixR.Type_In(AlphaAnimated,'z');
 
    Vector3D symetry;
    symetry=quadro.GetHull().GetSymetryPoint();


    /*obrocenie wierzcholkow*/
    while(FilmFrame--){

      quadro.ChangeOrientation(matrixR,symetry);

      for(int i=0;i<4;i+=2){
        quadro[i].rotor(true,DiscRotor);
        quadro[i+1].rotor(false,DiscRotor);
      }


      if (!WriteToFile(WholeScene)) return 1;
      link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
        
       for(shared_ptr<ObjectOfScene> &Elem: WholeScene.GetScienceObject()){ 
           if((*Elem).IfCollision(quadro.MoveSymetry(),quadro.GetRadius())){
              cout << endl << "Kolizja" << endl;
              collision=true;
                    break;       
           }
       }
      usleep(CountSecondsOfFrame(speed));
      
      if(collision)
        break;

    } 
      quadro.GetTrack().push_back(quadro.GetSymetry());
  
  return 0;
}

/**
 * @brief Ruch w game mode
 * 
 * @param link - link do gnuplota
 * @param WholeScene - cala scena
 * @param quadro - dron ktorym latamy
 * @param vec - kierunek lotu
 */
void DoIt(PzG::GnuplotLink link,scene &WholeScene,Quadracopter &quadro,Vector3D vec){
            Speed DiscRotor=Fast;
            quadro.GetHull().Translate(vec);
            
            for(int i=0;i<4;i++)
            quadro[i].Translate(vec);
            
            for(int i=0;i<4;i+=2){
            quadro[i].rotor(true,DiscRotor);
            quadro[i+1].rotor(false,DiscRotor);
            }

            WriteToFile(WholeScene);
            link.Draw();  
         
          for(shared_ptr<ObjectOfScene> &Elem: WholeScene.GetScienceObject()){ 
           if((*Elem).IfCollision(quadro.MoveSymetry(),quadro.GetRadius())){
              cout << "Kolizja";
                    break;       
           }
          }
}

int main()
{
srand( time( NULL ) );

  PzG::GnuplotLink  link;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku prostokata
   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //
  link.AddFilename(mainbody);
  link.SetDrawingMode(PzG::DM_3D);
   //
   //  Ustawienie trybu rysowania 3D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy tylko x,y.
   //
  link.Init();
  link.SetRangeX(-100,250);
  link.SetRangeY(-100,250);
  link.SetRangeZ(-100,200);
  link.SetRotationZ(70);
{

      /* Utworzenie obiektu dron - wpisanie wierzcholkow na sztywno */  
                PlantOfObstacles plant;
                scene WholeScene;
                  
      shared_ptr<ObjectOfScene> object = plant.AddObject(Obstacle,Root);          
      WholeScene.GetScienceObject().push_back(static_pointer_cast<Quadracopter>(object));
      shared_ptr<Quadracopter> quadro=static_pointer_cast<Quadracopter>(plant.AddObject(Drone,Root));
      WholeScene.GetDrone().push_back(static_pointer_cast<Quadracopter>(quadro));            
      WholeScene.GetScienceObject().push_back(static_pointer_cast<Quadracopter>(quadro));
      object= plant.AddObject(Drone,Root);

      WholeScene.GetDrone().push_back(static_pointer_cast<Quadracopter>(object));            
      WholeScene.GetScienceObject().push_back(static_pointer_cast<Quadracopter>(object));

    PrintMenu(); 
  char choice='g'; // wybor w switchu, ustawiony na start na g=good
  

  unsigned int ChoiceOfDrone=1;

  /*! glowa petla interkacji z uzytkownikiem*/
  while(choice!='e'){
    
    cout << "Obecnie wyselekcjonowanym dronem jest :" << endl;
    cout << "Dron " << ChoiceOfDrone << "  Wspolrzedne srodka: " << quadro->GetSymetry();
    ObjectOfScene::HowManyScene();
    Vector3D::HowMany();
    cout << "Twoj wybor: ";
    cin >> choice ;
    if(cin.fail())return 1;
    cin.clear();
    cin.ignore(100000,'\n');

    switch (choice)
    {
      case 'D':
          quadro= static_pointer_cast<Quadracopter>(plant.AddObject(Drone,User));
          
          FOR:
          for(shared_ptr<ObjectOfScene> &Elem: WholeScene.GetScienceObject()){ 
           if((*Elem).IfCollision(quadro->MoveSymetry(),quadro->GetRadius())){
            cout << "Dron na dronie ?!?!?!?!?! No nieladnie ..." << endl;
            quadro= static_pointer_cast<Quadracopter>(plant.AddObject(Drone,User));
            goto FOR;
           }
          }

          WholeScene.GetDrone().push_back(static_pointer_cast<Quadracopter>(quadro));            
          WholeScene.GetScienceObject().push_back(static_pointer_cast<Quadracopter>(quadro));
          ChoiceOfDrone++;
          if (!WriteToFile(WholeScene)) return 1;
          link.Draw();
      break;

      case 'O':
          object= plant.AddObject(Obstacle,User);                  
          WholeScene.GetScienceObject().push_back(static_pointer_cast<Obstacles>(object));
        
        FOR3:
          for(shared_ptr<ObjectOfScene> &Elem: WholeScene.GetScienceObject()){ 
           if((*Elem).IfCollision(quadro->MoveSymetry(),quadro->GetRadius())){
            cout << "Przeszkoda na przeszkodzie ?!?!?!?!?! No nieladnie ..." << endl;
            WholeScene.GetScienceObject().remove(object);
            object= plant.AddObject(Obstacle,User);
            WholeScene.GetScienceObject().push_back(static_pointer_cast<Obstacles>(object));
            goto FOR3;
           }
          }

          if (!WriteToFile(WholeScene)) return 1;
          link.Draw();
      break;

      case 'R':
      if(ChoiceOfDrone){
      WholeScene.GetScienceObject().remove(quadro);
      WholeScene.GetDrone().pop_back();
      ChoiceOfDrone--;
      quadro=WholeScene.GetDrone().back();
      if (!WriteToFile(WholeScene)) return 1;
      link.Draw();
      }else 
      cout << "Nie mozna juz usuwac." << endl;      
      break;

      case 'd':
        if (!WriteToFile(WholeScene)) return 1;
        link.Draw();
      break;
    
      case 'r':
        /* obrocenie drona */
       if(ChangeOrientation(link,WholeScene,*quadro)) return 1;
      break;


      case 't':{
        //---------wektor translacji----------------//
                  Vector3D transVector;  
        
        quadro->GetTrack().push_back(quadro->GetSymetry());  
        int filmframe = kFilmFrame; //liczba klatek
        Speed speed,DiscRotor;
        bool collision = false;


        double angle=quadro->GetAngle();
        transVector=quadro->MoveUpDown(angle);
        transVector=transVector/kFilmFrame;

        DiscRotor = LoadMode(true); // zaladowanie szybkosci obrotu smigiel
        speed = LoadMode(false); // the same -ii- tylko ruch

        while(filmframe--){
        
          quadro->GetHull().Translate(transVector);
          
          for(int i=0;i<4;i++)
          (*quadro)[i].Translate(transVector);

          for(int i=0;i<4;i+=2){
            (*quadro)[i].rotor(true,DiscRotor);
            (*quadro)[i+1].rotor(false,DiscRotor);
          }
         
          if (!WriteToFile(WholeScene)) return 1;
          
          link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
          usleep(CountSecondsOfFrame(speed)); //dodane dla animacji

          for(shared_ptr<ObjectOfScene> &Elem: WholeScene.GetScienceObject()){ 
           if((*Elem).IfCollision(quadro->MoveSymetry(),quadro->GetRadius())){
              cout << endl << "Kolizja" << endl << endl;
              collision=true;
                    break;       
           }
          }
         if(collision)
         break;
        }

        quadro->GetTrack().push_back(quadro->GetSymetry());

        if (!WriteToFile(WholeScene)) return 1;
        link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku

      }break;

      case 'm':
        PrintMenu();
      break;

      case 's':{
      cout << endl << "Wybierz drona [1-3]: ";
      cin >> ChoiceOfDrone;
      while(cin.fail()){
        cin.ignore(10000,'\n');
        cin.clear();
        cout << endl << "Cos odwaliles ! Wybierz madrze drona [1-3]: ";
        cin >> ChoiceOfDrone;
        quadro = WholeScene.GetDrone()[ChoiceOfDrone-1];
      }

      quadro = WholeScene.GetDrone()[ChoiceOfDrone-1];
      
      }break;

      case 'q':

          for(unsigned int i=0;i<quadro->GetTrack().size();i++)
          quadro->GetTrack().pop_back();
          cout << quadro->GetTrack().size();
        
          if (!WriteToFile(WholeScene)) return 1;
          link.Draw();
      
      break;

      case 'e':
      break;

      case 'g': {
        link.SetRotationXZ(70,10);
        Vector3D forward={0,2,0}, backward={0,-2,0}, up={0,0,2}, down={0,0,-2}, left={2,0,0},right={-2,0,0};  
        int Choice=1;
        initscr();
        keypad(stdscr, TRUE);
       
        Choice = getch();
        while(Choice!=KEY_BACKSPACE){
          switch (Choice){
          
            case KEY_UP:
            DoIt(link,WholeScene,*quadro,forward);
            break;
    
            case KEY_DOWN:
            DoIt(link,WholeScene,*quadro,backward);
            break;

            case KEY_LEFT:
            DoIt(link,WholeScene,*quadro,right);
            break;
            
            case KEY_RIGHT:
            DoIt(link,WholeScene,*quadro,left);
            break;
                        
            case 32:
            DoIt(link,WholeScene,*quadro,up);
            break;
          
            case 9:
            DoIt(link,WholeScene,*quadro,down);
            break;

          }
        
          refresh(); 
          Choice = getch(); 
        }
           
        getch();
        endwin();

      }break;

      default:
        cout << "Cos zle wpisales ;( " << endl;
      break;
    }
  }
  
  }
    ObjectOfScene::HowManyScene();
    Vector3D::HowMany();

}
