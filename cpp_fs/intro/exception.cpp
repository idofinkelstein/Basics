#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;

struct BadDog: public runtime_error
{
    BadDog(const string& s = "This is a bad dog"): runtime_error(s) {}
};

/*---------------------------------------------------------------------------*/

void Fifi()
{
    throw BadDog("bad pup"); 
    cerr << "Fifi() after throw" << endl;
}

/*---------------------------------------------------------------------------*/

void Foo()
{
    // X x1
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

/*---------------------------------------------------------------------------*/

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

/****************************************************************************/

int main()
{
    try
    {
        Bar();
    }

    catch (bad_alloc&)
    {
        cerr << "Out of memory! exiting."; 
        exit (2);
    }
/*
    catch(BadDog& b)
    {
        cerr << "Bad dog exception: " << b.what();
        exit(3);
    }
*/
    catch(exception& r)
    {
        cerr << "unknown exception: " << r.what();
        exit(4);
    }

    return (0);
}