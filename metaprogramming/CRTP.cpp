// The curiously recurring template pattern, or CRTP, is a pattern in which a class derives from a template class
// where the template argument is the derived class. For example, "class Derived : Base<Derived>". Wikipedia
// has some good examples at https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern. This example
// derives from those.

#include <stdio.h>
#include <string>

#pragma region Simple object counter

template <typename T>
class counter
{
protected:

    counter()
    {
        ++objects_created;
        ++objects_alive;

        printf("create %s ", T::get_name().c_str());
        print_count();
    }

    counter(const counter&)
    {
        ++objects_created;
        ++objects_alive;

        printf("copied %s ", T::get_name().c_str());
        print_count();
    }

    ~counter() // Make the destructor protected. 
    {
        --objects_alive;

        printf("delete %s ", T::get_name().c_str());
        print_count();
    }

private: 
    void print_count()
    {
        printf("created=%d, alive=%d\n", objects_created, objects_alive);
    }

    static size_t objects_created;
    static size_t objects_alive;
};

template <typename T> size_t counter<T>::objects_created{ 0 };
template <typename T> size_t counter<T>::objects_alive{ 0 };

class X: counter<X>
{
public:
    static std::string get_name()
    {
        return "X";
    }
};

class Y : counter<Y>
{
public:
    static std::string get_name()
    {
        return "Y";
    }
};

#pragma endregion

#pragma region Static polymorphism. No virtual function calls.

template <typename T>
class Shape : counter<Shape<T>>
{
protected:
    Shape() = default;

public:
    static std::string get_name()
    {
        return T::get_name();
    }

    T clone()
    {
        printf("cloning %s via copy constructor\n", T::get_name().c_str());
        return *(static_cast<T*>(this));
    }
};

class Circle : Shape<Circle> 
{ 
public:
    using Shape<Circle>::clone;

    static std::string get_name()
    {
        return "Circle";
    }
};

class Square : Shape<Square> 
{
public:
    using Shape<Square>::clone;

    static std::string get_name()
    {
        return "Square";
    }
};

#pragma endregion


int main()
{
    {
        X x1;
        Y y1;

        X x2(x1);
    }

    // Output:
    // create X created=1, alive=1
    // create Y created=1, alive=1
    // copied X created=2, alive=2
    // delete X created=2, alive=1
    // delete Y created=1, alive=0
    // delete X created=2, alive=0
    // create Y created=2, alive=1
    // delete Y created=2, alive=0

    {
        Circle c1;
        Square s1;

        Circle c2 = c1.clone();
        Square s2 = s1.clone();
    }

    return 0;
}

