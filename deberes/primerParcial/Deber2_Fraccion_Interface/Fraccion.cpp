/***********************************************************************
 * Module:  Fraccion.cpp
 * Author:  Edu
 * Modified: domingo, 4 de octubre de 2026 11:11:43
 * Purpose: Implementation of the class Fraccion
 ***********************************************************************/

#include "Fraccion.h"

float Fraccion::getDenominador(void)
{
   return denominador;
}

void Fraccion::setDenominador(float newDenominador)
{
   denominador = newDenominador;
}

float Fraccion::getNumerador(void)
{
   return numerador;
}

void Fraccion::setNumerador(float newNumerador)
{
   numerador = newNumerador;
}