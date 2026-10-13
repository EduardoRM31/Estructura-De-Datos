#include <iostream>

using namespace std;

template<typename T>

T suma(T a, T b){
    return a + b;
}

int main(){
    cout<<"La suma es: "<< suma(6, 4);
    cout<<"La suma de flotantes es: "<< suma(4.9f, 2.5f)<<endl;
    cout<<"La suma de flotantes es: "<< suma(2.5, 3.5)<<endl;
}