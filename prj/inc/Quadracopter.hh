#pragma once

#include <iostream>
#include <fstream>
#include "cuboid.hh"
#include "HexPrism.hh"
#include <vector>
#include <iomanip>
#include <cmath>
#include "ObjectOfScene.hh"
#include <list>
#include <memory>
/**
 * @brief Liczba smigiel
 * 
 */
const int kNumberOfDisc=4;

/**
 * @brief Model pojecia dron
 * 
 * Dron sklada sie z kadluba reprezentowanego przez prostopadloscian
 * oraz 4 smigiel reprezentowanych przez graniastloslupy prawidlowe 
 * szesciokatne
 * 
 */
class Quadracopter:public ObjectOfScene{

private:

    /**
     * @brief kadlub drona reprezentowany jako prostopadloscian+
     * 
     */
    Cuboid hull;

    /**
     * @brief smigla drona reprezentowane przez graniastoslup szeciokatny
     * 
     */
    HexPrism disc[kNumberOfDisc];

    /**
     * @brief sumaryczny kat obrotu
     * 
     */ 
    double RotationAngle;

    /**
     * @brief Promien walca przyblizajacego dron
     * 
     */
    double radius;

    /**
     * @brief polowa dlugosci walca przyblizajacego dron
     * 
     */
    double height;

    /**
     * @brief Sciezka/Trasa jako lista punktow
     * 
     */
    list<Vector3D> track;


public:
friend class PlantOfObstacles;
    /**
     * @brief Zmiana kazdego wierzcholka o zadany kat obrotu
     * 
     * Aby wykonac obrot dron na poczatku jest przesuwany do bazowego 
     * ukladu wspolrzednych a dopiero nastepnie dokonana jest rotacja
     * 
     * @param matrix - macierz obrotu
     * @param symetry - punkt symetri 
     */
    void ChangeOrientation(Matrix3x3 matrix,Vector3D symetry);

    /**
     * @brief Stworzenie drona z automatycznym przypisaniem 
     * wierzcholkow
     * 
     */
    Quadracopter();

    /**
     * @brief Konstruktor parametryczny z zadanym wektorem przesuniecia
     * 
     * @param x - wspl x
     * @param y - wsp y
     * @param z - wyp x
     */
    Quadracopter(double x,double y,double z);
    
    /**
     * @brief Pobranie kadluba z mozliwoscia zmiany
     * 
     * @return Cuboid& - kadlub z mozliwoscia dokonywania zmian
     */
    Cuboid &GetHull(){return hull;}
    
    /**
     * @brief Pobranie kadluba bez mozliwosci dokonywania zmian
     * 
     * @return Cuboid - kadlub
     */
    Cuboid GetHull()const{return hull;}
   
    /**
     * @brief - Pobranie smigiel z mozliowscia modyfikacji
     * 
     * @param Index - wybor smigla
     * @return HexPrism& - smiglo z mozliwoscia modyfikacji
     */
    HexPrism &operator[](int Index){return disc[Index];}   

    /**
     * @brief Pobranie smigla bez mozliwosci modyfikacji
     * 
     * @param Index - wybor smigla
     * @return HexPrism - smiglo bez mozliwosci modyfikacji
     */
    HexPrism operator[](int Index)const{return disc[Index];} 

    /**
     * @brief zapamietanie katu obrotu
     * 
     * @param value dodany kat obrotu
     */
    void AddAngle(int value){RotationAngle+=value;}

    /**
     * @brief pobranie sumarycznego kata obrout
     * 
     * @return double- sumaryczny kat obrotu
     */
    double GetAngle()const{return RotationAngle;}  

    /**
     * @brief Wyliczenie wektora translacji
     * 
     * Funkcja wymaga interakcji z uzytkownikiem, sprawdza wszelkie warunki
     * poprawnosci. Wylicza wektor translacji na podstawie trojkata 
     * pitogarejskiego. Zaklada sie ze ruch w przod oznacz ruch o taka
     * sama odlegosc w kierunku x i y proporcjonalna do podanej drogi
     * 
     * @return Vector3D - wektor translacji , wyliczony z danych podanych przez uzytkownika
     */
    Vector3D MoveUpDown(double angle)const;

    /**
     * @brief Sprawdzanie kolizji z dronem
     * 
     * @param PhysicalPoint - srodek symetri drona ktory lata
     * @param radius - promien drona ktory lata
     * @return true - jest detekcja kolizji
     * @return false - nie ma kolizji
     */
    bool IfCollision(Vector3D PhysicalPoint,double radius)const;

    /**
     * @brief Pobierz promien walca
     * 
     * @return double& - promien
     */
    double &GetRadius(){return radius;}

    /**
     * @brief Pobierz pol wysokosci walca
     * 
     * @return double& - pol wysokosci walca
     */
    double &GetHeight(){return height;}

    /**
     * @brief Zmiana wspolrzednych srodka symetri ( punktu materialnego)
     * podczas przemieszczania/rotacji
     * 
     * @return Vector3D 
     */
    Vector3D MoveSymetry();

    /**
     * @brief Pobranie trasy
     * 
     * @return list<Vector3D>& - trasa (sciezka) 
     */
    list<Vector3D> &GetTrack(){return track;}

    /**
     * @brief Zapis drona do pliku
     * 
     * @param stream - strumien do zapisu
     * @return true - udany zapis
     * @return false - nieudany zapis
     */
    bool WriteToFile(ofstream &stream);
};

/**
 * @brief Przeciazenie operatora zapisujacego wierzcholki
 * drona do pliku
 * 
 * @param stream - strumien plikowy do zapisu wierzcholkow
 * @param quad - drona do zapisu
 * @return std::ofstream&  - strumien z zapisanymi danymi
 */
std::ofstream& operator << (std::ofstream & stream, Quadracopter & quad);