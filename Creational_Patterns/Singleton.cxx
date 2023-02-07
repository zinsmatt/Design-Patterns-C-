#include <iostream>

using namespace std;

/**
 *  Singleton
 * 
 * - Ensure a class has a single instance
 * - Provide a global access to that instance
 * 
 */


class Singleton_Database
{
    private:
        string name_;

        static Singleton_Database *instance_;

        // private constructor
        Singleton_Database(const std::string& name)
        : name_(name) {}


    public:

        static Singleton_Database* GetInstance(const std::string& name) {
            if (!instance_)
                instance_ = new Singleton_Database(name);
            return instance_;
        }

        static void ReleaseInstance() {
            if (instance_)
                delete instance_;
        }

        Singleton_Database(Singleton_Database&) = delete; // not copyable
        Singleton_Database& operator =(Singleton_Database&) = delete; // not assignable

        string GetName() const {
            return name_;
        }

};

// Initialize the instance
Singleton_Database* Singleton_Database::instance_ = nullptr;



int main() {
    std::cout << "Singleton\n\n";

    Singleton_Database *db = Singleton_Database::GetInstance("losc.db");

    std::cout << "DB name: " << db->GetInstance("losc.db")->GetName() << "\n";

    Singleton_Database::ReleaseInstance();

    return 0;
}