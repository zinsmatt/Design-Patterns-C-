#include <iostream>
#include <unordered_map>

using namespace std;

/**
 *  Factory Method (template version):
 * 
 * - provides interface for creating objects in a superclass, but allows subclasses
 *   to alter the type of objects that will be created
 * - the different type of objects should share a common base interface
 * 
 */




// Product interface
class Product
{
    public:
    virtual ~Product() {}
    virtual std::string operation() const = 0;
};


class ConcreteProduct1 : public Product
{
    public:
        std::string operation() const override {
            return "Concrete Product 1";
        }

};

class ConcreteProduct2 : public Product
{
    public:
        std::string operation() const override {
            return "Concrete Product 2";
        }
};




// Base Factory
class Creator
{
    public:
        virtual ~Creator() {}

        // Factory method with implementation in subclasses to create different types of objects
        virtual Product* factory_method() const = 0;

        void doSomeOperation() const {
            auto * p = factory_method();
            cout << "Creator: the same creator has worked with " << p->operation() << "\n";
            delete p;
        }

};

template <class TProd>
class ConcreteProductCreator : public Creator
{
    public:
        Product* factory_method() const override {
            return new TProd();
        }
};


int main() {
    std::cout << "Factory Method (templated version)\n\n";

    Creator* creator1 = new ConcreteProductCreator<ConcreteProduct1>();
    creator1->doSomeOperation();
    delete creator1;

    Creator* creator2 = new ConcreteProductCreator<ConcreteProduct2>();
    creator2->doSomeOperation();
    delete creator2;

    
    return 0;
}