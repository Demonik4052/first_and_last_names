#include <iostream>
#include <string>
#include <map>
#include <iterator>
using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string& first_name){
		change_first_name[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name){
		change_last_name[year] = last_name;
	}
	string GetFullName(int year){
		map<int, string, greater<int>> :: iterator first_name;
		first_name = change_first_name.lower_bound(year);
		map<int, string, greater<int>> :: iterator last_name;
		last_name = change_last_name.lower_bound(year);

		if(first_name == end(change_first_name) && last_name == end(change_last_name))
		{
			string name = "Incognito";
			return name;
		}else if(first_name != end(change_first_name) && last_name == end(change_last_name))
		{
			string name = first_name->second + " with unknown last name";
			return name;
		}else if(first_name == end(change_first_name) && last_name != end(change_last_name))
		{
			string name = last_name->second + " with unknown first name";
			return name;
		}else{
			string name = first_name->second + " " + last_name->second;
			return name;
		}
	}

private:
	map<int, string, greater<int>> change_first_name;
	map<int, string, greater<int>> change_last_name;
};

int main() {
	Person person;
	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	return 0;
}
