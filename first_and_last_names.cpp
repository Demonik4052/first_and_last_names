#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

string PrintHistoryNames(vector<string>& names)
{
	string str = "";
	int count_name = names.size() - 1;
	reverse(begin(names), end(names));
	for(const auto& name : names)
	{
		if(count_name != 0)
		{
			str += name + ", ";
			count_name--;
		}else{
			str += name;
		}
	}
	return str;
}

string FindNameByYear(const map<int, string>& names, int year)
{
	string name;
	for(const auto& item : names)
	{
		if(item.first <= year)
			name = item.second;
	}
	return name;
}

class Person {
public:
	void ChangeFirstName(int year, const string& first_name){
		first_names[year] = first_name;
	}

	void ChangeLastName(int year, const string& last_name){
		last_names[year] = last_name;
	}

	string GetFullName(int year){
		const string first_name = FindNameByYear(first_names, year);
		const string last_name = FindNameByYear(last_names, year);
		if(first_name.empty() && last_name.empty())
			return "Incognito";
		else if(first_name.empty())
		{
			return last_name + " with unknown first name";
		}
		else if(last_name.empty())
			return first_name + " with unknown last name";
		else
			return first_name + " " + last_name;
	}


	string GetFullNameWithHistory(int year)
	{
		const string first_name = FindNameByYear(first_names, year);
		const string last_name = FindNameByYear(last_names, year);
		vector<string> history_first = FindFirstNamesHistory(year, first_name);
		vector<string> history_last = FindLastNamesHistory(year, last_name);
		if(first_name.empty() && last_name.empty())
			return "Incognito";
		else if(first_name.empty())
		{
			if(history_last.size() == 0)
				return last_name + " with unknown first name";
			return last_name + " (" + PrintHistoryNames(history_last) + ")" +" with unknown first name";
		}
		else if(last_name.empty())
		{
			if(history_first.size() == 0)
				return first_name + " with unknown last name";
			return first_name + " (" + PrintHistoryNames(history_first) + ")" +" with unknown last name";
		}
		else
		{
			if(history_first.size() == 0 && history_last.size() == 0)
				return first_name + " " + last_name;
			else if(history_first.size() == 0)
				return first_name + " " + last_name + " (" + PrintHistoryNames(history_last) + ")";
			else if(history_last.size() == 0)
				return first_name + " (" + PrintHistoryNames(history_first) + ") " + last_name;
			else
				return first_name + " (" + PrintHistoryNames(history_first) + ") "
						+ last_name + " (" + PrintHistoryNames(history_last) + ")";
		}

	}

private:
	map<int, string> first_names;
	map<int, string> last_names;
	vector<string> last;
	vector<string> FindFirstNamesHistory(int year,const string& first_name)
	{
		vector<string> first;
		if(first_name == "")
			return first;
		for(const auto& item : first_names)
		{
			if(first.empty())
				first.push_back(item.second);
			else if(first.back() == item.second)
			{
				continue;
			}else if (item.first <= year){
				first.push_back(item.second);
			}
		}
		if(first.back() == first_name)
		{
			first.erase(first.end());
		}
		return first;
	}
	vector<string> FindLastNamesHistory(int year, const string& last_name)
	{
		vector<string> last;
		if(last_name == "")
			return last;
		for(const auto& item : last_names)
		{
			if(last.empty())
				last.push_back(item.second);
			else if(last.back() == item.second)
			{
				continue;
			}else if (item.first < year){
				last.push_back(item.second);
			}
		}
		if(last.back() == last_name)
		{
			last.erase(last.end());
		}
		return last;
	}
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	cout << person.GetFullNameWithHistory(1990) << endl;

	person.ChangeFirstName(1966, "Pauline");
	cout << person.GetFullNameWithHistory(1966) << endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	cout << person.GetFullNameWithHistory(1967) << endl;

	return 0;
}
