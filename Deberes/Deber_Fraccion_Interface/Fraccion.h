/***********************************************************************
 * Module:  Fraccion.h
 * Author:  Edu
 * Modified: domingo, 4 de octubre de 2026 11:11:43
 * Purpose: Declaration of the class Fraccion
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Fraccion_h)
#define __Class_Diagram_1_Fraccion_h

class Fraccion {
public:
   float getDenominador(void);
   void setDenominador(float newDenominador);
   float getNumerador(void);
   void setNumerador(float newNumerador);

protected:
private:
   float numerador;
   float denominador;
};

#endif