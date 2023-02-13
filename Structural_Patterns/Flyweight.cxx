#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  Flyweight
 * 
 * - minimize memory usage by separating shared stages and unique states.
 * 
 * - can be recognized by creation method that returns cached objects instead of
 * creating new.
 */



struct SharedState
{
    string brand_;
    string model_;
    string color_;

    SharedState(const string& brand, const string& model, const string& color)
        : brand_(brand), model_(model), color_(color) { }

    friend ostream& operator <<(ostream &os, const SharedState& s) {
        return os << "[" << s.brand_ << ", " << s.model_ << ", " << s.color_ << "]";
    }
};

struct UniqueState
{
    string owner_;
    string plates_;

    UniqueState(const string& owner, const string& plates)
        : owner_(owner), plates_(plates) {}
    
    friend ostream& operator <<(ostream &os, const UniqueState& s) {
        return os << "[" << s.owner_ << ", " << s.plates_ << "]";
    }
};

/**
 * The Flyweight stores a common portion of the state (also called intrinsic
 * state) that belongs to multiple real business entities. The Flyweight accepts
 * the rest of the state (extrinsic state, unique for each entity) via its
 * method parameters.
 */
class Flyweight
{
    private:
        SharedState *shared_state_;
    
    public:
        Flyweight(const SharedState *shared_data) : shared_state_(new SharedState(*shared_data)) {}

        Flyweight(const Flyweight &other) : shared_state_(new SharedState(*other.shared_state_)) {}

        ~Flyweight() {
            delete shared_state_;
        }

        SharedState* shared_state() const {
            return shared_state_;
        }

        void operation(const UniqueState& unique_state) const {
            cout << "Flyweight: Displaying shared (" << *shared_state_ << ") and unique state (" << unique_state << ")\n";
        }
};

class FlyweightFactory
{
    private:
        unordered_map<string, Flyweight> flyweights_;
    
        string getKey(const SharedState& ss) const {
            return ss.brand_ + " " + ss.model_ + " " + ss.color_;
        }

    public:
        FlyweightFactory(std::initializer_list<SharedState> shared_states) {
            for (const SharedState& ss : shared_states) {
                flyweights_.insert(make_pair(getKey(ss), Flyweight(&ss)));
            }
        }

        Flyweight getFlyweight(const SharedState& shared_state) {
            string key = getKey(shared_state);
            if (flyweights_.find(key) == flyweights_.end()) {
                cout << "FlyweightFactory: Can't fint a flyweight, creating new one.\n";
                flyweights_.insert(make_pair(key, Flyweight(&shared_state)));
            } else {
                cout << "FlyweightFactory: Reusing existing flyweight.\n";
            }
            return flyweights_.at(key);
        }

        void listFlyweights() const {
            size_t count = flyweights_.size();
            cout << "FlyweightFactory: I have " << count << " flyweights:\n";
            for (auto &p : flyweights_) {
                cout << p.first << "\n";
            }
        }
};

void AddCarToPoliceDataset(FlyweightFactory &ff, const string &plates, const string& owner, 
const string& brand, const string& model, const string &color) {
    cout << "\nClient: Adding a car to database: \n";
    const Flyweight& flyweight = ff.getFlyweight({brand, model, color});

    // the client stores or calculates extrinsic state and pass it to the flyweight's method
    flyweight.operation({owner, plates});
}




int main() {
    std::cout << "Flyweight\n\n";

    FlyweightFactory *ff = new FlyweightFactory({{"Chevrolet", "Camaro2018", "pink"}, {"Mercedes Benz", "C300", "black"}, {"Mercedes Benz", "C500", "red"}, {"BMW", "M5", "red"}, {"BMW", "X6", "white"}});
    ff->listFlyweights();

    AddCarToPoliceDataset(*ff,
                          "CL234IR",
                          "James Doe",
                          "BMW",
                          "M5",
                          "red");

    AddCarToPoliceDataset(*ff,
                          "CL234IR",
                          "James Doe",
                          "BMW",
                          "X1",
                          "red");
    ff->listFlyweights();

    delete ff;

    return 0;
}