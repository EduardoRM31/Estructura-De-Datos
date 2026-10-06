/***********************************************************************
 * Module:  Proceso.h
 * Author:  Edu
 * Modified: domingo, 4 de octubre de 2026 10:57:55
 * Purpose: Declaration of the class Proceso
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Proceso_h)
#define __Class_Diagram_1_Proceso_h

#include "Fraccion.h"
#include "IProceso.h"

template<typename T>
class Proceso : public IProceso<T> {
   public:
   Proceso();
   ~Proceso();
   Fraccion<T> sumar(Fraccion<T> f1, Fraccion<T> f2);

   private:
   protected:
};

template<typename T>
Proceso<T>::Proceso(){
}

template<typename T>
Proceso<T>::~Proceso(){
}

template<typename T>
Fraccion<T> Proceso<T>::sumar(Fraccion<T> f1, Fraccion<T> f2) {
   Fraccion<T> r;

   r.setNumerador(f1.getNumerador() * f2.getDenominador() + f2.getNumerador() * f1.getDenominador());
   r.setDenominador(f1.getDenominador() * f2.getDenominador());
   
   return r;
}

#endif