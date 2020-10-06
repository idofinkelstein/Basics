#include <iostream>
using namespace std;

int main()
{
	int i = 8;
	int &ip = i;
	
	ip = 9;

	cout << &i << endl;
	cout << &ip << endl;
}
