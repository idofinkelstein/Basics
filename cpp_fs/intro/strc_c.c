struct x
{
	int a;
	const int b;
};

int main ()
{
	const struct x x1 = { 5, 2 };

	/*x1.a = 5;
	x1.b = 3;*/

	const struct x *px = &x1;

	return 0;

}
