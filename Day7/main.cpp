#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>
#include <sstream>

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

struct Func
{
    string function;
    vector<string> input;
    bool found = false;
    unsigned value;
};

int main()
{
    regex func_regex("([0-9a-z]*) ?([A-Z]*) ?([0-9a-z]*) -> ([a-z]*)");
    smatch func_match;
    map<string,Func> gates;
    cin.imbue(locale(locale(),new line_reader()));
    int count = accumulate(
        istream_iterator<string>(cin),
        istream_iterator<string>(),
        0,
        [&](int count,string current){
            regex_match(current,func_match,func_regex);
            gates[func_match[4]].function = func_match[2];
            gates[func_match[4]].input.push_back(func_match[1]);
            gates[func_match[4]].input.push_back(func_match[3]);
            return count +1;
        });
    
    function<unsigned int(string)> process = [&gates,&func_match,&process](string variable){
        if(gates[variable].found) return gates[variable].value;
        if(regex_match(variable,func_match,regex("\\d+"))){
            unsigned int num;
            istringstream(variable) >> num;
            return num;
        }
        unsigned int value;
        switch(gates[variable].function[0])
        {
            case 'N':
                value = ~process(gates[variable].input[1]);
            break;
            case 'O':
                value = process(gates[variable].input[0])|process(gates[variable].input[1]);
            break;
            case 'A':
                value = process(gates[variable].input[0])&process(gates[variable].input[1]);
            break;
            case 'L':
                value = process(gates[variable].input[0])<<process(gates[variable].input[1]);
            break;
            case 'R':
                value = process(gates[variable].input[0])>>process(gates[variable].input[1]);
            break;
            default:
                value = process(gates[variable].input[0]);
        }
        gates[variable].value = value;
        gates[variable].found = true;
        return value;
    };
    unsigned int a = process("a");
    cout<<a<<endl;
    gates["b"].function ="";
    gates["b"].input.clear();
    gates["b"].input.push_back(to_string(a));
    for(map<string,Func>::iterator it = gates.begin(); it!=gates.end();++it){
        it->second.found = false;
    }   
    unsigned int b = process("a");
    cout<<b<<endl;
    return 0;
}
