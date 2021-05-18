#pragma once
#include <string>
#include <iostream>
class Base
{
private:
	std::string name;
	int32_t age;
	float hight;
	float weight;
public:
	Base();
    Base(std::string name, int32_t age, float hight, float weight);
	~Base();
	void Show();
public:
    std::string getName() const;
    void setName(std::string name);

    int32_t getAge() const;
    void setAge(int32_t age);

    float getHight() const;
    void setHight(float hight);

    float getWeight() const;
    void setWeight(float weight);

};

