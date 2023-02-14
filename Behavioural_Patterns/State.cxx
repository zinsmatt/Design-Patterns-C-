#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  State
 *
 * - allows an object to change the behaviour when its internal state changes.
 * - avoid the large nb of conditions (if and switch)
 *
 */


class Context;

class State
{
    protected:
        Context *context_ = nullptr;
    
    public:
    virtual ~State() {}

    void setContext(Context *c) {
        context_ = c;
    }

    virtual void handle1() = 0;
    virtual void handle2() = 0;
};


class Context
{
    private:
        State *state_ = nullptr;
    public:
        Context(State *state) : state_(nullptr) {
            this->transitionTo(state);
        }

        ~Context() {
            delete state_;
        }

        void transitionTo(State *state) {
            std::cout << "Transition to " << typeid(*state).name() << ".\n";
            if (state_) {
                delete state_;
            }
            state_ = state;
            state_->setContext(this);
        }

        void request1() {
            state_->handle1();
        }

        void request2() {
            state_->handle2();
        }
};


class ConcreteStateA : public State
{
    public:
        void handle1() override;
        void handle2() override {
            cout << "ConcreteStateA handles request2.\n";
        }
};



class ConcreteStateB : public State
{
    public:
        void handle1() override {
            cout << "ConcreteStateB handles request1.\n";
        }
        void handle2() override {
            cout << "ConcreteStateB handles request2.\n";
            cout << "ConcreteStateB wants to change the state of the context.\n";
            context_->transitionTo(new ConcreteStateA);
        }
};


void ConcreteStateA::handle1() {
    cout << "ConcreteStateA handles request1.\n";
    cout << "ConcreteStateA wants to change the state of the context.\n";
    context_->transitionTo(new ConcreteStateB);
}




int main() {
    std::cout << "State\n\n";

    Context *context = new Context(new ConcreteStateA);
    context->request2();

    context->request1();

    context->request1();

    context->request2();

    delete context;

    return 0;
}