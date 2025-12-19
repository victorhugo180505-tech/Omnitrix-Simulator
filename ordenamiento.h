#include <vector>
#include "alien.h"
#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H



class Ordenamiento{
private:

  void swap(int a, int b, std::vector<Alien>& source){

    //Intercambiamos los aliens.
    Alien auxAlien = source[a];
    source[a] = source[b];
    source[b] = auxAlien;
  }
  void swap(int a, int b, std::vector<int>& source){

    //Intercambiamos los aliens.
    int auxAlien = source[a];
    source[a] = source[b];
    source[b] = auxAlien;
  }

  void insertionSort(std::vector<Alien>& source, std::vector<int>& ref){

    for(int i = 1; i<source.size();i++){
      for(int j = i; j>0 && ((ref[j])>(ref[j-1])); j--){
      swap(j,j-1,source);
      swap(j,j-1,ref);
      }
    }
  }
//////////////////////////////////////////
  int calcularValor(Alien& alien, const std::string stat1,
                    const std::string stat2){

    //int valor1 = 0, valor2 = 0;
    auto metodo1 = getPCriterio(stat1);
    auto metodo2 = getPCriterio(stat2);
    if(stat1 == stat2){
      return (alien.*metodo1)();
    }
    else{
      return ((alien.*metodo1)() + (alien.*metodo2)());
    }

  }

int (Alien::*getPCriterio(const std::string& atributo))(){
  int (Alien::*getStat)() = nullptr;
  if(atributo =="inteligencia"){
    getStat = &Alien::getInteligencia;
  }
  else if(atributo == "fuerza"){
    getStat = &Alien::getFuerza;
  }
  else if(atributo == "velocidad"){
    getStat = &Alien::getVelocidad;
  }
  else if(atributo == "resistencia"){
    getStat = &Alien::getResistencia;
  }
  else if(atributo=="total"){
    getStat = &Alien::getTotal;
  }
  return getStat;

}


void mergeArray(std::vector<Alien>& aliens, std::vector<Alien>& aliens_tmp,
  std::vector<int>& valores, std::vector<int>& valores_tmp, int low,
  int mid,int high) {
	//int ind_menor;
	int i,j,k;
	i = low;
	j = mid+1;
	k = low;
	//k se usa para llevar el control de que indice voy a llenar en los tmp
	while (i<= mid && j <= high){
		if(valores[i]>valores[j]){

      valores_tmp[k] = valores[i];
      aliens_tmp[k] = aliens[i];
			i++;


		}
		else {
			valores_tmp[k] = valores[j];
      aliens_tmp[k] = aliens[j];
			j++;

			//Lo mismo se aplica con esta j.
		}

		k++;
	}
	if (i > mid){
		for (;j<=high;j++){
			valores_tmp[k] = valores[j];
      aliens_tmp[k] = aliens[j];
			k++;
			//Pongo el k++ aqui para no hacerme bolas.
		}
	}
	else {
		for (;i<=mid;i++){
			valores_tmp[k] = valores[i];
      aliens_tmp[k] = aliens[i];
			k++;
		}
	}


	}






void mergeSplit(std::vector<Alien>& aliens, std::vector<Alien>& aliens_tmp,
  std::vector<int>& valores, std::vector<int>& valores_tmp, int low, int high)
{
	int mid;
	if (high > low){
    //Antes era un !=
		//El caso base es cuando solo tengamos un elemento.

		mid = (high+low)/2;
		//Divido favoreciendo al lado izquierdo.
		mergeSplit(aliens,aliens_tmp,valores,valores_tmp,low,mid);
		//Llamada recursiva que divide a la izquierda.
		mergeSplit(aliens,aliens_tmp,valores,valores_tmp,mid+1,high);
		//Hacia la derecha.
		mergeArray(aliens,aliens_tmp,valores,valores_tmp,low,mid,high);
    //Aqui copio los valores a los vectores principales.
    for(int i = low; i<= high;i++){
      aliens[i] = aliens_tmp[i];
      valores[i] = valores_tmp[i];
    }
		//copyArray(A,B,low,high);
	}
	//Fin de la ejecucion debido a que este mergeSplit es void.
}


void mergeSort(std::vector<Alien>& source, std::vector<int>& ref) {
	std::vector<Alien> tmp_aliens(source.size());
  std::vector<int> tmp_ref(ref.size());
	mergeSplit(source,tmp_aliens,ref,tmp_ref,0,source.size()-1);


}



public:
  void sort(std::vector<Alien>& aliens, std::vector<int>& valores,
  const std::string& atributo1, const std::string& atributo2){

    int num_elementos = aliens.size();
    for(int i = 0; i<num_elementos;i++){
      valores.push_back(calcularValor(aliens[i],atributo1,atributo2));
    }
    
    //std::cout<<"\nBandera inteligencia en sort\n";
    if( num_elementos<= 0){

      std::cout<<"Error! No hay aliens disponibles...\n";
    }
    //El numero original aqui es 15, pero pondre 100 para probarlo
    else if(num_elementos <= 20){
      std::cout<<"\n\nOrdenamiento con insertionSort\n\n";
      insertionSort(aliens,valores);


    }
    else{
      std::cout<<"\n\nOrdenamiento con mergeSort\n\n";
      mergeSort(aliens,valores);

    }


  }









};

#endif
