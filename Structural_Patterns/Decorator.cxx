#include <iostream>
#include <list>
#include <ctime>
#include <random>

using namespace std;

/**
 *  Decorator
 * 
 * - adds new behaviors to objects dynamically by placing them inside a special wrapper
 * - using decorator you can wrap objects countless number of times (like a stack)
 * 
 * Example:
 * - very useful in stream related code (NormalDataWriter, CompressedDataWriter, EncryptedDataWriter, ...)
 *  Encryption and Compression can be decorators
 */


class Component
{
    public:
        virtual ~Component() {}
        virtual string operation() const = 0;
};


class ConcreteComponent : public Component
{
    public:
        string operation() const override {
            return "ConcreteComponent";
        }
};


class Decorator : public Component
{
    protected:
        Component *component_;
    
    public:
        Decorator(Component* c) : component_(c) {}

        string operation() const override {
            return this->component_->operation();
        }
};

class ConcreteDecoratorA : public Decorator
{
    public:
        ConcreteDecoratorA(Component *c) : Decorator(c) {}

        string operation() const override {
            return "ConcreteDecoratorA (" + Decorator::operation() + ")";
        }
};

class ConcreteDecoratorB : public Decorator
{
    public:
        ConcreteDecoratorB(Component *c) : Decorator(c) {}

        string operation() const override {
            return "ConcreteDecoratorB (" + Decorator::operation() + ")";
        }
};






int main() {
    std::cout << "Decorator\n\n";

    Component *simple = new ConcreteComponent;
    cout << "simple : " << simple->operation() << "\n\n";

    ConcreteDecoratorA *decA = new ConcreteDecoratorA(simple);
    cout << "decA : " << decA->operation() << "\n\n";

    ConcreteDecoratorB *decAB = new ConcreteDecoratorB(decA);
    cout << "decAB : " << decAB->operation() << "\n\n";

    delete simple;
    delete decA;
    delete decAB;


    return 0;
}