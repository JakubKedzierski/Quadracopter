#pragma once

#include <vector>
#include "vector3D.hh"
#include "matrix3x3.hh"

/**
 * @bief Plik zawiera model pojecia figury geometrycznej 3-wymiarowej
 * 
 */

/**
 * @brief Model szerokiego pojecia figury geometrycznej 3-wymiarowej, klasy nadrzednej
 * 
 * Zawiera typowe atrybuty i metody ktore moze posiadac dowolna figura geometryczna
 * 
 */
class figures3D
{
protected:
   
   /**
    * @brief wierzcholki figury geometrycznej lub punkty nalezace do niej,
    * mozna stworzyc dowolna ilosc wierzcholkow
    * 
    */
  vector<Vector3D> P;
  
public:
 
  /**
    * @brief Odwolanie do wierzcholka z mozliwa zmiana wartosci
    * 
    * @param Index - indeks wierzcholka
    * @return Vector3D& - zwracamy wierzcholek
    */
  Vector3D &operator[](int Index){return P[Index];}    


  /**
   * @brief Odowolanie do wierzcholka bez mozliwosci zmiany wartosci
   * 
   * @param Index - indeks wierzcholka
   * @return Vector3D - zwracamy wierzcholek
   */
  Vector3D operator[](int Index)const{return P[Index];}

  /**
   * @brief Rotacja kazdego punktu nalezacego do figury
   * 
   * @param matrix - macierz obrotu
   */
  void rotate(Matrix3x3 matrix);

  /**
   * @brief translacja kazdego punktu nalezacego do danej figury
   * 
   * @param offset -zadany wektor translacji
   */
  void Translate(Vector3D offset);
};
