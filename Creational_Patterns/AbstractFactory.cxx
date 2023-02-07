#include <iostream>
#include <unordered_map>

using namespace std;

/**
 *  Abstract Factory:
 * 
 * - create families of related objects
 * 
 * - for example: chair (A) and sofa (B) can be built in type modern (1) or victorian (2)
 *  => one abstractFactory to define the interface for creating a chair or a sofa
 *  => two conrete factories to produce either modern or victorian-style objects 
 *  (each implement the construction method for chair and sofa in the corresponding style)
 *  Two products from the same factory are compatible together, i.e they have the same style.
 * 
 */


// ProductA interface
class AbstractProductA
{
    public:
    virtual ~AbstractProductA() {}
    virtual void print() const = 0;
};

class ConcreteProductA1 : public AbstractProductA
{
    public:
        virtual void print() const override {
            cout << "Product A1\n";
        }
};

class ConcreteProductA2 : public AbstractProductA
{
    public:
        virtual void print() const override {
            cout << "Product A2\n";
        }
};


// ProductA interface
class AbstractProductB
{
    public:
    virtual ~AbstractProductB() {}
    virtual void print() const = 0;
};

class ConcreteProductB1 : public AbstractProductB
{
    public:
        virtual void print() const override {
            cout << "Product B1\n";
        }
};

class ConcreteProductB2 : public AbstractProductB
{
    public:
        virtual void print() const override {
            cout << "Product B2\n";
        }
};



class AbstractFactory
{
    public:
        virtual AbstractProductA* buildProductA() = 0;
        virtual AbstractProductB* buildProductB() = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
    public:
        virtual AbstractProductA* buildProductA() override {
            return new ConcreteProductA1;
        }

        virtual AbstractProductB* buildProductB() override {
            return new ConcreteProductB1;
        }
};

class ConcreteFactory2 : public AbstractFactory
{
    public:
        virtual AbstractProductA* buildProductA() override {
            return new ConcreteProductA2;
        }

        virtual AbstractProductB* buildProductB() override {
            return new ConcreteProductB2;
        }
};





int main() {
    std::cout << "Abstract Factory\n\n";

    AbstractFactory *fact = new ConcreteFactory1();

    AbstractProductA *p1 = fact->buildProductA();
    p1->print();
    AbstractProductB *p2 = fact->buildProductB();
    p2->print();
    
    delete p1, p2, fact;

    AbstractFactory *fact2 = new ConcreteFactory2();
    AbstractProductA *p3 = fact2->buildProductA();
    p3->print();
    AbstractProductB *p4 = fact2->buildProductB();
    p4->print();

    delete p3, p4, fact2;
    
    return 0;
}