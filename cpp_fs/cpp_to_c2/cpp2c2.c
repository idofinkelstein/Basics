#include <stdio.h>

int Animal_s_count = 0;

enum func_name 
{
    Dtor = 0,
    Display = 1,
    BuySues = 2
};

typedef void (*FUNCPTR)(void*);

typedef struct 
{
    FUNCPTR *Vptr;
    int m_id;
}Animal;

typedef struct 
{
    Animal animal;
    int m_numLegs;
}Centipede;

typedef struct 
{
    Animal animal;
}Squirl;

/* Animal function declarations */
void AnimalCtor(Animal * const this);
void AnimalCCtor(Animal * const this, const Animal *animal);
void AnimalDtorV(Animal * const this);

void AnimalDisplayV(Animal * const this);
void AnimalPrintCount();
int AnimalGetID(Animal * const this);

Animal *AnimalOperatorAsignment(Animal * const this, const Animal other);

/* Centipede function declarations */
void CentipedeCtor(Centipede * const this);
void CentipedeCCtor(Centipede * const this, const Centipede *other);
void CentipedeDtorV(Centipede * const this);
void CentipedeDisplayV(Centipede * const this);
void CentipedeBuyShuesV(Centipede * const this);


/* Squirl function declarations */
void SquirlCtor(Squirl * const this);
void SquirlCCtor(Squirl * const this, const Squirl *other);
void SquirlDtorV(Squirl * const this);
void SquirlDisplayV(Squirl * const this);

FUNCPTR AnimalVMT[2] = 
{
    (void(*)(void*))AnimalDtorV,
    (void(*)(void*))AnimalDisplayV
};

FUNCPTR CentipedeVMT[3] = 
{
    (void(*)(void*))CentipedeDtorV,
    (void(*)(void*))CentipedeDisplayV,
    (void(*)(void*))CentipedeBuyShuesV
};

FUNCPTR SquirlVMT[2] = 
{
    (void(*)(void*))SquirlDtorV,
    (void(*)(void*))SquirlDisplayV
};


void AnimalCtor(Animal * const this)
{
    this->m_id = ++Animal_s_count;
    printf("Animal::Ctor()%d\n", this->m_id);
    this->Vptr = AnimalVMT;
}

void AnimalCCtor(Animal * const this, const Animal *animal)
{
    this->m_id = ++Animal_s_count;
    printf("Animal::CCtor()%d\n", this->m_id); 
    this->Vptr = AnimalVMT;
}

void AnimalDtorV(Animal * const this)
{
    --Animal_s_count;
    printf("Animal::Dtor()%d\n", this->m_id);
}

void AnimalDisplayV(Animal * const this)
{
    printf("Animal::Display()%d\n", this->m_id);
}
void AnimalPrintCount()
{
    printf("s_count: %d\n", Animal_s_count);
}

int AnimalGetID(Animal * const this)
{
    return this->m_id;
}


void CentipedeCtor(Centipede * const this)
{
    AnimalCtor(&this->animal);
    this->m_numLegs = 46;
    printf("s_count: %d\n", Animal_s_count);
    this->animal.Vptr = CentipedeVMT;
}
void CentipedeCCtor(Centipede * const this, const Centipede *other)
{
    AnimalCCtor(&this->animal, &other->animal);
    this->m_numLegs = other->m_numLegs;
    printf("Centipede::CCtor()\n");
    this->animal.Vptr = CentipedeVMT;
}
void CentipedeDtorV(Centipede * const this)
{
    AnimalDtorV(&this->animal);
    printf("Centipede::Dtor()\n");
}

void CentipedeDisplayV(Centipede * const this)
{
    printf("Centipede::Display() ID: %d num legs: %d\n",
             AnimalGetID(&this->animal), this->m_numLegs);
}

void CentipedeBuyShuesV(Centipede * const this)
{
    printf("Centipede::BuyShues() ID: %d\n", AnimalGetID(&this->animal));
}



/* Squirl function declarations */
void SquirlCtor(Squirl * const this)
{
    AnimalCtor(&this->animal);
    printf("Squirl::Ctor()\n");
}

void SquirlCCtor(Squirl * const this, const Squirl *other)
{
    AnimalCCtor(&this->animal, &other->animal);
    printf("Squirl::CCtor()\n");
}

void SquirlDtorV(Squirl * const this)
{
    AnimalDtorV(&this->animal);
    printf("Squirl::Dtor()\n");
}
void SquirlDisplayV(Squirl * const this)
{
    printf("Squirl::Display() ID: %d", AnimalGetID(&this->animal));
}

void Foo(Animal *a) 
{
    a->Vptr[Display](a);
}

void Foo2()
{ 
    AnimalPrintCount(); 
}

void AFoo(int i, Animal *res)
{
    Centipede temp;
    CentipedeCtor(&temp);

    printf("Foo(int i)\n");
    CentipedeDisplayV(&temp);

    AnimalCCtor(&temp.animal, res);
    CentipedeDtorV(&temp);
}

void FiFi(Centipede *c)
{
    Centipede temp;
    CentipedeCCtor(&temp, c);
    CentipedeDisplayV(&temp);
    CentipedeDtorV(&temp);
}

int main(int argc, char const *argv[])
{
    Centipede c;
    CentipedeCtor(&c);
    Foo(&c.animal);

    return 0;
}
