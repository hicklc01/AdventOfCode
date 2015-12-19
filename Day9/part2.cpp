#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>
#include <sstream>
#include <limits>
#include <set>

using namespace std;

struct line_reader: std::ctype<char> {
    line_reader(): std::ctype<char>(get_table()) {}
    static std::ctype_base::mask const* get_table() {
        static std::vector<std::ctype_base::mask> 
             rc(table_size, std::ctype_base::mask());
        rc['\n'] = std::ctype_base::space;
        return &rc[0];
    }
};

regex dist_regex("(\\w+) to (\\w+) = (\\d+)");




int main()
{
    map<string,map<string,int>> dist;

    cin.imbue(locale(locale(),new line_reader()));
    int count = accumulate(
        istream_iterator<string>(cin),
        istream_iterator<string>(),
        0,
        [&](int count,string line){
            smatch dm;
            regex_match(line,dm,dist_regex);
            dist[dm[1]][dm[2]] = stoi(dm[3]);
            dist[dm[2]][dm[1]] = stoi(dm[3]);
            return count+1;
        });
    int largest = accumulate(
        dist.begin(),
        dist.end(),
        0,
        [&](int running_largest,const pair<string,map<string,int>>& current){
            function<int(string,set<string>)> find_largest = [&](string current,set<string> past){
                int largest = 0;
                for(map<string,int>::iterator jump = dist[current].begin();
                    jump != dist[current].end();jump++){
                    if(past.count(jump->first)==0){
                        set<string> n(past);
                        n.insert(jump->first);
                        int c = jump->second + find_largest(jump->first,n);
                        largest = max(c,largest);
                    }
                }
                return largest;
            };
            set<string> s;
            s.insert(current.first);
            int current_largest = find_largest(current.first,s);
            return max(running_largest,current_largest);
        }
    );
    cout<<"largest dist "<<largest<<endl;
    return 0;
}
