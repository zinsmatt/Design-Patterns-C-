#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  Iterator
 * 
 * - allows to traverse a complex data structure without knowing its real internal details.
 * 
 * - example: DFS or BFS tree traversal iterators
 */



// T: data type
// U: container type (the iterator is working only with a container having with the same structure
// as the Container class declared below. It is possible to remove U and force Container<T>)
template <class T, class U>
class Iterator
{
    public:
        typedef typename std::vector<T>::iterator iter_type;

    private:
        U *m_p_data_;
        iter_type m_it_;

    public:

        Iterator(U *p_data, bool reverse=false) : m_p_data_(p_data) {
            m_it_ = m_p_data_->m_data_.begin();
        }

        void First() {
            m_it_ = m_p_data_->m_data_.begin();
        }

        void Next() {
            m_it_++;
        }

        bool IsDone() {
            return m_it_ == m_p_data_->m_data_.end();
        }

        iter_type Current() {
            return m_it_;
        }
};


template <class T>
class Container
{
    friend class Iterator<T, Container>;

    public:
        void Add(const T &a) {
            m_data_.push_back(a);
        }

        Iterator<T, Container> *CreateIterator() {
            return new Iterator<T, Container>(this);
        }

    private:
        std::vector<T> m_data_;
};

class Data
{
    public:
        Data(int a = 0) : m_data_(a) {}

        void setData(int a) {
            m_data_ = a;
        }

        int data() const {
            return m_data_;
        }

    private:
        int m_data_;
};



int main() {
    std::cout << "Iterator\n\n";

    std::cout << "Iterator with int:\n";
    Container<int> cont;
    for (int i = 0; i < 10; ++i) {
        cont.Add(i);
    }

    Iterator<int, Container<int>> *it = cont.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next()) {
        cout << *it->Current() << "\n";
    }



    cout << "Iterator with custom data:\n";

    Container<Data> cont2;
    Data a(200), b(2567), c(333);
    cont2.Add(a);
    cont2.Add(b);
    cont2.Add(c);

    Iterator<Data, Container<Data>> *it2 = cont2.CreateIterator();
    for (it2->First(); !it2->IsDone(); it2->Next()) {
        cout << it2->Current()->data() << "\n";
    }


    delete it;
    delete it2;


    return 0;
}