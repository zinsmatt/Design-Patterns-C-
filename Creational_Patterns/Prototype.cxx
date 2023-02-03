#include <iostream>
#include <unordered_map>

using namespace std;

/**
 *  Prototype:
 * 
 * - let you copy an existing object without making the code dependent on their class
 * - used to create a clone of an object
 * - otherwise we need to know the class attributes in order to copy each of them
 * - delegates the cloning process to the actual object by implementing a clone() method
 * 
 */


enum class Type {
    PROTO_TYPE_1,
    PROTO_TYPE_2
};



// Prototype interface. All concrete interface need to declare a clone method
class Prototype
{
    protected:
        string name_;

    public:
        Prototype(const string& name) : name_(name) {}

        virtual Prototype* clone() const = 0;

        virtual void print() const = 0;
};

class ConcretePrototype1 : public Prototype
{
    private:
        int value_;

    public:
        ConcretePrototype1(const std::string& name, int value) :
            Prototype(name), value_(value) {}

        // Copy Constructor automatically generated

        Prototype* clone() const {
            return new ConcretePrototype1(*this);
        }

        void print() const {
            cout << "ConcretePrototype: " << name_ << " " << value_ << "\n";
        }
};


class ConcretePrototype2 : public Prototype
{
    private:
        float value_;

    public:
        ConcretePrototype2(const std::string& name, float value) :
            Prototype(name), value_(value) {}
        
        // Copy constructor is automatically generated

        Prototype* clone() const {
            return new ConcretePrototype2(*this);
        }

        void print() const {
            cout << "ConcretePrototype2: " << name_ << " " << value_ << "\n";
        }

};



// Prototype factory. It creates a set of initial objects and then call clone to get a new object
class PrototypeFactory
{
    private:
        std::unordered_map<Type, Prototype*> prototypes_;

    public:

        PrototypeFactory() {
            prototypes_[Type::PROTO_TYPE_1] = new ConcretePrototype1("proto1", 0);
            prototypes_[Type::PROTO_TYPE_2] = new ConcretePrototype2("proto2", 3.14);
        }

        ~PrototypeFactory() {
            for (auto &p : prototypes_)
                delete p.second;
        }

        Prototype* createPrototype(Type type) {
            return prototypes_[type]->clone();
        }
};



int main() {
    std::cout << "Prototype\n";

    ConcretePrototype1 obj("losc", 1);
    obj.print();

    Prototype* obj2 = obj.clone();
    obj2->print();
    delete obj2;


    ConcretePrototype2 obj3("csol", 3.14);
    obj3.print();

    Prototype* obj4 = obj3.clone();
    obj4->print();
    delete obj4;


    // Test prototype factory
    PrototypeFactory factory;

    Prototype* obj5 = factory.createPrototype(Type::PROTO_TYPE_1);
    obj5->print();
    delete obj5;

    Prototype* obj6 = factory.createPrototype(Type::PROTO_TYPE_2);
    obj6->print();
    delete obj6;

    return 0;
}