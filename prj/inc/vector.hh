#pragma once

#include <iostream>
#include <iomanip>
using namespace std;


/*!
 * \file
 * \brief Definicja szablonu Vector<>
 *
 * Plik zawiera szablon wektora
 */


/*!
 * \brief Pojecie wektora w ukladzie wspolrzednych
 * 
 *  Szablon wektor modeluje pojecie wektora w ukladzie 
 *  wspolrzednych. Mozliwe jest dowolne wybranie wymiaru wektora.
 *  Szablon zawiera przeciazenia operatorow indeksujacych, operatora 
 * dodawania oraz dzielenia. Konstruktor przypisuje kazdemu elementowi
 * wektora wartosc 0.
 *  
 */
template <typename Typ,int Dimension>
class Vector {

    /**
      * @brief Wspolrzedne wektora
      * 
      */
    Typ coordinates[Dimension];

 public:  

 /**
   * @brief Licznik akutalnie istniejacych obiektow
   * 
   */
 static int counter;

  /**
   * @brief licznik stworzonych obiektow
   * 
   */
 static int CounterUpdated;

  /**
   * @brief Zliczanie i obrazowanie ilosci obiektor Vector
   * 
   */
 static void HowMany(){
   cout << endl << "Liczba stworzonych obiektow Vector =" << CounterUpdated << endl ;
   cout << "Liczba aktualnie istniejacych obiektow Vector =" << counter << endl << endl;
   }

/**
 * @brief Construct a new Vector object
 * 
 * Kazda wspolrzedna otrzymuje wartosc 0
 * 
 */
 Vector(){

   for(int i=0;i<Dimension;i++){coordinates[i]=0;}
  
   CounterUpdated++; 
   counter++;
 }

~Vector(){counter--;}


/**
 * @brief Konstruktor paramatryczny , podajemy wszystkie wspolrzedne wektora
 * 
 * @param x  -wsp x
 * @param y  - wsp y
 * @param z  - wsp z
 */
Vector(double x,double y,double z)
  {coordinates[0]=x;coordinates[1]=y;coordinates[2]=z;counter++;CounterUpdated++;}

/**
 * @brief Konstuktor kopiujacy
 * 
 * @param vec - skopiowany obiekt
 */
Vector(const Vector &vec){
  for(int i=0;i<Dimension;i++){coordinates[i]=vec[i];}
  counter ++;}

/**
 * @brief Zapisanie wektora wspolrzednych
 * 
 * @param Index - wybor osi
 * @return Typ& - zwracana wartosc wspolrzednej
 */
Typ &operator[] (int Index){return coordinates[Index];}


/**
 * @brief uzyskanie wartosci wspolrzeednej
 * 
 * @param Index - wybor osi
 * @return Typ - wartosc wspolrzednej
 */
Typ operator[] (int Index)const {return coordinates[Index];}


/**
 * @brief Dodawanie dwoch wektorow
 * 
 * @param vector2 - wektor dodawany
 * @return Vector - wektor bazowy po dodaniu drugiego wektora
 */
Vector operator += (Vector vector2){

  for(int i=0;i<Dimension;i++){
    coordinates[i]+=vector2[i];
  }

return (*this);
}

/**
 * @brief Przeciazenie dzielenia 
 * szczegolne pomocne przy animacji
 * 
 * @param divorce - dzielnik
 * @return Vector& - podzielony wektor
 */
Vector &operator /(double divorce){
    for(double &vector: coordinates)
        vector=vector/divorce;
return (*this);
}

  /**
   * @brief Przeciazenie odejmowania wektorow
   * 
   * @param vector2 - wektor odejmowany
   * @return Vector - zwracany wektor po odjeciu
   */
Vector operator -=(Vector vector2){

   for(int i=0;i<Dimension;i++){
    coordinates[i]-=vector2[i];
  }

return (*this);
}

/**
 * @brief Przeciazenie operatora porownania
 * 
 * @param vector2 - wektor do porownania
 * @return true - rowne
 * @return false -  nie rowne
 */
bool operator ==(Vector vector2){
   
   for(int i=0;i<Dimension;i++){
    
    if(coordinates[i]!=vector2[i])
    return false;    
  }

return true;
}

 /**
  * @brief Odejmowanie bez zmiany obiektu
  * 
  * @param vector2 - wektor ktory odejmujemy
  * @return Vector  - zwracany wektor po odjeciu
  */
Vector operator -(Vector vector2)const{
Vector vec;

   for(int i=0;i<Dimension;i++){
    vec[i]=(*this)[i]-vector2[i];
  }

return vec;
}

};


/**
 * @brief Wczytania wektora translacji
 * 
 * @tparam Typ - Typ wspolrzednej
 * @tparam Dimension - wymiar wektora
 * @param stream - stumien do wczytywania
 * @param vector - wektor wczytywany
 * @return std::istream& - zwracamy stumien z wczytanym wektorem
 */
template <typename Typ, int Dimension>
inline
std::istream& operator >> (std::istream & stream, Vector<Typ,Dimension> & vector){


                stream >> vector[0]  >> vector[1] >> vector[2] ;
                
                while (stream.fail()) {
                        cerr << "Nieprawidlowy wektor" << endl ;
                        cerr << "Sprobuj ponownie wpisac odpowiedni wektor" << endl;
                        stream.clear();
                        stream.ignore(10000,'\n');
                        stream >> vector[0] >> vector[1] >> vector[2];
                }
              
return stream;
}



/**
 * @brief Wypisanie wspolrzednych wektora
 * 
 * @tparam Typ - typ wspolrzednych 
 * @tparam Dimension - wymiar wektora
 * @param output_stream - stumien do zapisu wspolrzednych 
 * @param vector - wyswietlany wektor
 * @return std::ostream& - stumien z danymi
 */
template <typename Typ,int Dimension>
inline
std::ostream& operator << (std::ostream & output_stream, const Vector<Typ,Dimension> & vector){

          for(int i=0;i<Dimension;i++)
        output_stream << setw(16) << fixed << setprecision(10) << vector[i];
 
            output_stream << endl;

return output_stream;
}

/**
 * @brief Zapisanie wspolrzednych do pliku
 * 
 * @tparam Typ - typ wspolrzednej
 * @tparam Dimension - wymiar wektora
 * @param output_stream - zwracdany strumien plikowy z danymi
 * @param vector - wektor
 * @return std::ofstream& - strumien z danymi
 */
template <typename Typ,int Dimension>
inline
std::ofstream& operator << (std::ofstream & output_stream, const Vector<Typ,Dimension> & vector){

          for(int i=0;i<Dimension;i++)
        output_stream << setw(16) << fixed << setprecision(10) << vector[i];
 
            output_stream << endl;

return output_stream;
}

/**
 * @brief Wyzerowanie licznika
 * 
 */
template <typename Typ,int Dimension>
int Vector<Typ,Dimension>::counter=0;

/**
 * @brief Wyzerowanie licznika
 * 
 */
template <typename Typ,int Dimension>
int Vector<Typ,Dimension>::CounterUpdated=0;

