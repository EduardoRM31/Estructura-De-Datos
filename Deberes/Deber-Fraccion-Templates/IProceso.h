/***********************************************************************
 * Module:  IProceso.h
 * Author:  Edu
 * Modified: domingo, 4 de octubre de 2026 11:08:50
 * Purpose: Declaration of the class IProceso
 ***********************************************************************/

#if !defined(__Class_Diagram_1_IProceso_h)
#define __Class_Diagram_1_IProceso_h

#include "Fraccion.h"

template<typename T>
class IProceso {
   public:
   virtual Fraccion<T> sumar(Fraccion<T> f1, Fraccion<T> f2)=0;
   
   private:
   protected:
};

#endif