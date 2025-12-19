#include <ctime>
#include <iostream>
#include <cctype>
#include <limits>
#include "omnitrix.h"
#include "ordenamiento.h"
#include <queue>
#include <unordered_map>
#ifndef MENU_H
#define MENU_H
Ordenamiento orden;
class Menu{

private:
  Omnitrix& dispositivo;
  int duracion_pausas;
  /*(En segundos, no todas las pausas duran el valor de la variable, algunas el
  doble o incluso mas)*/
  void delay(int secs) {
    for(int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
  }
  /*Declaro aqui los input ya que no se usa ningun cin ni getline fuera de
  estas funciones*/
  std::string input(const std::string& mensaje, std::string& cad) {
	cad = "";
	bool valido = false;
	bool espacios_consecutivos = false;
	while (!valido) {
		std::cout << mensaje<<"\n";
		getline(std::cin, cad);

		//Solo dio enter?
		if (cad.empty()) {
			std::cout << "\nError! Favor de realizar una entrada valida!\n\n";
			continue;
		}

		//Mas de 80 caracteres?
		if (cad.length() > 80) {
			std::cout << "\nError! La entrada no debe exceder 80 caracteres."
				<<"\n\n";
			continue;
		}

		//Espacios al inicio o al final?
		if (std::isspace(cad.front()) || std::isspace(cad.back())) {
			std::cout << "\nError! Favor de evitar los espacios al inicio y "
				<<"al final!\n\n";
			continue;
		}

		//Espacios consecutivos?
		espacios_consecutivos = false;
		for (int i = 1; i < cad.length() - 1; ++i) {
			if (std::isspace(cad[i]) && std::isspace(cad[i - 1])) {
				espacios_consecutivos = true;
				break;
			}
		}

		if (espacios_consecutivos) {
			std::cout << "\nNo se aceptan mas de dos espacios seguidos!\n\n";
		} else {
			valido = true;
			// La entrada es valida
		}
	}

	return cad;
}

  int input(const std::string& mensaje, int& entero){
    /*Pido por referencia para evitar crear un entero y regreso un entero para
    evitar confundirme con la estructura*/
    std::string cad = "";
    bool valido = false;
    while(!valido){
      //Mientras valido sea igual a falso.
      valido = true;
      std::cout<<mensaje<<"\n";
      getline(std::cin,cad);
      if (cad ==""){
        std::cout<<"\nError! Favor de realizar una entrada "
        <<"valida!\n\n";
      }
      else{
        for (int i = 0; i < cad.length(); i++){
          if (isdigit(cad[i]) == false){
            std::cout<<"\nError! Solo se permiten numeros enteros positivos."
            <<"\n\n";
            valido = false;
            break;
          }
        }
      }
    }
    entero = std::stoi(cad);
    return entero;
  }

  char input(const std::string& mensaje, char& car){
    std:: string cad;
    while(true){
      std::cout<<mensaje<<"\n";
      getline(std::cin,cad);
      if (cad != " " && cad.length() == 1){
        car = cad[0];
        return car;
      }
      std::cout<<"\nError! Intente de nuevo.\n\n";
    }
  }


  void mostrarAlien(std::string nom){
    std::unordered_map <std::string, Alien>& aliens = dispositivo.getAliensHash();
    //Afuera ya se tuvo que haber verificado si existia dicho alien o no.
    //std::vector<Alien> a_d = dispositivo.getAliensUnlocked();
    //a_d son los aliens desbloqueados
    std::cout<<"Nombre: "<<aliens.at(nom).getNombre()<<"\n";
    std::cout<<"Inteligencia: "<<aliens.at(nom).getInteligencia()<<"\n";
    std::cout<<"Fuerza: "<<aliens.at(nom).getFuerza()<<"\n";
    std::cout<<"Velocidad: "<<aliens.at(nom).getVelocidad()<<"\n";
    std::cout<<"Resistencia: "<<aliens.at(nom).getResistencia()<<"\n";
    std::cout<<"Puntos totales: "<<aliens.at(nom).getTotal()<<"\n";
    std::cout<<"Veces usado: "<<aliens.at(nom).getVecesUsado()<<"\n";
    std::cout<<"Veces elegido: "<<aliens.at(nom).getVecesElegido()<<"\n";
    std::cout<<"Batallas ganadas: "<<aliens.at(nom).getBatallasGanadas()<<"\n";
    std::cout<<"\n";
  }

  void mostrarAlien(int indice){
    //Afuera ya se tuvo que haber verificado si existia dicho alien o no.
    std::vector<Alien> a_d = dispositivo.getAliensUnlocked();
    //a_d son los aliens desbloqueados
    std::cout<<"Nombre: "<<a_d[indice].getNombre()<<"\n";
    std::cout<<"Inteligencia: "<<a_d[indice].getInteligencia()<<"\n";
    std::cout<<"Fuerza: "<<a_d[indice].getFuerza()<<"\n";
    std::cout<<"Velocidad: "<<a_d[indice].getVelocidad()<<"\n";
    std::cout<<"Resistencia: "<<a_d[indice].getResistencia()<<"\n";
    std::cout<<"Puntos totales: "<<a_d[indice].getTotal()<<"\n";
    std::cout<<"Veces usado: "<<a_d[indice].getVecesUsado()<<"\n";
    std::cout<<"Veces elegido: "<<a_d[indice].getVecesElegido()<<"\n";
    std::cout<<"Batallas ganadas: "<<a_d[indice].getBatallasGanadas()<<"\n";
    std::cout<<"\n";
  }

  void mostrarAlien(Alien alien){
    //Afuera ya se tuvo que haber verificado si existia dicho alien o no.
    //a_d son los aliens desbloqueados
    std::cout<<"Nombre: "<<alien.getNombre()<<"\n";
    std::cout<<"Inteligencia: "<<alien.getInteligencia()<<"\n";
    std::cout<<"Fuerza: "<<alien.getFuerza()<<"\n";
    std::cout<<"Velocidad: "<<alien.getVelocidad()<<"\n";
    std::cout<<"Resistencia: "<<alien.getResistencia()<<"\n";
    std::cout<<"Puntos totales: "<<alien.getTotal()<<"\n";
    std::cout<<"Veces usado: "<<alien.getVecesUsado()<<"\n";
    std::cout<<"Veces elegido: "<<alien.getVecesElegido()<<"\n";
    std::cout<<"Batallas ganadas: "<<alien.getBatallasGanadas()<<"\n";
    std::cout<<"\n";
  }

  void mostrarNombresYNumero(){
    std::vector<Alien> a_d = dispositivo.getAliensUnlocked();
    //Vector copia con los aliens disponibles.
    int numero_aliens = a_d.size();
    if(numero_aliens == 0){
      std::cout<<"No hay aliens desbloqueados!...\n\n";
    }
    else{
      std::cout<<"Mostrando los "<<numero_aliens<<" aliens desbloqueados:\n\n";
      for(int i = 0; i < numero_aliens;i++){
        delay(duracion_pausas);
        std::cout<<"Alien #"<<i+1<<": "<<a_d[i].getNombre()<<"\n";
        std::cout<<"\n";
    }

    }

  }

  bool mostrarCatalogo(){
    //Verificador de vacio incluido
    std::vector<Alien> a_d = dispositivo.getAliensUnlocked();
    int numero_aliens = a_d.size();
    if(numero_aliens != 0){
      for (int i = 0; i < a_d.size();i++){
          delay(duracion_pausas);
          mostrarAlien(i);
        }
    }
    else{
      for (int i = 0; i<3;i++){
        delay(duracion_pausas);
        std::cout<<".";
      }
      std::cout<<"\n\nSin registros de ADN!\n\n";
    }
    return continuarSiNo();



  }

  bool registrarAlien(){
    std::unordered_map<std::string, Alien>& alien_hash =
    dispositivo.getAliensHash();
    std::string nom;
    std::vector<Alien> a_d = dispositivo.getAliensUnlocked();
    int numero_aliens = a_d.size();
    int intelecto, poder, rapidez, tenacidad;
    int numero_intentos = 5;
    bool terminado = false;
      //Linea para limpiar cualquier salto de linea
    while(!terminado){
      terminado = true;
      std::cout<<"Inserte el nombre del alien a agregar sin espacios al "
      <<"inicio y/o al final ni mas de un espacio entre\n"
      <<"dos palabras"
      <<"\nEjemplo 1: \"Grey Matter\"\n"
      <<"Ejemplo 2: \"HeatBlast\"\n";
      nom = input("",nom);
      std::cout<<"\n\n";
      for (int i = 0; i<3;i++){
        delay(duracion_pausas);
        std::cout<<".";
      }
      std::cout<<"\n\n";
      for (int i = 0; i < numero_aliens; i++){
        if(nom == a_d[i].getNombre()){
          terminado = false;
          break;

        }
      }
      numero_intentos -= 1;
      if(numero_intentos <= 0 ){
        std::cout<<"Intentos agotados! Favor de contactar con Azmuth "
        <<"para aprender a usar esta funcion...\n\n\n";
        return continuarSiNo();
      }
      else if(!terminado){
        std::cout<<nom<<" ya esta en uso, te quedan: "<<numero_intentos
        <<" intentos.\n";
        delay(duracion_pausas);
        std::cout<<"Evita usar cualquiera de estos nombres:\n\n\n";
        mostrarNombresYNumero();
        std::cout<<"\n\n";
        delay(duracion_pausas);
        }
      }
      terminado = false;
      while(!terminado){
        terminado = true;
        std::cout<<"Digita los puntos que tendra tu alien en distintas "
        <<"categorias, usa numeros enteros entre 1 y 20\n\n";
        intelecto=input("Inserta el valor de inteligencia de tu alien:\n",
        intelecto);
        poder = input("Inserta el valor de fuerza de tu alien:\n",poder);
        rapidez=input("Inserta el valor de velocidad de tu alien:\n",rapidez);
        tenacidad =input("Inserta el valor de resistencia de tu alien:\n",
        tenacidad);
        std::cout<<"\n\n";
        if(intelecto>20  || poder>20 || rapidez>20 || tenacidad>20
          || intelecto < 1 || poder < 1 || rapidez < 1 || tenacidad < 1){
          terminado = false;
          std::cout<<"Error! Todos los atributos deben de tener un valor entre "
          <<"uno y veinte.\n\n";
        }
        else{
          char eleccion = 'a';
          std::cout<<"Caracteristicas ingresadas: \n\n\n";
          delay(duracion_pausas);
          std::cout<<"Nombre: "<<nom<<"\n";
          std::cout<<"Inteligencia: "<<intelecto<<"\n";
          std::cout<<"Fuerza: "<<poder<<"\n";
          std::cout<<"Velocidad: "<<rapidez<<"\n";
          std::cout<<"Resistencia: "<<tenacidad<<"\n\n";
          while(eleccion != 'y' && eleccion != 'n'){
            std::cout<<"Estas seguro de querer guardar esta muestra de ADN?\n";
            eleccion = input("Escribe 'y' o 'n': ",eleccion);

            if(eleccion == 'y'){
              std::cout<<"Agregando muestra";
              for (int i = 0; i<3;i++){
                delay(duracion_pausas);
                std::cout<<".";
              }
              dispositivo.anadirAlien(Alien(nom,intelecto,poder,rapidez,
              tenacidad));
              dispositivo.anadirSplay(Alien(nom,intelecto,poder,rapidez,
              tenacidad));
              alien_hash.insert({nom,Alien(nom,intelecto,poder,rapidez,tenacidad)});
              std::cout<<"\nMuestra agregada exitosamente!\n\n";
              return continuarSiNo();
            }
            else if(eleccion == 'n'){
              std::cout<<"\nOperacion cancelada!\n\n";
              return continuarSiNo();

            }
            else{
              std::cout<<"\nError! Opcion no valida.\n\n";
            }
          }

        }

      }


    return continuarSiNo();

  }

  bool eliminarADN(){
    std::vector<Alien> a_d = dispositivo.getAliensUnlocked();
    int numero_aliens = a_d.size();
    std::unordered_map<std::string, Alien>& alien_hash =
    dispositivo.getAliensHash();

    if (numero_aliens == 0){
      for (int i = 0; i<3;i++){
        delay(duracion_pausas);
        std::cout<<".";
      }
      std::cout<<"\n\nSin registros de ADN!\n\n";
      return continuarSiNo();
    }
    else{
      int numero_intentos = 5;
      std::string name;

      //Linea para limpiar cualquier salto de linea
      while(true){
        std::cout<<"Inserte el nombre del alien a eliminar sin espacios al "
        <<"inicio y/o al final"
        <<"\nEjemplo 1: \"Grey Matter\"\n"
        <<"Ejemplo 2: \"HeatBlast\"\n";

        name = input("",name);
        std::cout<<"\n\n";
        for (int i = 0; i<3;i++){
          delay(duracion_pausas);
          std::cout<<".";
        }
        std::cout<<"\n\n";
        if (alien_hash.count(name)>0){


          char eleccion = 'a';
          while (eleccion != 'y' && eleccion != 'n'){
          std::cout<<"Estas seguro de querer eliminar este alien?\n\n";
          mostrarAlien(name);
          std::cout<<"\n";
          eleccion = input("Escribe 'y' o 'n': \n",eleccion);

          if(eleccion == 'y'){
            std::cout<<"Eliminando muestra de ADN";
            for (int i = 0; i<3;i++){
              delay(duracion_pausas);
              std::cout<<".";
            }
            dispositivo.eliminarAlienSplay(alien_hash.at(name));
            dispositivo.borrarAlien(name);
            alien_hash.erase(name);


            std::cout<<"\n\n\nMuestra eliminada exitosamente!\n";
            return continuarSiNo();
          }
          else if(eleccion == 'n'){
            std::cout<<"\nOperacion cancelada!\n\n";
            return continuarSiNo();

          }
          else{
            std::cout<<"Error! Opcion no valida.\n\n";
          }

        }

          //Hasta aqui
        }
        numero_intentos -= 1;

        if(numero_intentos <= 0){
          std::cout<<"Intentos agotados! Favor de contactar con Azmuth "
          <<"para aprender a usar esta funcion...\n\n\n";
          return continuarSiNo();
        }
        std::cout<<"Nombre no encontrado, te quedan "<<numero_intentos
        <<" intentos.\n";
        delay(duracion_pausas);
        std::cout<<"Por que no pruebas con uno de estos nombres?\n\n\n";
        mostrarNombresYNumero();
        std::cout<<"\n\n";
        delay(duracion_pausas);
      }
    }
  }
  bool mostrarBaseNombre(){
    //Verificador de vacio incluido.
    std::unordered_map<std::string, Alien>& alien_hash =
    dispositivo.getAliensHash();

    if (alien_hash.size()==0){
      for (int i = 0; i<3;i++){
        delay(duracion_pausas);
        std::cout<<".";
      }
      std::cout<<"\n\nSin registros de ADN!\n\n";
      return continuarSiNo();
    }
    else{
      int numero_intentos = 5;
      std::string name;

      //Linea para limpiar cualquier salto de linea
      while(true){
        std::cout<<"Inserte el nombre del alien a buscar sin espacios al "
        <<"inicio y/o al final"
        <<"\nEjemplo 1: \"Grey Matter\"\n"
        <<"Ejemplo 2: \"HeatBlast\"\n";


        name = input("",name);
        std::cout<<"\n\n";
        for (int i = 0; i<3;i++){
          delay(duracion_pausas);
          std::cout<<".";
        }
        std::cout<<"\n\n";
        if (alien_hash.count(name)>0){
          mostrarAlien(name);
          return continuarSiNo();
        }
        numero_intentos -= 1;


        if(numero_intentos <= 0){
          std::cout<<"Intentos agotados! Favor de contactar con Azmuth "
          <<"para aprender a usar esta funcion...\n\n\n";
          return continuarSiNo();
        }
        std::cout<<"Nombre no encontrado, te quedan "<<numero_intentos
        <<" intentos.\n";
        delay(duracion_pausas);
        std::cout<<"Por que no pruebas con uno de estos nombres?\n\n\n";
        mostrarNombresYNumero();
        std::cout<<"\n\n";
        delay(duracion_pausas);
      }
    }
    //No pongo un continuar compartido debido al while(true)

  }


  bool seleccionLibre(){
    //Verificador de vacio incluido.
    //std::vector<Alien> a_d = dispositivo.getAliensUnlocked();
    //int numero_aliens = a_d.size();
    std::unordered_map<std::string, Alien>& alien_hash =
    dispositivo.getAliensHash();
    //std::cout<<alien_hash.at("Goku").getNombre();
    if (alien_hash.size() == 0){
      for (int i = 0; i<3;i++){
        delay(duracion_pausas);
        std::cout<<".";
      }
      std::cout<<"\n\nSin registros de ADN!\n\n";
      return continuarSiNo();
    }
    else{
      char eleccion = 'a';
      int numero_intentos = 5;
      std::string name;
      std::string name_actual =" ";
      bool seleccion_error;
      //int trans_seguidas = 0;
      //Linea para limpiar cualquier salto de linea
      while(true){

        seleccion_error = true;
        std::cout<<"Inserte el nombre del alien deseado sin espacios al "
        <<"inicio y/o al final"
        <<"\nEjemplo 1: \"Grey Matter\"\n"
        <<"Ejemplo 2: \"HeatBlast\"\n";


        name = input("",name);
        std::cout<<"\n\n";
        for (int i = 0; i<3;i++){
          delay(duracion_pausas);
          std::cout<<".";
        }
        std::cout<<"\n\n";


        if( (alien_hash.count(name)>0) && name_actual != name){

          name_actual = name;
          seleccion_error = false;
          numero_intentos = 5;
          std::cout<<"Transformacion actual:\n\n";
          //dispositivo.registrarUso(a_d[i].getNombre());
          dispositivo.registrarEleccion(alien_hash.at(name).getNombre());
          dispositivo.registrarEleccionSplay(alien_hash.at(name));
          mostrarAlien(name);

          //return continuarSiNo();
        }

        //Arriba


        if(numero_intentos <= 0){
          std::cout<<"Intentos agotados! Favor de contactar con Azmuth "
          <<"para aprender a usar esta funcion...\n\n\n";
          return continuarSiNo();
        }
        if(seleccion_error == true){
          numero_intentos -= 1;
          std::cout<<"Nombre no encontrado, te quedan "<<numero_intentos
          <<" intentos.\n";
          delay(duracion_pausas);
          std::cout<<"Por que no pruebas con uno de estos nombres?\n\n\n";
          mostrarNombresYNumero();
          std::cout<<"\n\n";
          delay(duracion_pausas);
        }
        else{

          while(eleccion != 'y' && eleccion != 'n'){
            std::cout<<"Deseas seguir eligiendo aliens? \n\n";
            //terminar el programa o no
            eleccion = input("Digita 'y' o 'n': ",eleccion);
            eleccion = std::tolower(eleccion);
            std::cout<<"\n\n";
            if(eleccion != 'y' && eleccion != 'n'){
              std::cout<<"Opcion invalida! Intente de nuevo.\n\n";
            }
            else if(eleccion == 'n'){
              return continuarSiNo();
              //no se quiere continuar
            }
            else{
              eleccion ='a';
              break;
            }

          }

        }
      }//Fin del while
    }
    //No pongo un continuar compartido debido al while(true)

  }



  bool seleccionPrincipal(){
    char choice = 'a';
    while(choice != '1' && choice != '2' && choice != '3' && choice != '4'){
      std::cout<<"Digite el numero que corresponda al modo de operacion deseado:"
               <<"\n\n\n";
      delay(duracion_pausas);
      std::cout<<"(1)Ver/Eliminar aliens desbloqueados o registrar\n\n";
      //Esta opcion tambien trabaja con un splay tree y un vector.
      delay(duracion_pausas);
      std::cout<<"(2)Amenaza detectada! (Transformacion guiada)\n\n";
      //La opcion dos trabaja con un queue y los sort.
      delay(duracion_pausas);
      std::cout<<"(3)Amenaza detectada! (Transformacion libre)\n\n";
      //La opcion 3 trabaja con un splay tree.
      delay(duracion_pausas);
      std::cout<<"(4)Apagar Omnitrix \n\n";
      //Finalizar el programa.
      delay(duracion_pausas);
      choice=input("Inserte un numero entero positivo, entre 1 y 4!\n",choice);
      std::cout<<"\n";

      if (choice != '1' && choice != '2' && choice != '3' && choice != '4'){
        std::cout<<"Opcion invalida! Por favor intentelo de nuevo.\n\n\n";

      }
      delay(duracion_pausas);
    }


    switch(choice){
      case '1':
      return seleccionVerEditar();
      //std::cout<<"Opcion1\n";

      break;
      case '2':
      return seleccionGuiada();
      //return false;
      //std::cout<<"Opcion2\n";

      break;
      case '3':
      return seleccionLibre();
      //return false;
      //std::cout<<"Opcion3\n";
      break;
      default:
      //std::cout<<"Opcion4\n";
      return false;
      break;
    }
    //Esta linea ya no se va a ejecutar.
    //std::cout<<"\n";
  }

  bool seleccionVerEditar(){
    char choice = 'a';

    std::cout<<"\nModo Ver/eliminar aliens seleccionados! (o registrar)\n\n\n";
    delay(duracion_pausas);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '4'
          && choice != '5' && choice != '6'){
      std::cout<<"Digite el numero que corresponda al modo de operacion "
      <<"deseado:\n\n\n";
      delay(duracion_pausas);
      std::cout<<"(1)Ver aliens desbloqueados\n\n";
      //Esta opcion tambien trabaja con un splay tree y un vector.
      delay(duracion_pausas);
      std::cout<<"(2)Ver aliens y estadisticas\n\n";
      //La opcion dos trabaja con un queue y los sort.
      delay(duracion_pausas);
      std::cout<<"(3)Ver informacion de un alien\n\n";
      //Muestra alien con sus estadisticas
      delay(duracion_pausas);
      std::cout<<"(4)Escanear alien \n\n";
      //Sirve para poder anadir un nuevo alien
      delay(duracion_pausas);
      std::cout<<"(5)Eliminar ADN peligroso\n\n";
      delay(duracion_pausas);
      //Sirve para volver dar la opcion de apagar o no.
      std::cout<<"(6)Cancelar\n\n";
      delay(duracion_pausas);
      choice = input("",choice);
      std::cout<<"\n";
      if (choice != '1' && choice != '2' && choice != '3' && choice != '4'
          && choice != '5' && choice != '6'){
        std::cout<<"Opcion invalida! Por favor intentelo de nuevo.\n\n\n";
      }
      delay(duracion_pausas);
    }

    switch(choice){
      case '1':
       mostrarNombresYNumero();
       return continuarSiNo();
      //std::cout<<"Opcion1\n";

      break;
      case '2':
      return mostrarCatalogo();
      //std::cout<<"Opcion2\n";

      break;
      case '3':

      return mostrarBaseNombre();
      //std::cout<<"Opcion3\n";
      break;
      case '4':
      return registrarAlien();
      break;
      case '5':
      return eliminarADN();
      break;
      default:
      std::cout<<"\nCancelando";

      for (int i = 0; i<3;i++){
        delay(duracion_pausas);
        std::cout<<".";
      }
      std::cout<<"\n\n\n";
      return continuarSiNo();
      break;
    }
  }

bool seleccionGuiada(){
  char choice = 'a';
  std::string criterio1,criterio2 ="";
  std::cout<<"\nModo de transformacion guiada!\n\n\n";
  while(choice != '1' && choice != '2' && choice != '3' && choice != '4'){
    std::cout<<"Digite el numero que corresponda al modo de operacion deseado:"
             <<"\n\n\n";
    delay(duracion_pausas);
    std::cout<<"(1)Transformacion en base a un parametro\n\n";
    //Ordenamiento con un parametro, luego queue.
    delay(duracion_pausas);
    std::cout<<"(2)Transformacion en base a dos parametros\n\n";
    //Ordenamiento en base a un criterio compuesto, luego queue.
    delay(duracion_pausas);
    std::cout<<"(3)Transformacion balanceada(Considera todas las stats del "
    <<"alien)\n\n";
    /*La opcion 3 usa el atributo total del alien, es basicamente lo mismo que
    la opcion 1 pero usando "total" en vez de un atributo seleccionado*/
    delay(duracion_pausas);
    std::cout<<"(4)Cancelar\n\n";
    //Finalizar el programa.
    delay(duracion_pausas);
    choice = input("Inserte un numero entero positivo, entre 1 y 4!\n",choice);
    std::cout<<"\n";

    if (choice != '1' && choice != '2' && choice != '3' && choice != '4'){
      std::cout<<"Opcion invalida! Por favor intentelo de nuevo.\n\n\n";

    }
    delay(duracion_pausas);
  }

  std::vector<std::string> atributos = {"velocidad","resistencia",
  "inteligencia","fuerza"};
  bool crit_valido = false;
  switch(choice){
    case '1':


    criterio1 = input("Ingresa el atributo que mas necesitas (fuerza, "
      "inteligencia, velocidad, resitencia):\n\n",criterio1);
    for(int i =0; i < atributos.size();i++){
      if(atributos[i] == criterio1){
        crit_valido = true;
        break;
      }
    }
    if(!crit_valido){
      std::cout<<"Criterio no valido, usando velocidad!\n\n\n";
      criterio1 = "velocidad";
    }
    std::cout<<"Criterio seleccionado: '"<<criterio1<<"'\n\n\n";
    criterio2 = criterio1;
    //std::vector<Alien> ordenados=sort(aliens_desordenados,criterio1);
    //La linea de arriba no se usaria universalmente?
    //Puede ser, pero tendria que adaptarse.
    //return continuarSiNo();
    //std::cout<<"Opcion1\n";

    break;
    case '2':
    //std::string criterio2;

    //crit_valido = false;
    criterio1 = input("\nIngresa el primer atributo a considerar (fuerza, "
      "inteligencia, velocidad, resitencia):\n\n",criterio1);
    for(int i =0; i < atributos.size();i++){
      if(atributos[i] == criterio1){
        crit_valido = true;
        break;
      }
    }
    std::cout<<"\n";
    if(!crit_valido){
      std::cout<<"Criterio no valido, usando 'velocidad' como criterio por "
      <<"defecto!\n\n";
      criterio1 = "velocidad";
    }

    std::cout<<"Primer criterio: '"<<criterio1<<"'\n\n\n";
    //Para eliminar en base al valor.
    for (int i = 0; i < atributos.size(); i++){
      if (atributos[i] == criterio1){
        atributos.erase(atributos.begin()+i);
        break;
      }
    }

    crit_valido = false;

    criterio2 = input("\nIngresa el segundo atributo a considerar (fuerza, "
      "inteligencia, velocidad, resitencia):\n\n",criterio2);
    for(int i =0; i < atributos.size();i++){
      if(atributos[i] == criterio2){
        crit_valido = true;
        break;
      }
    }
    if(!crit_valido){
      std::cout<<"Criterio no valido o repetido, usando '"<<atributos[0]
      <<"' como criterio por defecto!\n\n\n";
      criterio2 = atributos[0];
    }
    std::cout<<"Segundo criterio: '"<<criterio2<<"'\n\n\n";


    //std::vector<Alien> ordenados=sort(aliens_desordenados,criterio1,criterio2);
    //Considerar usar universalmente.

    break;
    case '3':
    //std::vector<Alien> ordenados=sort(aliens_desordenados,"total");
    criterio1 = "total";
    criterio2 = criterio1;
    std::cout<<"Considerando todos los atributos para elegir al mejor alien!"
    <<"\n\n\n";
    break;

    default:
    std::cout<<"\nCancelando";

    for (int i = 0; i<3;i++){
      delay(duracion_pausas);
      std::cout<<".";
    }
    std::cout<<"\n\n\n";
    return continuarSiNo();
    break;
  }

  for (int i = 0; i<3;i++){
    delay(duracion_pausas);
    std::cout<<".";
  }
  std::cout<<"\n\n\n";
  std::vector<Alien> aliens_desordenados = dispositivo.getAliensUnlocked();
  std::vector<int> vector_valores;
  //vector_valores se llena solo en la funcion de sort.
  //std::cout<<"\nBandera caso inteligencia\n";
  //std::cout<<criterio1<<"\n";
  orden.sort(aliens_desordenados,vector_valores,criterio1,criterio2);
  //std::cout<<"\nSegunda bandera caso inteligencia\n";
  //std::cout<<criterio1<<"\n";
  //Ahora desordenados esta ordenado.
  std::queue<Alien> ordenados_queue;
  for(int i =0; i< aliens_desordenados.size();i++){
    ordenados_queue.push(aliens_desordenados[i]);
    //mostrarAlien(aliens_desordenados[i]);
    //std::cout<<"\nValor compuesto: "<<vector_valores[i]<<"\n";
    //std::cout<<"\n";
  }

  bool peligro = true;
  char victoria;

  while(peligro){
    if(ordenados_queue.empty()==false){
      std::cout<<"Transformacion completada! Mostrando registro del alien en "
      <<"uso:\n";
      //Muestra el numero de usos contando el actual.
      ordenados_queue.front().sumarUso();
      dispositivo.registrarUso(ordenados_queue.front().getNombre());
      mostrarAlien(ordenados_queue.front());

      if (criterio1 != criterio2){
        std::cout<<"\nValor compuesto: "<<vector_valores[0]<<"\n";
      }
      std::cout<<"\n"<<"El enemigo ha sido vencido?\n";
      input(" Digite \'y\' o \'n\':\n",victoria);
      victoria = tolower(victoria);
    }
    if (victoria == 'y'){
      peligro = false;
      dispositivo.registrarVictoria(ordenados_queue.front().getNombre());
    }
    else if(ordenados_queue.empty() == false){
      std::cout<<"\nEl ADN de "<<ordenados_queue.front().getNombre()<<" necesita "
      "estabilizarse! Cambiando a proximo alien mas optimo";
      for (int i = 0; i<3;i++){
        delay(duracion_pausas);
        std::cout<<".";
      }
      std::cout<<"\n";
      ordenados_queue.pop();
      vector_valores.erase(vector_valores.begin());
    }
    else{
      std::cout<<"No quedan mas aliens!\n";
      std::cout<<"Activando protocolo de teletransportacion de emergencia en "
      "T-5 segundos...\n";
      for (int i = 5; i>0;i--){
        delay(duracion_pausas);
        std::cout<<i<<"\n";
      }
      for (int i = 0; i<3;i++){
        delay(duracion_pausas);
        std::cout<<"!";
      }

      peligro = false;
    }


  }
  std::cout<<"\nPortador fuera de peligro\n";
  std::cout<<"Finalizando modo de preservacion";
  for (int i = 0; i<3;i++){
    delay(duracion_pausas);
    std::cout<<".";
  }
  std::cout<<"\n\n\n";


  return continuarSiNo();




}

  bool continuarSiNo(){
    char eleccion = 'a';


    while(eleccion != 'y' && eleccion != 'n'){
      std::cout<<"Deseas apagar el Omnitrix? Escribe 'y' o 'n'\n\n";
      //terminar el programa o no
      eleccion = input("",eleccion);
      eleccion = std::tolower(eleccion);
      std::cout<<"\n\n";
      if(eleccion != 'y' && eleccion != 'n'){
        std::cout<<"Opcion invalida! Intente de nuevo.\n\n";
      }
      else if(eleccion == 'y'){
        return false;
        //no se quiere continuar
      }
      else{
        return true;
        //se quiere continuar
      }
    }
    return true;
  }

public:
  //Uso referencia en vez de puntero ya que nunca cambiare de objeto Omnitrix.
  Menu(Omnitrix& p_omnitrix, int length) : dispositivo (p_omnitrix),
  duracion_pausas(length){}
  void menuPrincipal() {
    std::cout<<"\nInicializando omnitrix, por favor espere";

    for (int i = 0; i<3;i++){
      delay(duracion_pausas);
      std::cout<<".";
    }

    std::cout<<"\nOmnitrix activado!\n\n\n";
    delay(duracion_pausas);
    while(seleccionPrincipal()){}

    std::cout<<"\nApagando omnitrix";

    for (int i = 0; i<3;i++){
      delay(duracion_pausas);
      std::cout<<".";
    }
    std::cout<<"\n\n";

  }

};
#endif
