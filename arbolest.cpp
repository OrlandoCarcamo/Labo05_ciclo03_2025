#include <iostream>
using namespace std;


struct Estudiante {
 int carnet;
 char nombre[50];
 float nota;
 Estudiante* izquierdo;
 Estudiante* derecho;
};

Estudiante* crearEstudiante(int carnet, char nom[], float nota) {
 Estudiante* nuevo = new Estudiante();
 nuevo->carnet = carnet;
 nuevo->nota = nota;
 nuevo->izquierdo = NULL;
 nuevo->derecho = NULL;

 // Copiar el nombre
 int i = 0;
 while(nom[i] != '\0' && i < 49) {


 nuevo->nombre[i] = nom[i];
 i++;
 }
 nuevo->nombre[i] = '\0';

 return nuevo;
}

Estudiante* insertar(Estudiante* raiz, int carnet, char nombre[], float nota) {

    if(raiz == NULL)
        return crearEstudiante(carnet, nombre, nota);

    if(carnet < raiz->carnet)
        raiz->izquierdo = insertar(raiz->izquierdo, carnet, nombre, nota);

    else if(carnet > raiz->carnet)
        raiz->derecho = insertar(raiz->derecho, carnet, nombre, nota);

    return raiz;


}

void mostrarEstudiantes(Estudiante* raiz) {
    if (raiz != NULL) {
        mostrarEstudiantes(raiz->izquierdo);
        cout << "Carnet: " << raiz->carnet 
             << " | Nombre: " << raiz->nombre 
             << " | Nota: " << raiz->nota << endl;
        mostrarEstudiantes(raiz->derecho);
    }

}
void mostrarAprobados(Estudiante* raiz) {
    if (raiz != NULL) {
        mostrarAprobados(raiz->izquierdo);

        if (raiz->nota >= 6.0) {
            cout << raiz->nombre << " (" << raiz->nota << ")\n";
        }

        mostrarAprobados(raiz->derecho);
    }
}

///prueba
//ok

void mostrarReprobados(Estudiante* raiz) {
    if (raiz != NULL) {
        mostrarReprobados(raiz->izquierdo);

        if (raiz->nota < 6.0) {
            cout << raiz->nombre << " (" << raiz->nota << ")\n";
        }

        mostrarReprobados(raiz->derecho);
    }
}













void buscarEstudiante(Estudiante* raiz, int carnet) {

   if(!raiz){
printf("El dato buscado NO está en el árbol");
}

    if(carnet == raiz->carnet){
        cout << "Encontrado:\n";
        cout << raiz->nombre << " - Nota: " << raiz->nota << endl;
    }
    else if(carnet < raiz->carnet)
        buscarEstudiante(raiz->izquierdo, carnet);
    else
        buscarEstudiante(raiz->derecho, carnet);
}






float calcularPromedio(Estudiante* raiz, int* contador) {
    if (raiz == NULL) return 0;

    float suma = 0;

    suma += calcularPromedio(raiz->izquierdo, contador);

    suma += raiz->nota;
    (*contador)++;

    suma += calcularPromedio(raiz->derecho, contador);

    return suma;
}