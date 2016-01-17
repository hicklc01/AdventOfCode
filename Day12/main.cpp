#include "lasote/json11/json11.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace json11;

int traverse_node(Json &node);

int traverse_array(Json &node)
{
	int sum = 0;
	vector<Json> items =  node.array_items();
	for(vector<Json>::iterator it = items.begin();it!=items.end();it++){
		sum+=traverse_node(*it);
	}
	return sum;

};

int traverse_object(Json &node)
{
	int sum = 0;
	map<string,Json> items =  node.object_items();

	for(map<string,Json>::iterator it = items.begin();it!=items.end();it++){
		if(it->second.is_string()){
			if(it->second.string_value()=="red")
				return 0;
		}
		sum+=traverse_node(it->second);
	}
	return sum;
};

int traverse_node(Json &node){
	switch(node.type())
	{
		case Json::Type::NUL: return 0;
		case Json::Type::NUMBER: return node.int_value();
		case Json::Type::BOOL: return 0;
		case Json::Type::STRING: return 0;
		case Json::Type::ARRAY: return traverse_array(node);
		case Json::Type::OBJECT: return traverse_object(node);
	}

};

int main(){
	string raw;
	cin>> raw;
	string err;
	auto node = Json::parse(raw,err);
	cout<<"SUM "<<traverse_node(node)<<endl;
};
