#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Deque{
public:
    Deque() = default;

    //Methods
    bool Empty() const{
        return p_f.empty() && p_b.empty();
    }
    size_t Size() const{
        return p_f.size() + p_b.size();
    }

    //Operators
    T& operator[](size_t index) {
        if (index >= p_f.size()) {
            return p_b[index - p_f.size()];
        }
        return p_f[p_f.size() -index - 1];
    }
    const T& operator[](size_t index) const{
        if (index >= p_f.size()) {
            return p_b[index - p_f.size()];
        }
        return p_f[p_f.size() -index - 1];
    }

    T& At(size_t index){
        if (index > Size() - 1 || index < 0){
            throw std::out_of_range("out of range!");
        }
        return (*this)[index];
    }
    const T& At(size_t index) const{
        if (index > Size() - 1 || index < 0){
            throw std::out_of_range("out of range!");
        }
        return (*this)[index];
    }

    T& Front(){
        return At(0);
    }
    const T& Front() const{
        return At(0);
    }

    T& Back(){
        return Empty() ? At(0) : At(Size() - 1);
    }
    const T& Back() const{
        return Empty() ? At(0) : At(Size() - 1);
    }


    void PushFront(const T& val){
        p_f.push_back(val);
    }
    void PushBack(const T& val){
        p_b.push_back(val);
    }

private:
    vector<T> p_f;
    vector<T> p_b;
};






