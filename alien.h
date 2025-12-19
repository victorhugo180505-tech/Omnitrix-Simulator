#include <string>
#ifndef ALIEN_H
#define ALIEN_H

class Alien {

private:
  int inteligencia, fuerza, velocidad, resistencia,total,batallas_ganadas,
      veces_usado,veces_elegido;
  std::string nombre;

public:
  Alien() : nombre(""), inteligencia(0), fuerza(0), velocidad(0),
  resistencia(0),total(0),batallas_ganadas(0),veces_usado(0),veces_elegido(0){}
  Alien(std::string name,int iq, int power, int speed, int endurance,
    int times_used, int times_choosen, int battles_won){
      int min, max;
      min = 1;
      max = 20;
      nombre = name;

      if (iq  < min){
        inteligencia = min;
      }
      else if(iq > max){
        inteligencia = max;
      }
      else{
        inteligencia = iq;
      }

      if (power  < min){
        fuerza = min;
      }
      else if(power > max){
        fuerza = max;
      }
      else{
        fuerza = power;
      }

      if (speed  < min){
        velocidad = min;
      }
      else if(speed > max){
        velocidad = max;
      }
      else{
        velocidad = speed;
      }

      if (endurance  < min){
        resistencia = min;
      }
      else if(endurance > max){
        resistencia = max;
      }
      else{
        resistencia = endurance;
      }
      total = inteligencia+fuerza+velocidad+resistencia;

    if (battles_won > times_used){
      batallas_ganadas = times_used;
    }
    else {
      batallas_ganadas = battles_won;

    }
    if (times_choosen>times_used){
      veces_elegido = times_used;
    }
    else{
      veces_elegido = times_choosen;
    }
    veces_usado = times_used;
  }
    Alien(std::string name,int iq, int power, int speed, int endurance){
      int min, max;
      min = 1;
      max = 20;
      nombre = name;

      if (iq  < min){
        inteligencia = min;
      }
      else if(iq > max){
        inteligencia = max;
      }
      else{
        inteligencia = iq;
      }

      if (power  < min){
        fuerza = min;
      }
      else if(power > max){
        fuerza = max;
      }
      else{
        fuerza = power;
      }

      if (speed  < min){
        velocidad = min;
      }
      else if(speed > max){
        velocidad = max;
      }
      else{
        velocidad = speed;
      }

      if (endurance  < min){
        resistencia = min;
      }
      else if(endurance > max){
        resistencia = max;
      }
      else{
        resistencia = endurance;
      }
      total = inteligencia+fuerza+velocidad+resistencia;
      veces_elegido = 0;
      veces_usado = 0;
      batallas_ganadas = 0;

  }

  std::string getNombre (){
    return nombre;
  }
  int getInteligencia(){
   return inteligencia;
  }

  int getFuerza(){
    return fuerza;
  }
  int getVelocidad(){
    return velocidad;
  }

  int getResistencia(){
    return resistencia;
  }
  int getTotal(){
    return total;
  }
  int getBatallasGanadas(){
    return batallas_ganadas;
  }

  int getVecesUsado(){
    return veces_usado;
  }
  int getVecesElegido(){
    return veces_elegido;
  }
  void sumarUso(){
    veces_usado += 1;
  }
  void sumarEleccion(){
    veces_elegido += 1;
  }
  void sumarVictoria(){
    batallas_ganadas+=1;
  }

};
#endif
