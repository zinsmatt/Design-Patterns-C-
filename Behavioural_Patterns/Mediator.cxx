#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  Mediator
 *
 * - reduces coupling between components of a progrma by making them communicate indirectly
 *  through a special mediator object.
 * 
 * - for example: planes and helicopter on an airport do not communicate directly between them but through the control tower.
 *
 */


class BaseComponent;

class Mediator
{
    public:
        virtual void notify(BaseComponent* sender, const string &event) const = 0;
};

class BaseComponent
{
    protected:
        Mediator *mediator_;
    public:
        BaseComponent(Mediator* mediator=nullptr) : mediator_(mediator) {}

        void setMediator(Mediator *mediator) {
            mediator_ = mediator;
        }
};

class Component1 : public BaseComponent
{
    public:
        void DoA() {
            cout << "Component 1 does A.\n";
            mediator_->notify(this, "A");
        }

        void DoB() {
            cout << "Component 1 does B.\n";
            mediator_->notify(this, "B");
        }
};

class Component2 : public BaseComponent
{
    public:
        void DoC() {
            cout << "Component 2 does C.\n";
            mediator_->notify(this, "C");
        }

        void DoD() {
            cout << "Component 2 does D.\n";
            mediator_->notify(this, "D");
        }
};


class ConcreteMediator : public Mediator
{
    private:
        Component1 *component1_;
        Component2 *component2_;
    public:
    ConcreteMediator(Component1 *c1, Component2 *c2) : component1_(c1), component2_(c2) {
        component1_->setMediator(this);
        component2_->setMediator(this);
    }

    void notify(BaseComponent *sender, const string& event) const override {
        // redirect event to react correctly
        if (event == "A") {
            cout << "Mediator reacts on A and triggers following operations:\n";
            component2_->DoC();
        }
        if (event == "D") {
            cout << "Mediator reacts on D and triggers following operations:\n";
            component1_->DoB();
            component2_->DoC();
        }
    }
};




int main() {
    std::cout << "Mediator\n\n";

    Component1 *c1 = new Component1;
    Component2 *c2 = new Component2;

    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
    cout << "Client triggers operation A.\n";
    c1->DoA();
    cout << "\n";
    cout << "Client triggers operation D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
    
    return 0;
}