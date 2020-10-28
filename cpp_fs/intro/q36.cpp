#include <iostream>
using namespace std;

class X
{
public:
	X(){cout << "X: " << this << endl;}
	/*virtual*/ ~X() {cout << "~X: " << this << endl;}

private:
	double m_a;
};

class Y: public X
{
public:
	Y(){cout << "Y: " << this << endl;}
	~Y() {cout << "~Y: " << this << endl;}

private:
	int m_b;
};

int main()
{
	X *xp = new Y[5];

	delete[] xp;

	return 0;
}
