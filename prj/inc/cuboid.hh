#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include "matrix3x3.hh"
#include "figures3D.hh"
const int kCubNodeNumber =8; 


/*!
 * \file 
 * \brief definicja klasy prostopadloscian, jako kadluba dronu
 * 
 */


/**
 * @brief Klasa prostopadloscian - jako kadlub dronu
 * 
 */
class Cuboid : public figures3D{
  
  public:
  /**
   * @brief Tworzymy nowy obiekt prostopadloscianu 
   * 
   * Automatycznie przypisujemy wierzcholki
   * Dzieki temu uzytkownik nie musi podawac wierzcholkow, tylko operuje na 
   * gotowym obiekcie
   */
  Cuboid(); 
  
  /**
   * @brief Construct a new Cuboid object
   * 
   * @param change - zestaw parametrow okreslajacyh ustawienia i 
   * rozmiar prostopadloscianu kolejno: x,y,z,scalex,scaley,scalez
   */
  Cuboid(double *change);

  /**
   * @brief Construct a new Cuboid object
   * 
   * @param centre - srodek symetri nowego prostopadloscianu
   * @param size - rozmiary prostopadloscianu
   */
  Cuboid(Vector3D centre,Vector3D size);
  
/**
 * @brief Pozyskanie punktu symetrii prostopadloscianu
 * 
 * Za punkt symetrii przyjeto srodek ciezkosci prostopadloscianu
 * Funkcja to moze byc wykorzystywana do przesuwania wspolrzednych
 * do ukladu wspolrzednych prosotpadloscianu
 * 
 * @return Vector3D - punkt symetrii
 */
Vector3D GetSymetryPoint()const;

};

 /**
  * @brief Wypisywanie wierzcholkow na zadany strumien
  * 
  */
std::ostream& operator << (std::ostream & stream, Cuboid & cube);

  /**
   * @brief Przeciazenie operatora zapisujacego wierzcholki do pliku 
   * 
   */
std::ofstream& operator << (std::ofstream & stream, Cuboid & cube);
