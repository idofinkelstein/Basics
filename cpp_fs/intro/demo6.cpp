#include <stdio.h>

void Foo() {}
void Foo(int i) {++i;}
void Foo(char c){c += 'j';}

int main()
{
	unsigned char h = 'h';

	Foo();
	Foo(6);
	Foo('h');

	Foo(NULL);
	Foo(6.5);
	Foo(h);

	return 0;
}
