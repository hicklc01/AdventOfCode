#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct xsv_reader: ctype<char>{
    xsv_reader(): ctype<char>(get_table()){}
    static ctype_base::mask const* get_table(){
    static vector<ctype_base::mask> rc(table_size, ctype_base::mask());
        rc['x'] = ctype_base::space;
        rc['\n'] = ctype_base::space;
        rc[' '] = ctype_base::space;
        return &rc[0];
    }
};

int main()
{
    int total = accumulate(
        istream_iterator<string>(cin),
        istream_iterator<string>(),
        0,
        [&](int x, string y) {  
            stringstream ss(y);
            ss.imbue(std::locale(std::locale(),new xsv_reader()));
            vector<int> sides = vector<int>(istream_iterator<int>(ss),
                istream_iterator<int>());
            sort(sides.begin(),sides.end());
            return x + 2*(sides[0]+sides[1]) + sides[0]*sides[1]*sides[2]; 
        }
    );
    cout<<total<<endl;
    return 0;
}
