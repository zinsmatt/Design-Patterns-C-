#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  Template Method
 *
 * - allows you to define a skeleton of an algorithm in a base class and let subclasses
 *  override the steps without changing the overall algorithm's structure.
 *
 */


class AbstractClass
{
    public:
        void TemplateMethod() const {
            this->BaseOperation1();
            this->RequiredOperation1();
            this->BaseOperation2();
            this->Hook1();
            this->RequiredOperation2();
            this->BaseOperation3();
            this->Hook2();
        }

    protected:
        
        // Common to all subclasses
        void BaseOperation1() const {
            cout << "AbstractClass: base operation1\n";
        }
        void BaseOperation2() const {
            cout << "AbstractClass: base operation2\n";
        }
        void BaseOperation3() const {
            cout << "AbstractClass: base operation3\n";
        }

        // These operations have to be implemented in concrete classes
        virtual void RequiredOperation1() const = 0;
        virtual void RequiredOperation2() const = 0;

        /**
         * "Hooks": Subclasses may override them, but it's not mandatory
         */
        virtual void Hook1() const {}
        virtual void Hook2() const {}
};


class ConcreteClass1 : public AbstractClass
{
    public:
        void RequiredOperation1() const override {
            cout << "ConcreteClass1: Implemented required Operation1\n";
        }

        void RequiredOperation2() const override {
            cout << "ConcreteClass1: Implemented required Operation2\n";
        }
};

class ConcreteClass2 : public AbstractClass
{
    public:
        void RequiredOperation1() const override {
            cout << "ConcreteClass2: Implemented required Operation1 !!!\n";
        }

        void RequiredOperation2() const override {
            cout << "ConcreteClass2: Implemented required Operation2 !!!\n";
        }

        void Hook1() const override {
            cout << "ConcreteClass2: Overriden Hook1 !!!\n";
        }

        void Hook2() const override {
            cout << "ConcreteClass2: Overriden Hook2 !!!\n";
        }
};



void ClientCode(AbstractClass *class_) {
    class_->TemplateMethod();
}


int main() {
    std::cout << "Template Method\n\n";

    cout << "Same Client can work with different subclasses:\n";

    ConcreteClass1 *concrete1 = new ConcreteClass1;
    ClientCode(concrete1);
    delete concrete1;


    cout << "\n\nSame Client can work with different subclasses:\n";

    ConcreteClass2 *concrete2 = new ConcreteClass2;
    ClientCode(concrete2);
    delete concrete2;

    return 0;
}