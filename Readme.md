# MakefileStudy

## 二. makefile介绍

makefile 一般来说，会具有以下特性：

1. 如果工程没有被编译过，那么，所有的c文件都要被编译并且链接
2. 如果工程中的某几个c文件被修改了，那么只需要编译被修改的几个c文件，并链接目标程序
3. 如果工程的头文件被改变了，那么我们则需要去编译引用了该头文件的c文件，并链接目标程序

### 2.1 makefile的规则

~~~shell
target... : prerequisites...
	command
	...
	...
# target 可以是一个目标文件 也可以是一个执行文件，还能是一个标签，target故名思意，其实就是我们要得到的文件
# prerequisites 生成target所需要的文件和（或）target
# command 可以是任意shell命令，但是一般会包含生成该target所需要的命令
# 其实 简单的来说 makefile就是一个文件之间的依赖关系：
########################################################################################
# 	prerequisites 种如果有一个以上的文件更新，那么就会重新执行command命令生成target文件###
########################################################################################
~~~

Make具有自动推导的功能，一般来讲，对于最为复杂的Makefile 以下列文件为例：

~~~cpp
##########demo.cpp#############
#include <iostream>
#include "Base.h"
using namespace std;
int main() {
	Base base("张三", 12, 186.3, 118.5);
	base.Show();
	return 0;
}                 

########Base.h##################
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

########Base.cpp###################
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


~~~

最为原始的makefile应该如下：

~~~makefile
demo : demo.o Base.o
	g++ -o demo demo.o Base.o
	
demo.o : demo.cpp Base.h
	g++ -c demo.cpp

Base.o : Base.cpp Base.h
	g++ -c Base.cpp
	
clean : 
	rm demo demo.o Base.o
~~~

makefile文件可以使用变量，对于上述的Makefile 其中，我们可以发现对于demo.o 和Base.o 两个文件，在多处都有使用，可以使用一个变量来替代：

~~~makefile
objects : demo.o Base.o

demo : $(objects)
	g++ -o demo $(objects)
	
demo.o : demo.cpp Base.h
	g++ -c demo.cpp

Base.o : Base.cpp Base.h
	g++ -c Base.cpp
	
clean : 
	rm demo $(objects)
~~~

更一般的，<span style = "color : red;">Make具有自动推导的功能</span>，它可以自动推到文件以及文件依赖关系背后的命令，例如：

​	对于一个.o文件 ，它会自动把.cpp/.c文件添加在依赖关系中，并且自动推导出相对应的命令：<span style = "color:red">g++/cc -c test.c</span> 所以，上述的makefile文件可以进一步进行简化：

~~~makefile
objects : demo.o Base.o

demo : $(objects)
	g++ -o demo $(objects)
	
demo.o :Base.h
Base.o : Base.h

.PHONY : clean
clean : 
	-rm demo $(objects)
~~~

同时，上述的makefile依旧显得略微复杂，可以进一步简化为以下：

~~~makefile
objects : demo.o Base.o

demo : $(objects)
	g++ -o demo $(objects)
	
$(objects) : Base.h

.PHONY : clean
clean : 
	-rm demo $(objects)
~~~

虽然这种makefile更为简洁，但是其依赖关系却不清晰。

<span style="color:red">Ps: .PHONY 表示clean命令为一个为目标，在rm前加-可以保证即使部分文件存在删除问题，也依旧进行后续清除任务。</span>

### 2.2 Makefile里面有什么

对于一个Makefile来说，有五个重要的东西：显示规则、隐式规则、变量定义、文件指示、注释

1. 显示规则。显示规则说明了如何生成一个或者多个目标文件，需要显示的指明将要生成的目标文件，依赖的文件以及文件的生成规则
2. 隐式规则：Makefile自动推导的规则。
3. 变量的定义：可以在Makefile中定义变量，且使用方法与c语言相同
4. 文件指示：可以在一个makefile中去引用另一个Makefile；更为特别的，可以载一个文件中指定引入另一个Makefile文件的部分有效内容。
5. 注释：Makefile中的注释使用#

对于文件指示，在Makefile中可以使用include关键字引入其他的Makefile：

~~~makefile
include <filename>
~~~

值得注意的是，在include的前面虽然可以存在一些空格，但是不能以Tab键开头。

除了显示的include引入的文件之外，make命令在执行的时候，还回去以下几个目录下进行查找：

- 如果make执行时存在-I 或者--include-dir参数，那么也有会在对应参数下的目录下去寻找makefile引入进来
- 如果目录<prefix>/include (一般而言是/usr/local/bin以及/usr/include)存在，也会在对应文件夹下去找。

#### 2.3 make的工作方式

make的工作方式一般如下：

1. 读入所有的makefile
2. 引入include文件
3. 初始化文件中的变量
4. 推导隐式规则，并分析规则
5. 为所有的目标文件创建依赖关系链
6. 根据依赖关系，决定重新生成哪些目标文件
7. 执行命令


