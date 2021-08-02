#include <string>
#include <vector>
using namespace std;

#define GET_NUM(line) varios_##line

#define NAME(line) GET_NUM(line)

#define UNIQ_ID NAME(__LINE__)

int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}