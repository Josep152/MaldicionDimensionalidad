#include <iostream>	//cout
#include <vector>	//vector
#include <stdlib.h>	//random
#include <time.h> 	//time
#include <math.h> 	//pow
#include <map>  	//map
#include <fstream>  //files

using namespace std;

#define dim 1000

constexpr int FLOAT_MIN = 0;         //Rango minimo de los numero aleatorios
constexpr int FLOAT_MAX = 1;		 //Rango maximo de los numero aleatorios

template <class T>
struct Point {						 //Estructura que nos ayudara a manejar mejor los puntos
	vector<T> my_v;
	Point () {						 //Cosntructor para numeros aleatorios
		for (int i = 0; i < dim; i++) {
			T r = FLOAT_MIN + (T)(rand()) / ((T)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
			my_v.push_back(r);
		}
	}
	//Operators
	Point operator + (Point<T> n) {
		Point<T> rpta;
		for (int i = 0; i < dim; i++) {
			rpta.my_v[i] = my_v[i] + n.my_v[i];
		}
		return rpta;
	}
	void operator = (Point<T> n) {
		for (int i = 0; i < dim; i++) {
			my_v[i] = n.my_v[i];
		}
	}

	//Functions
	void print_p () {
		for (int i = 0; i < dim; i++) {
			cout << my_v[i] << ' ';
		}
		cout << endl;
	}
};

template <class T>
class DistanciaEu {				//Functor para la distancia
public:
	T operator() (Point<T> a, Point<T> b) {
		T rpta = 0;
		for (int i = 0; i < dim; i++) {
			rpta += pow(a.my_v[i] - b.my_v[i],2);
		}
		return sqrt(rpta);
	}
};

int main() {
	srand(time(0));
	
	int cant_datos = 100;			//Cantidad de datos a experimentar
	DistanciaEu<float> dis;			//Creamos el functor de distancia
	map<float, int> counter;		//Map donde almacenaremos las distancias
	
	vector<Point<float>> all_p (cant_datos);	//Creamos el vector de Points
	for (int i = 0; i < cant_datos; i++) {		//Sacamos la distancia entre los puntos
		for (int j = i+1; j < cant_datos; j++) {
			counter[dis(all_p[i],all_p[j])]++;
		}
	}

    ofstream file;            		//Abrimos un file, donde almacenaremos el map
    string nombre = "1000_Dim100Elem";
    string direccion = "D://Programacion//EDA//Thisone//Maldicion//";
    direccion.append(nombre);
    direccion.append(".csv");
    file.open(direccion, ios::out);

    for (auto i : counter) {
        file << i.first << "," << i.second << ",\n";
    }
    file.close();   //Se cierra el file

	return 0;
}