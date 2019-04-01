#include <boost/numeric/ublas/vector.hpp>//������
#include <boost/numeric/ublas/matrix.hpp>//�������
#include <boost/numeric/ublas/io.hpp>//���������� operator<<(����� �� �����)
#include <boost/random.hpp>//��������� ��������� �����
#include <iostream>
#include <cstdint>
#include <boost/lexical_cast.hpp>
#include <cstdlib>// comment
using namespace boost::numeric::ublas;
typedef boost::mt19937 BaseGenerator;//��� ����������/
typedef boost::uniform_real<double> Distribution;//�������� ���������
typedef boost::variate_generator<BaseGenerator, Distribution> Generator;
//��������� ��������� �����
double boostDoubleRand(int first, int last) {
	static BaseGenerator base;
	static Distribution dist(first, last);
	static Generator rng(base, dist);
	return rng();
}
//�������� ������� � ��������� ���������
matrix<double> CreateMatrix(int a, int p, int f, int l)
{
	matrix<double> A(a, p);
	for (int j = 0;j < a;j++)
	{
		for (int o = 0;o < p;o++)
		{
			//����� ������� ��� ��������� ������ �������� �������
			A(j, o) = boostDoubleRand(f, l);
		}
	}
	return A;
}
//����� ������� �� �����
void ShowMatrix(matrix<double> A)
{
	for (int i = 0; i < A.size1(); i++)
	{
		//���� �� ���������� i, � ������� ���������� ������ �������
		for (int j = 0; j < A.size2(); j++)
			std::cout << A(i, j) << "\t"; //����� ���������� �������� �������
		std::cout << std::endl; //������� �� ����� ������ ����� ������ ���� ��������� ������
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "������� ����� �������: " << std::endl;
	int a, u;
	std::cin >> a;
	//�������� ������ �������
	vector<double> x(a);
	//������������ ������ �������� �������
	for (int i = 0;i < a;i++)
	{
		std::cout << "������� " << i + 1 << "� " << " �������: " << std::endl;
		std::cin >> u;
		x(i) = u;
	}
	//����� ������� �� �����
	std::cout << "��� ������:" << x << std::endl;
	std::cout << "������� ���������� ����� � �������" << std::endl;
	int p;
	std::cin >> p;
	int first, last, f, l;
	std::cout << "������� �������� ��������� ����� ��� �������:" << std::endl;
	std::cout << "����� �������:" << std::endl;
	std::cin >> first;
	std::cout << "������ �������:" << std::endl;
	std::cin >> last;
	if (first >= last)
	{
		std::cout << "������ ��������� ����� ���� ������ �����. ������� ������ �� 0 �� 10." << std::endl;
		f = 0;
		l = 10;
	}
	else
	{
		f = first;
		l = last;
	}
	//�������� ������� � ��������� ���������
	matrix<double> A = CreateMatrix(a, p, f, l);
	//����� ������� �� �����
	std::cout << "���� �������:" << std::endl;
	ShowMatrix(A);
	//��������� ������� �� �������: y = xA
	vector<double> y = prod(x, A);
	//����� ���������� �� �����
	std::cout << "��������� ��������� ������� �� �������: " << y << std::endl;
	matrix<double> B = CreateMatrix(a, p, f, l);
	matrix<double> C = CreateMatrix(p, a, f, l);
	std::cout << "������a B" << std::endl;
	ShowMatrix(B);
	std::cout << "������a C" << std::endl;
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
	std::cout << "���������������� A" << std::endl;
	ShowMatrix(M);
	//��������� �������� ������� (�������� ������������ ��������� �����������)
	A.resize(2, 2);
	std::cout << "��������� �������� ������� A" << std::endl;
	ShowMatrix(A);
	system("pause");
	return 0;
}