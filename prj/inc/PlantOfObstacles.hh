#include "scene.hh"
#include <cstdlib>
#include <ctime>

/**
 * @brief numer identyfikacyjny obiektu
 * 
 */
enum ID {Drone,Obstacle};

/**
 * @brief Wybor uzytkownik/programista
 * 
 */
enum Users{User,Root};

/**
 * @brief Klasa modeluje pojecie fabryki obiektow
 * 
 * Tyllko tutaj mozliwe jest tworzenie obiektow klasy przeszkoda oraz dron
 * 
 */
class PlantOfObstacles{

public:

    /**
     * @brief Metoda tworzaca nowy obiekt
     * 
     * @param id - identyfikator obiektu (Dron lub przeszkoda)
     * @param users - uzytkownik ktory tworzy obiekt 
     * @return shared_ptr<ObjectOfScene> - nowy stworzony obiekt zrzutowany na obiekt sceny
     */
    shared_ptr<ObjectOfScene> AddObject(ID id,Users users) const;

};

