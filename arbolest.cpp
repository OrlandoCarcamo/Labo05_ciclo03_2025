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





Estudiante* encontrarMejorNota(Estudiante* raiz) {

    if(!raiz) return NULL;

    Estudiante* mejor = raiz;

    Estudiante* izq = encontrarMejorNota(raiz->izquierdo);
    Estudiante* der = encontrarMejorNota(raiz->derecho);

    if(izq && izq->nota > mejor->nota) mejor = izq;
    if(der && der->nota > mejor->nota) mejor = der;

    return mejor;
}

int main() {
 Estudiante* sistema = NULL;
 int opcion;
 int carnet;
char nombre[50];
 float nota;

 do {
 cout << "\n===== SISTEMA DE GESTION DE ESTUDIANTES=====\n";
 cout << "1. Agregar estudiante\n";
 cout << "2. Mostrar todos los estudiantes\n";
 cout << "3. Buscar estudiante por carnet\n";
 cout << "4. Mostrar estudiantes aprobados\n";
 cout << "5. Mostrar estudiantes reprobados\n";
 cout << "6. Calcular promedio general\n";
 cout << "7. Mostrar estudiante con mejor nota\n";
 cout << "8. Salir\n";
 cout << "Opcion: ";
 cin >> opcion;

 switch (opcion)
 {
 case 1: 
        cout << "Carnet: ";
        cin >> carnet;

        cout << "Nombre: ";
        cin >> nombre;

        cout << "Nota: ";
        cin >> nota;

        sistema = insertar(sistema, carnet, nombre, nota);
    break;

case 2: mostrarEstudiantes(sistema);
    break;


case 3:{  
        cout << "Carnet a buscar: ";
        cin >> carnet;
        buscarEstudiante(sistema, carnet);
    break;
        }

case 4:
        mostrarAprobados(sistema);
    break;

case 5:
        mostrarReprobados(sistema);
    break;

case 6:{
        int contador = 0;
        float suma = calcularPromedio(sistema, &contador);

        if(contador > 0)
        cout << "Promedio: " << suma/contador << endl;
        else
        cout << "Sin datos\n";
    break;
        }

        case 7:{
            Estudiante* mejor = encontrarMejorNota(sistema);
            if(mejor)
                cout << mejor->nombre << ": " << mejor->nota << endl;
            break;
        }

        }



 } while(opcion != 8);

 return 0;
}
