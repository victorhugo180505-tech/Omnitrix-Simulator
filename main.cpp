#include "arbol.h"
#include <vector>
#include "omnitrix.h"
#include "menu.h"
//#include "funciones_adn.h"
#include "alien.h"
#include "guardador.h"
#include <unordered_map>
void asignarConexiones(std::vector<Node>& nodos_desconectados,
  const std::vector<std::vector<std::string>>& conexiones) {
    //Mapa de nombre a puntero con el nodo que contiene al alien.
    std::unordered_map<std::string, Node*> nombre_a_nodo;
    for (auto& nodo : nodos_desconectados) {
        nombre_a_nodo[nodo.alien.getNombre()] = &nodo;
    }

    //Guardar padre, e hijos correspondientes.
    for (int i = 0; i < nodos_desconectados.size(); i++) {
        std::string nombre_actual = conexiones[i][0];
        std::string padre_nombre = conexiones[i][1];
        std::string izquierdo_nombre = conexiones[i][2];
        std::string derecho_nombre = conexiones[i][3];

        //Buscar el nodo actual en el mapa recién creado
        Node* nodo_actual = nombre_a_nodo[nombre_actual];

        //Asignar el padre si existe
        if (!padre_nombre.empty() && nombre_a_nodo.count(padre_nombre)) {
            nodo_actual->parent = nombre_a_nodo[padre_nombre];
        }

        //Asignar izquierdo si existe en el Hash
        if (!izquierdo_nombre.empty() && nombre_a_nodo.count(izquierdo_nombre)) {
            nodo_actual->left = nombre_a_nodo[izquierdo_nombre];
        }

        //Asignar el hijo derecho si existe en el Hash
        if (!derecho_nombre.empty() && nombre_a_nodo.count(derecho_nombre)) {
            nodo_actual->right = nombre_a_nodo[derecho_nombre];
        }
    }



}

std::unordered_map<std::string,Alien> crearHash(
  const std::vector<Alien>& aliens_vect){
  std::unordered_map<std::string,Alien> nuevo_hash;
  for (auto alien: aliens_vect){
    nuevo_hash[alien.getNombre()] = alien;
  }
  return nuevo_hash;
}
int main(){
  std::unordered_map<std::string,Alien> alien_hash;
  SplayTree arbol;
  arbol.removeAll();
  std::string nombre_archivo = "ADN.txt";

  std::vector<Alien> aliens_archivo_vector;
  std::vector<std::vector<std::string>> conexiones;
  //std::cout<<"Banderafinal";
  leer(aliens_archivo_vector,nombre_archivo);
  //std::cout<<"Banderaleer";
  leerSplay(conexiones,nombre_archivo);
  //std::cout<<"BanderaleerSplay";
  std::vector<Alien> aux = aliens_archivo_vector;
  std::vector<Node> nodos_desconectados;

  if(conexiones.size()!= 0){
    for (int i = 0; i < aliens_archivo_vector.size();i++){
      //std::cout<<"\n"<<i<<"\n";
      for(int j = 0; j < aux.size();j++){
        //std::cout<<"\n"<<j<<"\n";

        if(conexiones[i][0]==aux[j].getNombre()){
          //std::cout<<"Comparando: "<<conexiones[i][0]<<" y "<<aux[j].getNombre()<<"\n";
          nodos_desconectados.push_back(Node(aux[j]));
          //std::cout<<"\nEliminando: "<<aux[j].getNombre()<<"\n";
          aux.erase(aux.begin()+j);
          break;
        }
      }

    }
    //Asignamos las conexiones con un unordered_map.
    asignarConexiones(nodos_desconectados,conexiones);
    if (!nodos_desconectados.empty()) {
        arbol.root = &nodos_desconectados[0];
    }

  }
  else if(aliens_archivo_vector.size()!= 0){
    for (int i = 0; i < aliens_archivo_vector.size();i++){
      arbol.add(aliens_archivo_vector[i]);
    }
  }
  else{
    std::cout<<"\nVacio, registrando aliens iniciales por defecto!\n";
    std::vector<Alien> aliens_iniciales_vector = {
      Alien("HeatBlast", 10, 12, 10, 12, 4, 2, 2),
      Alien("Grey Matter", 20, 2, 4, 1, 4, 1, 1),
      Alien("Wildmutt", 13, 15, 16, 16, 6, 4, 4),
      Alien("Ghostfreak", 14, 9, 17, 20, 5, 3, 3),
      Alien("Four Arms", 12, 18, 15, 18, 8, 4, 4),
      Alien("Stinkfly", 12, 10, 17, 12, 5, 2, 2),
      Alien("Diamondhead", 14, 17, 14, 19, 7, 5, 5),
      Alien("Upgrade", 18, 10, 13, 14, 6, 3, 3),
      Alien("XLR8", 16, 12, 20, 14, 9, 7, 7),
      Alien("Cannonbolt", 12, 16, 16, 18, 5, 2, 2),
      Alien("Ripjaws", 10, 12, 10, 15, 4, 1, 1),
      Alien("Blitzwolfer", 13, 16, 15, 17, 7, 4, 4),
      Alien("Upchuck", 12, 10, 8, 14, 3, 1, 1),
      Alien("Benmummy", 11, 14, 12, 18, 4, 2, 2),
      Alien("Benvicktor", 10, 18, 10, 19, 6, 3, 3),
      Alien("Eye Guy", 15, 12, 9, 15, 5, 2, 1),
      Alien("Way Big", 8, 20, 12, 20, 8, 5, 4),
      Alien("Ditto", 12, 8, 15, 10, 3, 1, 0),
      Alien("Eon", 18, 12, 13, 17, 6, 4, 3),
      Alien("Spitter", 10, 10, 12, 10, 4, 2, 1)
    };
    /*Deje 20 aliens iniciales para que al aniadir uno mas se pruebe el
    ordenamiento con mergeSort en vez de insertionSort*/


    for (int i = 0; i < aliens_iniciales_vector.size();i++){
      arbol.add(aliens_iniciales_vector[i]);
      aliens_archivo_vector.push_back(aliens_iniciales_vector[i]);
    }

  }

  alien_hash = crearHash(aliens_archivo_vector);
  Omnitrix omnitrix(aliens_archivo_vector,arbol,alien_hash);
  Menu menu (omnitrix,0);
  menu.menuPrincipal();

  std::cout<<"\n"<<arbol.print_tree();
  escribir(aliens_archivo_vector,arbol,nombre_archivo);
  std::cout<<"\nEscritura terminada\n";

  //std::cout<<"Prueba terminada!";
}
