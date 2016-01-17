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

regex dist_regex("(\\w+) would (gain|lose) (\\d+) happiness units by sitting next to (\\w+).");




int main()
{
    map<string,map<string,int>> dhappy;
    vector<string> guests;
    cin.imbue(locale(locale(),new line_reader()));
    int count = accumulate(
        istream_iterator<string>(cin),
        istream_iterator<string>(),
        0,
        [&](int count,string line){
            smatch dm;
            regex_match(line,dm,dist_regex);
            dhappy[dm[1]][dm[4]] = stoi(dm[3])*( (dm[2]=="gain")?1:-1  );
	    //6am hack for part 2 comment out for part1
	    dhappy["hicklc01"][dm[1]] = 0;
	    return count+1;
        });
    for(auto guest: dhappy)
        guests.push_back(guest.first);
    sort(guests.begin(),guests.end());
    int largest = numeric_limits<int>::min();
    int number = guests.size();
    do{
        int current = 0;
        for(int i =0; i<number;i++){
		current += dhappy[guests[i]][guests[(i+number-1)%number]];  
        	current += dhappy[guests[i]][guests[(i+number+1)%number]];  
        }
        largest = max(largest,current);
    } while(std::next_permutation(guests.begin(),guests.end()));
    cout<<largest<<endl;
    return 0;
}
