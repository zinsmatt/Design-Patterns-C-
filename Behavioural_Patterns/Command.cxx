#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  Command
 *
 * - converts a request or simple operations into objects.
 * - often used as an alternative for callbacks to parameterizing UI element with actions
 * - also used for queueing tasks, trakcing operations history, ...
 *
 */

class Command
{
    public:
        virtual ~Command() {}
        virtual void Execute() const = 0;
};

class SimpleCommand : public Command
{
    private:
        string pay_load_;
    public:
        SimpleCommand(const string& pay_load) : pay_load_(pay_load) { }

        void Execute() const override {
            cout << "SimpleCommand: See, I can do simple things like printing (" << this->pay_load_ << ")\n";
        }
};


class Receiver
{
    public:
        void DoSomething(const string& a) {
            cout << "Receiver: Working on (" << a << ")\n";
        }
        void DoSomethingElse(const string& b) {
            cout << "Receiver: Also working on (" << b << ")\n";
        }
};



class ComplexCommand : public Command
{
    private:
        Receiver *receiver_ = nullptr;
        string a_;
        string b_;

    public:
        ComplexCommand(Receiver *rec, const string& a, const string& b) 
            : receiver_(rec), a_(a), b_(b) {}
        
        void Execute() const override {
            cout << "ComplexCommand: Complex stuff should be done by a receiver object\n";
            receiver_->DoSomething(a_);
            receiver_->DoSomethingElse(b_);
        }
};


class Invoker
{
    private:
        Command *on_start_ = nullptr;
        Command *on_finish_ = nullptr;
    
    public:
        ~Invoker() {
            if (on_start_)
                delete on_start_;
            if (on_finish_)
                delete on_finish_;
        }

        void setOnStart(Command* cmd) {
            on_start_ = cmd;
        }

        void setOnFinish(Command *cmd) {
            on_finish_ = cmd;
        }

        void DoSomethingImportant() {
            cout << "Invoker: Does anybody want something done before I begin?\n";

            if (on_start_)
                on_start_->Execute();

            cout << "Invoker: ...doing something really important...\n";
            cout << "Invoker: Doest anybody wants something done after I finish?\n";

            if (on_finish_)
                on_finish_->Execute();

        }
};


int main() {
    std::cout << "Command\n\n";

    Invoker *invoker = new Invoker;
    invoker->setOnStart(new SimpleCommand("Say Hi !!"));

    Receiver *receiver = new Receiver;
    invoker->setOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));

    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;
    
    return 0;
}