class Widget
{
private:
    /* data */
public:
    Widget(/* args */);
    ~Widget();
    void Foo();
    
};

Widget::Widget(/* args */)
{
}

Widget::~Widget()
{
}

class Gadget
{
private:
    /* data */
    Gadget(/* args */);
public:
    ~Gadget();
    template<typename T>
    friend T& GetInstance();

};

void Widget::Foo()
{

}

Widget w;

Gadget::Gadget(/* args */)
{
    w.Foo();
}

Gadget::~Gadget()
{
}
template<typename T>
T& GetInstance()
{
    static T g1;

    return (g1);
}

int main()
{
    Gadget g = GetInstance<Gadget>();
    Gadget g1 = GetInstance<Gadget>();

    w;
    return 0;
}