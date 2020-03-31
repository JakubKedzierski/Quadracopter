#pragma once

#include "vector3D.hh"

/**
 * @brief Klasa bazowa dla drona i przeszkod
 * 
 * Modeluje pojecie obiektu sceny, przypisuje mu srodek symetri
 * 
 */
class ObjectOfScene{

protected:

    /**
     * @brief srodek symetri obiektu sceny
     * 
     */
   Vector3D symetry;

public:

    /**
    * @brief Liczniki wystapien obiektow sceny
    * 
    */
    static int counterS;

    /**
     * @brief Calkowity licznik wystapien obiektow sceny
     * 
     */
    static int AddCounter;

    /**
     * @brief Construct a new Object Of Scene object
     * 
     */
    ObjectOfScene(){symetry={0,0,0};counterS++;AddCounter++;}

    /**
     * @brief Destroy the Object Of Scene object
     * 
     */
    virtual ~ObjectOfScene(){counterS--;}

    /**
     * @brief Konstrktor kopiujacy
     * 
     * @param obj - obiekt sceny
     */
    ObjectOfScene(const ObjectOfScene &obj){counterS++;}    

    /**
     * @brief Wypisanie ilosci obiektow sceny
     * 
     */
    inline static void HowManyScene()
    {cout << endl << "Liczba stworzonych obiektow sceny = " <<AddCounter;
    cout << endl <<"Liczba aktualnie isniejacych obiektow sceny = " <<counterS << endl;}

    
    /**
     * @brief Sprawdzenie kolizji z obiektem
     * 
     * 
     * @param PhysicalPoint - srodek symetri wybranego drona
     * @param radius - promien
     * @return true  - jest kolizja
     * @return false - nie ma kolizji
     */
    virtual bool IfCollision(Vector3D PhysicalPoint, double radius)const {cout << "Kolizja z Obiektu";return false;}

    /**
     * @brief Zapis do pliku obiektow sceny
     * 
     * Dla kazdego obiektu zapis uzywa innego przeciazenia dlatego
     * ta metoda jest wirtualna
     * 
     * @param stream - strumien do zapisu
     * @return true - udany zapis
     * @return false - nieudany zapis
     */
    virtual bool WriteToFile(ofstream &stream){return false;}

    /**
     * @brief Pobranie punktu symetri
     * 
     * @return Vector3D& - punkt symetri
     */
    Vector3D &GetSymetry(){return symetry;} 

};


