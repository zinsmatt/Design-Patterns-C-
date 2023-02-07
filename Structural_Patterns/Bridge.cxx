#include <iostream>
#include <list>
#include <ctime>
#include <random>

using namespace std;

/**
 *  Bridge
 * 
 * - useful to separate abstract interface (not in the inheritance sense) from implementation.
 * 
 * Example:
 *  - the Abstraction is the GUI layer
 *  - the Implementation is the OS API
 *  you can change the GUI without changing the implementation and add another OS by extending 
 *  the implementation without touching the GUI.
 */



// Implementation interface
class Implementation
{
    public:
        virtual ~Implementation() {}
        virtual string OperationImplementation() const = 0;
};

class ConcreteImplementationA : public Implementation
{
    public:
        virtual string OperationImplementation() const {
            return "ConcreteImplementationA: Here's the result on the platform A.\n";
        }
};

class ConcreteImplementationB : public Implementation
{
    public:
        virtual string OperationImplementation() const {
            return "ConcreteImplementationB: Here's the result on the platform B.\n";
        }
};

class Abstraction
{
    protected:
        Implementation *impl_ = nullptr;
    
    public:
        Abstraction(Implementation* impl) : impl_(impl) {}

        virtual ~Abstraction() {}

        virtual string Operation() const {
            return "Abstraction: Base operation with: \n" + this->impl_->OperationImplementation();
        }
};


class ExtendedAbstraction : public Abstraction
{
    public:
        ExtendedAbstraction(Implementation *impl) : Abstraction(impl) {}

        string Operation() const override {
            return "ExtendedAbstraction: Extended operation with: \n" + this->impl_->OperationImplementation();
        }
};





int main() {
    std::cout << "Bridge\n\n";

    Implementation *impl = new ConcreteImplementationA();
    Abstraction *abstraction = new Abstraction(impl);

    cout << abstraction->Operation() << "\n";
    delete impl, abstraction;

    impl = new ConcreteImplementationB();
    abstraction = new ExtendedAbstraction(impl);
    cout << abstraction->Operation() << "\n";
    delete impl, abstraction;


    return 0;
}