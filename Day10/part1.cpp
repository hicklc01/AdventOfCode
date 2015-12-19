#include<iostream>
#include<string>
#include<sstream>

using namespace std;

string lookandsay(const string &s)
{
    std::ostringstream o;
    for(int i =0;i!=s.length();){
        int new_i = s.find_first_not_of(s[i],i);
        if(new_i == string::npos)
            new_i = s.length();
        
        o << new_i-i << s[i];
        i = new_i;
    }
    return o.str();
}

int main(){
    string input;
    int rounds;
    cin>>input;
    cin>>rounds;
    for(int i =0;i<rounds;i++){
        input = lookandsay(input);
    }
    cout<<input.length()<<endl;
}
