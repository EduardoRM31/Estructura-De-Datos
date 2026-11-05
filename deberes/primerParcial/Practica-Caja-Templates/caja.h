#ifndef CAJATEMPLATES_H
#define CAJATEMPLATES_H

template<typename T>
class Caja{
    private:
    T valor;

    protected:
    public:
    Caja();
    Caja(T valor);
    ~Caja();

    T getValor(void);
    void setValor(T newValor);
    void mostrar(void);
};

template<typename T>
Caja<T>::Caja() : valor(){
}

template<typename T>
Caja<T>::Caja(T valor){
    this->valor = valor;
}

template<typename T>
Caja<T>::~Caja(){
}

template<typename T>
T Caja<T>::getValor(void){
    return valor;
}

template<typename T>
void Caja<T>::setValor(T newValor){
    valor = newValor;
}

template<typename T>
void Caja<T>::mostrar(void){
    std::cout<< valor << std::endl;
}

#endif