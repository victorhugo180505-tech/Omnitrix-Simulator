#include "alien.h"
#include "arbol.h"
#include <vector>
#include <unordered_map>
//#include <queue>
#ifndef OMNITRIX_H
#define OMNITRIX_H

class Omnitrix {
private:
    SplayTree& tree;
    std::vector<Alien>& aliens_unlocked;
    std::unordered_map<std::string, Alien>& aliens_hash;
    //int num_aliens_unlocked;
    //std::queue<Alien> aliens_disp;
    //Creo que el uso del queue sera por fuera y demas.
public:
  Omnitrix(std::vector<Alien>& vector_aliens, SplayTree& splay,
  std::unordered_map<std::string, Alien>& aliens_dicc)
  :aliens_unlocked(vector_aliens),tree(splay),aliens_hash(aliens_dicc){}
  void registrarVictoria(std::string nom){
    for(int i =0; i < aliens_unlocked.size();i++){
      if(aliens_unlocked[i].getNombre()==nom){
        aliens_unlocked[i].sumarVictoria();
        break;
      }
    }
  }
  void anadirSplay(Alien alien){
    tree.add(alien);
  }
  void eliminarAlienSplay(Alien alien){
    tree.remove(alien);
  }
  void registrarEleccionSplay(Alien alien){
    tree.find(alien);
    tree.root->alien.sumarEleccion();
  }

  void registrarEleccion(std::string nom){
    for(int i =0; i < aliens_unlocked.size();i++){
      if(aliens_unlocked[i].getNombre() == nom){
        aliens_unlocked[i].sumarEleccion();
        aliens_unlocked[i].sumarUso();
      }
    }
  }

  void registrarUso(std::string nom){
    for(int i =0; i < aliens_unlocked.size();i++){
      if(aliens_unlocked[i].getNombre() == nom){
        aliens_unlocked[i].sumarUso();
      }
    }
  }

  /*
  void iniciarBatalla(const std::vector<Alien>& aliens_ordenados){
    int size = aliens_ordenados.size();
    if (size != 0){
      for (int i = 0; i < size; i++){
        aliens_disp.push(aliens_ordenados[i]);
      }
    }
  }
*/
  /*int getNumUnlocked(){
    return aliens_unlocked.size();
  }*/
  const std::vector<Alien>& getAliensUnlocked(){
    //const ya que quiero solo lectura para el mostrar
    return aliens_unlocked;
  }
  std::unordered_map<std::string,Alien>& getAliensHash(){
    return aliens_hash;
  }
  /*const Alien getAlien(std::string){
    for (int i = 0; i < aliens_unlocked.size();i++){
      if(nombre == aliens_unlocked[i].getNombre()){
        aliens_unlocked.erase(aliens_unlocked.begin()+i);
        //begin devuelve un iterador y el valor de i lo ajusta.
        return;
      }
    }

  }*/

  /*void anadirAliens(std::vector<Alien>& aliens){
    aliens_unlocked = aliens;
  }*/

  void anadirAlien(Alien alien_nuevo){
    aliens_unlocked.push_back(alien_nuevo);
  }
  void borrarAlien(std::string name){
    //Hare la verificacion de que dicho alien exista en la funcion de Menu.
    for (int i = 0; i < aliens_unlocked.size();i++){
      if(name == aliens_unlocked[i].getNombre()){
        aliens_unlocked.erase(aliens_unlocked.begin()+i);
        //begin devuelve un iterador y el valor de i lo ajusta.
        return;
      }
    }
  }









};

#endif
