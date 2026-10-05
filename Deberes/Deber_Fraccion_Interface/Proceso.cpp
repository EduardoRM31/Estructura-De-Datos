/***********************************************************************
 * Module:  Proceso.cpp
 * Author:  Edu
 * Modified: domingo, 4 de octubre de 2026 10:57:55
 * Purpose: Implementation of the class Proceso
 ***********************************************************************/

#include "Proceso.h"

////////////////////////////////////////////////////////////////////////
// Name:       Proceso::sumar(Fraccion f1, Fraccion f2)
// Purpose:    Implementation of Proceso::sumar()
// Parameters:
// - f1
// - f2
// Return:     Fraccion
////////////////////////////////////////////////////////////////////////

Fraccion Proceso::sumar(Fraccion f1, Fraccion f2)
{
   Fraccion r;
   
   r.setNumerador(f1.getNumerador() * f2.getDenominador() + f2.getNumerador() * f1.getDenominador());
   r.setDenominador(f1.getDenominador() * f2.getDenominador());
   
   return r;
}