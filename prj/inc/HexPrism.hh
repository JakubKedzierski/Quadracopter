#pragma once

#include "vector.hh"
#include "matrix3x3.hh"
#include "figures3D.hh"

using namespace std;
const int kHexNodes=12;

/*!
 * \file
 * \brief Definicja graniastoslupa szescikatnego
 *
 * Plik zawiera klase graniastoslupa szesciokatnego 
 * oraz modyfikacje szybkosci obrotu
 * 
 */

/**
 * @brief Wybor odpowiedniej szybkosci rotowania smigiel
 * 
 */
enum Speed{Null, Slow , Medium , Fast};

/**
 * @brief Klasa modelujaca pojecie graniastoslupow prawidlowych szesciokatnych
 * 
 * Klasa wykorzystywana do sformulowania modelu smigla
 *
 */
class HexPrism:public figures3D{

  public:
    /**
      * @brief Stworzenie nowego obiektu z mozliwoscia ustalenia jego polozenia
      * na plaszczyznie xy
      * 
      * @param x - zmiana polozenia obiektu wedlug osi x
      * @param y - zmiana polozenia obiektu wedlug osi y
      */
    HexPrism(double x=0,double y=0,double z=0);

    /**
     * @brief Pobranie srodka symetrii graniastoslupa
     * 
     * Metoda przydatna przy przesuwaniu wspolrzednych
     * do ukladu wspolrzednych danego graniastoslupa
     * szesciokatnego
     * 
     * @return Vector3D - srodek symetri graniastoslupa
     */
    Vector3D GetSymetryPoint()const;

    /**
     * @brief Rotowanie smigla podczas lotu
     * 
     * Rotujac smiglo najpierw przesuwamy uklad
     * wspolrzednych do ukladu wspolrzednych graniastoskupa
     * szeciokatnego dokonujemy rotacji, a nastepnie przywracamy
     * bazowy uklad wspolrzednych
     * 
     * @param side - zmienna pomocna do ustalenia kierunku obrotu [lewo/prawo]
     * @param speed - szybkosc obrotu smigla
     */
    void rotor(bool side,Speed speed);
};

/**
 * @brief "zaladowanie" szybkosci obrotu smigla
 * 
 * @return Speed - szybkosc obrotu smigla
 */
Speed LoadMode(bool RotorOrHull);

/**
 * @brief Zapis wspolrzednych graniastoslupa szesciokatnego do pliku
 * 
 * @param stream - strumien do ktorego zapisujemy
 * @param hex - graniastoslup ktory zapisujemy
 * @return std::ofstream& - strumien z zapisanymi danymi
 */
std::ofstream& operator << (std::ofstream & stream, HexPrism & hex);

