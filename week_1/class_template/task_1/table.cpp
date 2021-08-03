#include "test_runner.h"

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

template <typename T>
class Table {
public:
    Table(size_t hor, size_t vert){
        Resize(hor, vert);
    }

    // Methods
    void Resize(size_t hor, size_t vert){
        table_.resize(hor);
        for (auto& t : table_){
            t.resize(vert);
        }
    }

    pair<size_t, size_t>  Size() const {
        if (table_.size() == 0)
            return make_pair(0,0);
        else if (table_.begin()->size() == 0){
            return make_pair(0,0);
        }
        return make_pair(table_.size(), table_.begin()->size());
    }

    //Operators
    vector<T>& operator[] (const int index) {
        return table_[index];
    }

    const vector<T>& operator[] (const int index) const {
        return table_[index];
    }

private:
    vector<vector<T>> table_;
};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
