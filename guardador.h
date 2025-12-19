#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include "arbol.h"
#include "alien.h"
#ifndef GUARDADOR_H
#define GUARDADOR_H
void escribir(std::vector<Alien>& vector_aliens, SplayTree& tree ,
  const std::string& nombre_archivo){
  //Obtener ruta del ejecutable.

  std::ofstream archivo;
  archivo.open(nombre_archivo,std::ios::out);
  if(archivo.fail()){
    std::cout<<"\nError!! No se pudo acceder a las muestras de ADN\n";
    return;
  }
  //std::cout<<"\nArchivo abierto exitosamente!\n";
  for(int i = 0; i < vector_aliens.size();i++){
    archivo<<vector_aliens[i].getNombre()<<";"
           <<vector_aliens[i].getInteligencia()<<";"
           <<vector_aliens[i].getFuerza()<<";"
           <<vector_aliens[i].getVelocidad()<<";"
           <<vector_aliens[i].getResistencia()<<";"
           //<<vector_aliens[i].getTotal()<<";"
           <<vector_aliens[i].getVecesUsado()<<";"
           <<vector_aliens[i].getVecesElegido()<<";"
           <<vector_aliens[i].getBatallasGanadas()<<"\n";
 //std::cout << "Escribiendo alien " << i << ": " << vector_aliens[i].getNombre() << "\n";
  }
//Mi separador seran 10 guiones.
  archivo<<"----------\n";
  //std::stringstream aux;
  archivo<<tree.print_tree();


archivo.close();



}



void leer(std::vector<Alien>& vector, const std::string nombre_archivo){

  std::ifstream archivo(nombre_archivo);
  //archivo.open(nombre_archivo,std::ios::in);
  if(!archivo.is_open()){
    return;
  }

  std::string line;

  /*Inicia activado porque siempre empezamos con vector,
  ya luego pasamos a splay*/
  while(std::getline(archivo,line)){
    if(line == "----------"){

      archivo.close();
      return;

    }

    std::istringstream ss(line);
    std::string nombre;
    int inteligencia, fuerza, velocidad, resistencia, batallas_ganadas,
    veces_usado, veces_elegido;
    char d;
    //Delimeter
    std::getline(ss,nombre,';');
    ss>> inteligencia >> d >> fuerza >>d >> velocidad >> d >> resistencia >> d
      >> veces_usado >> d >> veces_elegido >>d>>batallas_ganadas;

      Alien alien(nombre,inteligencia,fuerza,velocidad,resistencia,
      veces_usado,veces_elegido,batallas_ganadas);

      vector.push_back(alien);



  }


}


void leerSplay(std::vector<std::vector<std::string>>& info_nodos,
const std::string& nombre_archivo){

  std::ifstream archivo(nombre_archivo);
  if(!archivo.is_open()){
    return;
  }
  std::string line;
  bool copiar = false;
  while(std::getline(archivo,line)){

    if (line == "----------"){
      copiar = true;
      continue;
    }
    if (copiar){

      std::istringstream ss(line);
      std::string nombre, padre, izq, der;
      std::getline(ss, nombre, ';');
      std::getline(ss, padre, ';');
      std::getline(ss, izq, ';');
      std::getline(ss, der, ';');
      //std::vector<std::string> nodo = {nombre, padre, izq, der};
      info_nodos.push_back({nombre, padre, izq, der});
    }


  }

  archivo.close();
}
#endif
