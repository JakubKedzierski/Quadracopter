#pragma once
#include "ObjectOfScene.hh"
#include "cuboid.hh"

/**
 * @brief Klasa modeluje pojecie przeszkody na scenie
 * 
 */
class Obstacles:public ObjectOfScene{

    /**
     * @brief Przeszkody sa wizualizowane za pomoca prostopadloscianow
     * 
     */
    Cuboid cub;

public:
    /**
     * @brief Construct a new Obstacles object
     * 
     */
    Obstacles(){Cuboid one;cub=one;symetry=one.GetSymetryPoint();}

    /**
     * @brief Construct a new Obstacles object
     * 
     * @param centre - srodek symetrii przeszkody
     * @param size - rozmiary przeszkody
     */
    Obstacles(Vector3D centre,Vector3D size);

    /**
     * @brief Dobranie sie do przeszkody
     * 
     * @param Index - numer przeszkody
     * @return Cuboid - przeszkoda
     */
    Cuboid GetObstacle (){return cub;}

    /**
     * @brief Sprawdzanie kolizji z obiektami
     * 
     * @param PhysicalPoint - srodek symetri wybranego drona
     * @param radius - promien walca przyblizajacego
     * @return true - detekcja kolizji
     * @return false - nie ma kolizji
     */
    bool IfCollision(Vector3D PhysicalPoint, double radius)const ;

    /**
     * @brief Zapis przeszkody do pliku
     * 
     * @param stream - strumien do zapisu
     * @return true - udany zapis
     * @return false - nieudany  zapis
     */
    bool WriteToFile(ofstream &stream);

};

/**
 * @brief Zapis przeszkod
 * 
 * @param output_ofstream - stumien do zapisu 
 * @param obs - przeszkody
 * @return std::ofstream& - stumien z zapisanymi danymi
 */
std::ofstream& operator << (std::ofstream & output_ofstream, Obstacles &obs);