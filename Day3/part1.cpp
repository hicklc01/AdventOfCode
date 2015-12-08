#include <iostream>
#include <iterator>
#include <numeric>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;
namespace std
{
    template<>
    struct  hash<pair<int,int>>
    {
        inline size_t operator()(const pair<int,int> &p) const {
            return hash<int>()(p.first)^ hash<int>()( p.second);
        }
    };
};

int main()
{
    unordered_set<pair<int,int>> homes = accumulate(
        istream_iterator<char>(cin),
        istream_iterator<char>(),
        unordered_set<pair<int,int>>(),
        [current = make_pair(0,0)](unordered_set<pair<int,int>> current_homes, char y) mutable {
            switch(y){
                case '<':
                    current.first -= 1;
                break;
                case '>':
                    current.first += 1;
                break;
                case '^':
                    current.second -= 1;
                break;
                case 'v':
                    current.second += 1;
                break;
                default:
                    cout<<y<<endl;
                break;
            }
            current_homes.insert(current);
            return current_homes; 
        }
    );
    cout<<homes.size()<<endl;
    homes.insert(make_pair(0,0));
    cout<<homes.size()<<endl;
    return 0;
}
