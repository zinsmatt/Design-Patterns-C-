#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <algorithm>


using namespace std;

/**
 *  Visitor
 * 
 * - allows adding new behaviour to existing class hierarchy without altering any existing code.
 * 
 * - relatively complex and not very common
 *
 */


class ConcreteComponentA;
class ConcreteComponentB;

class Visitor
{
    public:
        virtual void visitConcreteComponentA(const ConcreteComponentA *element) const = 0;
        virtual void visitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

class Component
{
    public:
        virtual ~Component() {}
        virtual void accept(Visitor *visitor) const = 0;
};

class ConcreteComponentA : public Component
{
    public:
        void accept(Visitor *visitor) const override {
            visitor->visitConcreteComponentA(this);
        }

        string ExclusiveMethodOfConcreteComponentA() const {
            return "A";
        }
};


class ConcreteComponentB : public Component
{
    public:
        void accept(Visitor *visitor) const override {
            visitor->visitConcreteComponentB(this);
        }
        string ExclusiveMethodOfConcreteComponentB() const {
            return "B";
        }
};

class ConcreteVisitor1 : public Visitor
{
    public:
        void visitConcreteComponentA(const ConcreteComponentA *element) const override {
            cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
        }

        void visitConcreteComponentB(const ConcreteComponentB *element) const override {
            cout << element->ExclusiveMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
        }
};


class ConcreteVisitor2 : public Visitor
{
    public:
        void visitConcreteComponentA(const ConcreteComponentA *element) const override {
            cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
        }

        void visitConcreteComponentB(const ConcreteComponentB *element) const override {
            cout << element->ExclusiveMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
        }
};

void ClientCode(std::array<const Component*, 2> components, Visitor* visitor)
{
    for (const auto* comp : components) {
        comp->accept(visitor);
    }
}



int main() {
    std::cout << "Strategy\n\n";

    std::array<const Component*, 2> components = {new ConcreteComponentA, new ConcreteComponentB};

    std::cout << "The client can work with all visitors via the base Visitor class\n";

    ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);

    cout << "\n";
    cout << "It allows the same client to work with different type of visitor\n";
    ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component *comp : components)
        delete comp;
    delete visitor1;
    delete visitor2;

    return 0;
}