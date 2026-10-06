/***********************************************************************
 * Module:  Proceso.h
 * Author:  Edu
 * Modified: domingo, 4 de octubre de 2026 10:57:55
 * Purpose: Declaration of the class Proceso
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Proceso_h)
#define __Class_Diagram_1_Proceso_h

#include "IProceso.h"
#include "Fraccion.h"

class Proceso : public IProceso
{
public:
   Fraccion sumar(Fraccion f1, Fraccion f2);

protected:
private:

};

#endif