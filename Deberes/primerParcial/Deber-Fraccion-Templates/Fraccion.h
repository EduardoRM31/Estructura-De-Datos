/***********************************************************************
 * Module:  Fraccion.h
 * Author:  Edu
 * Modified: domingo, 4 de octubre de 2026 11:11:43
 * Purpose: Declaration of the class Fraccion
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Fraccion_h)
#define __Class_Diagram_1_Fraccion_h

template<typename T>
class Fraccion {
   public:
   Fraccion();
   Fraccion(T numerador, T denominador);
   ~Fraccion();

   T getNumerador(void);
   T setNumerador(T newNumerador);

   T getDenominador(void);
   T setDenominador(T newDenominador);

   protected:
   private:
   T numerador;
   T denominador;
};

template<typename T>
Fraccion<T>::Fraccion(){
   numerador = 0;
   denominador = 1;
}

template<typename T>
Fraccion<T>::Fraccion(T numerador, T denominador){
   this->numerador = numerador;
   this->denominador = denominador;
}

template<typename T>
Fraccion<T>::~Fraccion(){
}

template<typename T>
T Fraccion<T>::getNumerador(void){
   return numerador;
}

template<typename T>
T Fraccion<T>::setNumerador(T newNumerador){
   numerador = newNumerador;
}

template<typename T>
T Fraccion<T>::getDenominador(void){
   return denominador;
}

template<typename T>
T Fraccion<T>::setDenominador(T newDenominador){
   denominador = newDenominador;
}

#endif