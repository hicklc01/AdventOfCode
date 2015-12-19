#include<iostream>
#include<locale>
#include<numeric>
#include<iterator>
#include<vector>
#include<functional>
#include<regex>

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

class Password: public string
{
    public:
        Password& operator++(){
            int place = length()-1;
            string & input = *this;
            while(++(input[place])>'z')
            {
                input[place] = 'a';
                place--;
            }
        };
        Password& operator++(int){
            int place = length()-1;
            string & input = *this;
            while(++(input[place])>'z')
            {
                input[place] = 'a';
                place--;
            }
        };
};

int main()
{
    
    vector<function<bool(Password)>> validators
    {
        [](Password password){
            vector<char> banned_list{'i','o','l'};
                return !accumulate(
                    banned_list.begin(),
                    banned_list.end(),
                    false,
                    [&](bool valid,char banned_char){
                      return valid || password.find(banned_char)!=string::npos;  
                    });
            
            },
        [](Password password){
            for(int i = 0;i+2<password.length();i++){
                if(
                    password[i] == (password[i+1]-1) &&
                    password[i] == (password[i+2]-2)       
                    ) return true;   
            }
            return false;
        },
        [](Password password){
            regex pairs("(\\w)\\1");
            return distance(
                sregex_token_iterator(password.begin(),password.end(),pairs,0),
                sregex_token_iterator())
            >=2;
        }
    };

    cin.imbue(locale(locale(),new line_reader()));
    int count = accumulate(
        istream_iterator<Password>(cin),
        istream_iterator<Password>(),
        0,
        [&](int count,Password password){
            do{
                password++;
            }while(
                accumulate(
                    validators.begin(),
                    validators.end(),
                    false,
                    [&](bool valid,function<bool(Password)> validator){
                        return valid || !validator(password);
                    }
                )
            );
            cout<<password<<endl;
            return count+1;
        }
        );
    return 0;
}
