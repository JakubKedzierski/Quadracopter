#pragma once
#include "Quadracopter.hh"
#include "Obstacles.hh"

/**
 * @brief Klasa modeluje pojecie sceny i obiektow znajdujacych sie na niej
 * 
 */
class scene{

    /**
     * @brief tablica dynamiczna dronow( z lista jest 
     * problem z odwolaniem do konretnego elementu)
     * 
     */
    vector <shared_ptr<Quadracopter>> Drone;

    /**
     * @brief Lista wszystkich obiektow na scenie z ktorymi jest sprawdzana kolizja
     * 
     */
    list <shared_ptr<ObjectOfScene>> SceneObject;

public:
    scene(){}

    /**
     * @brief Pobranie tablicy dronow
     * 
     * @return vector <shared_ptr<Quadracopter>>  tablica dronow
     */
    vector <shared_ptr<Quadracopter>> &GetDrone(){return Drone;}

    /**
     * @brief Pobranie listy obiektow na scenie
     * 
     * @return list<shared_ptr<ObjectOfScene>> lista obiektow na scenie 
     */
    list<shared_ptr<ObjectOfScene>> &GetScienceObject(){return SceneObject;}

};



