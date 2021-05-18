#include "Base.h"

Base::Base()
{
    this->name = "NotSet";
    this->age = -1;
    this->hight = 0.0f;
    this->weight = 0.0f;
}

Base::Base(std::string name, int32_t age, float hight, float weight)
{
    this->name = name;
    this->age = age;
    this->hight = hight;
    this->weight = weight;
}

Base::~Base()
{
    std::cout << "delete the user" + this->name << "\n";
}

void Base::Show()
{
    std::cout << "The information of " << this->name << " is:\n\t"
        << "age :\t" << this->age << "\n\t"
        << "height:\t" << this->hight << "\n\t"
        << "weight:\t" << this->weight << "\n";
}

std::string Base::getName() const
{
    return name;
}

void Base::setName(std::string name)
{
    this->name = name;
}

int32_t Base::getAge() const
{
    return age;
}

void Base::setAge(int32_t age)
{
    this->age = age;
}

float Base::getHight() const
{
    return hight;
}

void Base::setHight(float hight)
{
    this->hight = hight;
}

float Base::getWeight() const
{
    return weight;
}

void Base::setWeight(float weight)
{
    this->weight = weight;
}

