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
 *  Strategy
 *
 * - turns a set of behaviours into objects and makes them interchangeable inside original context object
 * - unlike template method which override some parts of an algorithm using inheritance, Strategy
 *  is based on composition and can change the complete algorithm at runtime.
 */

class Strategy
{
    public:
        virtual ~Strategy() {}
        virtual string doAlgorithm(const string &data) const = 0;
};


class Context
{
    private:
        std::unique_ptr<Strategy> strategy_;

    public:
        explicit Context(std::unique_ptr<Strategy> &&strategy = {}) : strategy_(std::move(strategy)) {}

        void setStrategy(std::unique_ptr<Strategy> &&strategy) {
            strategy_ = std::move(strategy);
        }

        void doSomeBusinessLogic() const {
            if (strategy_) {
                cout << "Context: Sorting data using the strategy\n";
                string result = strategy_->doAlgorithm("aecbd");
                cout << "result: " << result << "\n";
            } else {
                cout << "Context: Strategy isn't set.\n";
            }
        }
};


class ConcreteStrategyA : public Strategy
{
    public:
        virtual string doAlgorithm(const string& data) const override {
            string res(data);
            std::sort(res.begin(), res.end());
            return res;
        }
};


class ConcreteStrategyB : public Strategy
{
    public:
        virtual string doAlgorithm(const string& data) const override {
            string res(data);
            sort(res.begin(), res.end(), std::greater<char>());
            return res;
        }
};


int main() {
    std::cout << "Strategy\n\n";

    Context context(std::make_unique<ConcreteStrategyA>());
    cout << "Client: Strategy is set to normal sorting.\n";
    context.doSomeBusinessLogic();
    cout << "\n";
    cout << "Client: Stragey is set to reverse sorting.\n";
    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();

    return 0;
}