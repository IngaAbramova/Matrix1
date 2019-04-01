#include <boost/numeric/ublas/vector.hpp>//вектор
#include <boost/numeric/ublas/matrix.hpp>//матрица
#include <boost/numeric/ublas/io.hpp>//определяет operator<<(вывод на экран)
#include <boost/random.hpp>//генератор рандомных чисел
#include <iostream>
#include <cstdint>
#include <boost/lexical_cast.hpp>
#include <cstdlib>// comment
using namespace boost::numeric::ublas;
typedef boost::mt19937 BaseGenerator;//тип генератора/
typedef boost::uniform_real<double> Distribution;//указание диапазона
typedef boost::variate_generator<BaseGenerator, Distribution> Generator;
//Генератор случайных чисел
double boostDoubleRand(int first, int last) {
	static BaseGenerator base;
	static Distribution dist(first, last);
	static Generator rng(base, dist);
	return rng();
}
//Создание матрицы с заданными размерами
matrix<double> CreateMatrix(int a, int p, int f, int l)
{
	matrix<double> A(a, p);
	for (int j = 0;j < a;j++)
	{
		for (int o = 0;o < p;o++)
		{
			//Вызов функции для генерации нового элемента матрицы
			A(j, o) = boostDoubleRand(f, l);
		}
	}
	return A;
}
//Вывод матрицы на экран
void ShowMatrix(matrix<double> A)
{
	for (int i = 0; i < A.size1(); i++)
	{
		//Цикл по переменной i, в котором перебираем строки матрицы
		for (int j = 0; j < A.size2(); j++)
			std::cout << A(i, j) << "\t"; //вывод очередного элемента матрицы
		std::cout << std::endl; //переход на новую строку после вывода всех элементов строки
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите длину вектора: " << std::endl;
	int a, u;
	std::cin >> a;
	//Создание нового вектора
	vector<double> x(a);
	//Пользователь вводит злементы вектора
	for (int i = 0;i < a;i++)
	{
		std::cout << "Введите " << i + 1 << "й " << " элемент: " << std::endl;
		std::cin >> u;
		x(i) = u;
	}
	//Вывод вектора на экран
	std::cout << "Ваш вектор:" << x << std::endl;
	std::cout << "Укажите количество строк в матрице" << std::endl;
	int p;
	std::cin >> p;
	int first, last, f, l;
	std::cout << "Укажите диапазон рандомных чисел для матрицы:" << std::endl;
	std::cout << "Левая граница:" << std::endl;
	std::cin >> first;
	std::cout << "Правая граница:" << std::endl;
	std::cin >> last;
	if (first >= last)
	{
		std::cout << "Правая границане может быть меньше левой. Выбраны гранцы от 0 до 10." << std::endl;
		f = 0;
		l = 10;
	}
	else
	{
		f = first;
		l = last;
	}
	//Создание матрицы с заданными размерами
	matrix<double> A = CreateMatrix(a, p, f, l);
	//Вывод матрицы на экран
	std::cout << "Ваша матрица:" << std::endl;
	ShowMatrix(A);
	//Умножение вектора на матрицу: y = xA
	vector<double> y = prod(x, A);
	//Вывод результата на экран
	std::cout << "Результат умножения вектора на матрицу: " << y << std::endl;
	matrix<double> B = CreateMatrix(a, p, f, l);
	matrix<double> C = CreateMatrix(p, a, f, l);
	std::cout << "Матрицa B" << std::endl;
	ShowMatrix(B);
	std::cout << "Матрицa C" << std::endl;
	ShowMatrix(C);
	matrix<double> Q = A + B;
	std::cout << "A+B" << std::endl;
	ShowMatrix(Q);
	matrix<double> R = A - B;
	std::cout << "A-B" << std::endl;
	ShowMatrix(R);
	matrix<double> D = prod(A, C);
	std::cout << "A*C" << std::endl;
	ShowMatrix(D);
	matrix<double> M = trans(A);
	std::cout << "Транспонирование A" << std::endl;
	ShowMatrix(M);
	//Изменение размеров матрицы (значение существующих элементов сохраняются)
	A.resize(2, 2);
	std::cout << "Изменение размеров матрицы A" << std::endl;
	ShowMatrix(A);
	system("pause");
	return 0;
}