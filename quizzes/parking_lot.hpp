// parking lot - quiz 21/1/21

/*
classes:
    - parking lot
    - level
    - spot
    - row
    - vehicle

operations:
    - park a vehicle
    - unpark a vehicle
    - check available space
    - 

 */

#include <cstdlib>
class Vehicle;
class Spot;
class Level;
class Row;

class ParkingLot
{
public:
    ParkingLot(size_t nLevels, size_t nRows, size_t nSpotsInRow);
    ~ParkingLot();

    void ParkVehicle(const Vehicle& vehicle);
    void UnparkVehicle(const Vehicle &vehicle);
    int IsAvailable(const Vehicle &vehicle);
private:
    Level* levels;
};

class Vehicle
{
public:
    explicit Vehicle(int number, int type);
    virtual int GetType();
    virtual int GetNumber();
private:
    const int m_licenseNum;
    const int m_type;
};

class Car : public Vehicle
{
public:
    explicit Car(int number, int type);

};

class Bus : public Vehicle
{
public:
    explicit Bus(int number, int type);

};

class Motorcycle : public Vehicle
{
public:
    explicit Motorcycle(int number, int type);

};

class Level
{
public:

private:
    Row* rows;
};

class Row
{
private:
    Spot* spots;
};

class Spot
{
public:
    explicit Spot(int type);

    bool IsOccupied();
    int GetType();
private:
    int m_type;
    bool m_isOccupied;
};