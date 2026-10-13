#ifndef SUMATEMPLATES.h
#define SUMATEMPLAES.h

template<typename T>
class SumaT {
   public:
   SumaT(T num1, T num2);
   void sumar(T n1, T n2);
   ~SumaT();

   protected:
   private:
   T num1;
   T num2;
};

template<typename T>
SumaT<T>::SumaT(T n1, T n2){
   num1 = n1;
   num2 = n2;
}

template<typename T>
void sumaT<T>::sumar(T n1, T n2) {
    std::cout << "La suma es: " << n1 + n2;
}

template<typename T>
sumaT<T>::~sumaT() {}

#endif