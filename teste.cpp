//Programa básica de c++

#include <iostream>

using namespace std;

int main() {

    cout << "Hello World." << endl; //"Menor=<<" "Maior=>>"

// Adição de números
// cout << 3 + 3 << endl;
// Subtraçáo de números
// cout << 3 - 3 << endl;
// Multiplicação de números
// cout << 3 * 3 << endl;
// Divisão de números 
// cout << 5 / 3 << endl;
// Resto da divisão
// cout << 5 % 3 << endl;

// Variáveis sempre minúsculas ou camel, nunca deve começar por um número

int qntLivros = 5;
int x, y, z;
x = 25;
cout << qntLivros * 2 << endl;
cout << qntLivros + 5 << endl;
cout << qntLivros - 2 << endl;

bool isTrue = false;
bool isHigh;
isHigh = true;

float altura = 1,75;
float peso;
peso= 34.6;

double altura2 = 1.75;
double peso2;
peso2 = 34.6;

char letra = 'a'; 
char letra2;
letra2 = 'b';

string nome = "Lucas";
string sobrenome;
sobrenome = "santos";

cout << "Nome." << nome << " " << sobrenome << endl;

// 2 * pi * r
const int float PI = 3.1416; // constantes não podem ser mudades no valor e são sempre maiúsculas // A palavra "float" ou "double" pode ser usado, significa a mesma coisa
const int X = 2; 

float int valor;

cout << "indique o valor do raio: ";
cin >> valor;
cout << x * PI * valor << endl;







 
 
 return 0;
}

