#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
        class ObjectPool {
        public:
            T* Allocate(){
                if (!free.empty()) {
                    auto p = free.front();
                    busy.insert(p);
                    free.pop();
                    return p;
                }
                T* obj = new T;
                busy.insert(obj);
                return obj;
            }

            T* TryAllocate(){
                if (!free.empty()) {
                    auto p = free.front();
                    busy.insert(p);
                    free.pop();
                    return p;
                }
                return nullptr;
            }

            void Deallocate(T* object){
                auto p = busy.find(object);
                if (p == busy.end()) {
                    throw std::invalid_argument("No object!");
                }
                free.push(*p);
                busy.erase(p);
            }


            ~ObjectPool() {
                while (!free.empty()) {
                    auto p = free.front();
                    delete p;
                    free.pop();
                }
                for (auto b : busy) {
                    delete b;
                }
            }

        private:
            queue<T*> free;
            set<T*> busy;
        };

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}