#pragma once

#include "vector3D.hh"
#include <iostream>
#include <cmath>

/*!
 * \file matrix.hh
 * \brief Definicja szablonu macierzy
 *
 * Ten plik powinien zawierać definicję szablonu Matrix<>.
 * W tym celu należy przerobić definicję klasy Matrix3x3.
 */

/*!
 *
 * \brief Szablon modelujacy pojecie macierzy
 * 
 * Szablon modeluje pojecie macierzy,do ktorej mozemy wpisac odpowiednie wartosci
 * Dzieki przeciazeniu operatorow () mozemy bezposrednio odwolac sie do pol macierzy
 * reprezentowanych jako tablica 
 * 
 */
template <int Dimension>
class Matrix{
   
   /**
    * @brief Wspolrzedne macierzy przechowywane w dwuwymiarowej tablicy
    * 
    */
   double a[Dimension][Dimension]; 

public:

  /**
   * @brief Pobranie wartosci danego pola macierzy
   * 
   * @param Index1 - wiersz
   * @param Index2 - kolumna 
   * @return double&  - wartosc w danym polu, z mozliwoscia zmianny
   */
  double &operator()(int Index1,int Index2){return a[Index1][Index2];}
  
  /**
   * @brief Pobranie wartosci danego pola macierzy bez mozliwosci modyfikacji tego pola
   * 
   * @param Index1 - wiersz
   * @param Index2 - kolumna
   * @return double - wartosc danego pola macierzy bez mozliwosci modyfikacji
   */
  double operator()(int Index1,int Index2)const{return a[Index1][Index2];}

  /**
   * @brief Stworzenie nowego obiektu macierzy z przypisaniem zerowych wartosci
   * 
   */
  Matrix()
  {
    for(int i=0;i<Dimension;i++)
    for(int j=0;j<Dimension;j++)
    a[i][j]=0;
  }

  /**
   * @brief Wpsisanie odpowiednich wartosci do macierzy
   * 
   * Funkcja na potrzeby macierzy 3 wymiarowej. Umozliwia
   * wpisanie odpowiedniej macierzy obrotu(dla kazdej
   * osi wartosci macierzy obrotu sa inne)
   * 
   * @param alpha - kat obrotu  
   * @param ChoiceOfAxix - wybor osi obrotu
   */
  void Type_In(double alpha=1,char ChoiceOfAxix='z')
  {

      alpha=M_PI*alpha/180; // zamiana stopni na radiany

    if(Dimension==3){
      switch(ChoiceOfAxix){
        case 'z':
        (*this)(0,0)=cos(alpha);
        (*this)(0,1)=-sin(alpha);
        (*this)(0,2)=0;
        (*this)(1,0)=sin(alpha);
        (*this)(1,1)=cos(alpha);
        (*this)(1,2)=0;
        (*this)(2,0)=0;
        (*this)(2,1)=0;
        (*this)(2,2)=1;
        break;
      
        case 'y':
        (*this)(0,0)=cos(alpha);
        (*this)(0,1)=0;
        (*this)(0,2)=sin(alpha);
        (*this)(1,0)=0;
        (*this)(1,1)=1;
        (*this)(1,2)=0;
        (*this)(2,0)=-sin(alpha);
        (*this)(2,1)=0;
        (*this)(2,2)=cos(alpha);
        break;
      
        case 'x':
        (*this)(0,0)=1;
        (*this)(0,1)=0;
        (*this)(0,2)=0;
        (*this)(1,0)=0;
        (*this)(1,1)=cos(alpha);
        (*this)(1,2)=-sin(alpha);
        (*this)(2,0)=0;
        (*this)(2,1)=sin(alpha);
        (*this)(2,2)=cos(alpha);
        break;
      
        default:
       // cerr << "Cos jest zle";
        break;
      }
    }else
    {
      cout << "Konstruktor stworzony tylko dla 3x3 dla wymagan programu";
    }
  }

  /**
   * @brief mnozenie wektora przez macierz
   * 
   * mnozenie wektora przez macierz obrotu
   * do ustalenia wspolrzednych po operacji rotacji
   * 
   * @param vector - mnozony wektor
   * @return Vector3D - przemnozony wektor
   */
  Vector3D operator *(Vector3D &vector)const 
  {
      double vector2[Dimension]; // wektor pomocniczy

          /* przepisanie do wektora pomocniczego*/
      for(int i=0;i<Dimension;i++)
          vector2[i]=vector[i];

      // przemnozenie wektora przez macierz
      for(int i=0;i<Dimension;i++)
      vector[i]=(*this)(i,0)*vector2[0]+(*this)(i,1)*vector2[1]+(*this)(i,2)*vector2[2];
    
    return vector;
  }

  /**
   * @brief  Mnozenie dwoch macierzy
   * 
   * @param matrix2 - drugi czynnik mnozenia, wymagane jest
   * aby ten czynnik byl tych samych rozmiarow co pierwszy czynnik
   * 
   * @return Matrix<Dimension> - przemnozona macierz
   */
  Matrix<Dimension> operator *(Matrix<Dimension> &matrix2)
  {

    Matrix<Dimension> matrix1;
    for(int i=0;i<Dimension;i++){
      for(int j=0;j<Dimension;j++){
       matrix1(i,j)=(*this)(i,j);
      }
    }

    for(int i=0;i<Dimension;i++){
      for(int j=0;j<Dimension;j++){
       (*this)(i,j)=0;
      }
    }

    for(int i=0;i<Dimension;i++){
      for(int j=0;j<Dimension;j++){
        for(int k=0;k<Dimension;k++){
          (*this)(i,j)=(*this)(i,j)+matrix1(i,k)*matrix2(k,j);
        }
      }
    }
  
    return  (*this);
  }

};


/**
 * @brief Przeciazenia operacji wyswietlania macierzy
 * 
 * Operacja przydatna przy debugowaniu programu
 * Pokazuje aktualne wartosci macierzy obrotu
 * 
 * @tparam Dimension - rozmiar macierzy
 * @param stream  - strumien na ktory maja zostac wypisane dane
 * @param matrix - macierz ktorej wspolrzedna chcemy wypisac
 * @return std::ostream& 
 */
template <int Dimension>
inline
std::ostream& operator << (std::ostream &stream, const Matrix <Dimension> &matrix)
{

  for(int i=0;i<Dimension;i++){
  stream << endl;
    
    for(int j=0;j<Dimension;j++){
    stream <<  matrix(i,j); 
   
    }
  }

 return stream;  
}


