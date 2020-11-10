#include <new>
#include <cstring>
#include <cstdio>

class Widget
{
public:
    explicit Widget(const char *str = "I am a Widget");
    Widget(const Widget &other);
    void operator=(Widget other);
    void operator=(Widget(*other)());
    ~Widget();

    char* operator[](size_t index);
    operator const char*();

private:
    char* m_str;
};

Widget::Widget(const char *str) : m_str(strcpy(new char[strlen(str)], str))
{
}

Widget::Widget(const Widget &other)
{
    new (this) Widget(other); // רקורסיה אין סופית
}

void Widget::operator=(Widget other)
{
    char *str = m_str;
    m_str = other.m_str;
    other.m_str = str;
}

void Widget::operator=(Widget(*other)())
{
    other();
}

Widget::~Widget()
{
    delete m_str;
}

char* Widget::operator[](size_t index)
{
    return &m_str[index];
}

Widget::operator const char*()
{
    return m_str;
}


int main()
{
    Widget *x1 = new Widget();
    Widget x2(); // function declaration
    Widget x3("Don't worry, be happy");

    putchar(x3[2]); // x3[2] returns char*

    *x1 = *x1;
    *x1 = x2; // no definition

    puts(*x1);
}
