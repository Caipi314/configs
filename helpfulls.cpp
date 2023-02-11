#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

template <typename T>
string vecToStr(vector<T> vec, string label = "") {
	stringstream output;
	if (label.length())
		output << label + ": ";

	for (auto i : vec) {
		output << i;
		output << " ";
	}
	return output.str();
}

void demo_vector() {
	vector<string> countries = { "US", "Canada", "Mexico", "China" };

	// index vector
	cout << "First country: " << countries[0] << endl;
	cout << "Second last country: " << countries.at(countries.size() - 2) << endl; // cannot do .at() with negative number

	// find index of number
	auto indiaIdx = find(countries.begin(), countries.end(), "India");
	if (indiaIdx != countries.end()) {
		cout << "India is at " << (int)distance(countries.begin(), indiaIdx) << endl;
	}
	else {
		cout << "No India\n";
	}

	// does Canada exist after position 2
	auto caInEndPart = find(countries.begin() + 1, countries.end(), "Canada");
	if (caInEndPart != countries.end()) {
		cout << "Canada exists after pos 1\n";
	}
	else {
		cout << "No Canada after pos 1\n";
	}

}

void demo_transform() {
	string str = "hello there";
	string newStr;

	// transform to a new string
	transform(str.begin(), str.end(), back_inserter(newStr), [](char c) {
		return toupper(c);
		});
	// transform the original string
	transform(str.begin(), str.end(), str.begin(), [](char c) {
		return c - 1;
		});
	printf("New string (to upper): %s, Original string (+1): %s, \n", newStr.c_str(), str.c_str());


	vector<int> numbers = { 1, 3, 4, 5, 7, 8 };
	vector<int> squares;

	// transform to a new vector
	transform(numbers.begin(), numbers.end(), back_inserter(squares), [](int num) {
		return num * num;
		});

	// transform to original vector
	transform(numbers.begin(), numbers.end(), numbers.begin(), [](int num) {
		return num - 1;
		});
	printf("Numbers (-1): %s, Transformed (**2): %s\n", vecToStr(numbers).c_str(), vecToStr(squares).c_str());

	// equivalent of object.values
	unordered_map<string, int> map = {
		{"cai", 17},
		{"liana", 15},
		{"mom", 54},
		{"data", 54},
	};
	vector<string> names = { "daniel", "jakob" };
	transform(map.begin(), map.end(), back_inserter(names), [](pair<string, int> pair) {
		// pair.second for object.values
		return pair.first;
		});
	printf("%s\n", vecToStr(names, "names").c_str());


}

template <typename Ta, typename Tb>
string mapToStr(unordered_map<Ta, Tb> map, string label = "") {
	stringstream output;
	if (label.length())
		output << label + ": {";

	for (auto const& pair : map) {
		output << " " << pair.first << ": " << pair.second << ",";
	}
	output << " }";
	return output.str();
}
void demo_map() {
	// create map

	unordered_map<int, int> emptyMap;
	unordered_map<string, int> namesAge = {
		{"cai", 17},
		{"liana", 15},
		{"mom", 54},
		{"data", 54},
	};
	// add value
	emptyMap[-1] = 5;
	namesAge["bubby"] = 85;

	cout << mapToStr(emptyMap, "emptyMap") << '\n';
	cout << mapToStr(namesAge, "namesAge") << '\n';

	// remove value
	// namesAge.erase("bubby");

	// lookup value
	unordered_map<string, int>::iterator bubby = namesAge.find("bubby");
	if (bubby != namesAge.end()) {
		cout << bubby->first << " has " << bubby->second << '\n';
	}
	else {
		cout << "No bubby\n";
	}

	// or

	if (namesAge.count("bubby") > 0) {
		cout << "bubby has " << namesAge.at("bubby") << '\n';
	}
	else {
		cout << "No bubby\n";
	}

}

void demo_sort() {
	unordered_map<string, int> grades = {
		{"math", 94},
		{"chem", 92},
		{"tanach", 90},
		{"comp sci", 98},
		{"tanach2", 90},
		{"help", 93},
		{"music", 97}
	};
	unordered_map<string, int> grades_copy(grades);

	// sort map
	// you cannot sort unordered_map, must put them into a vector
	vector<pair<string, int>> gradesVec(grades.begin(), grades.end());
	sort(gradesVec.begin(), gradesVec.end());
	map<string, int> gradesMap(gradesVec.begin(), gradesVec.end());

	cout << "Default sort (key)\n";
	for (auto const& [key, value] : gradesMap) {
		cout << '\t' << key << ": " << value << '\n';
	}

	// sort map by value
	vector<pair<string, int>> _gradesVec(grades_copy.begin(), grades_copy.end());

	sort(_gradesVec.begin(), _gradesVec.end(), [](auto pair1, auto pair2) {
		return pair1.second > pair2.second;
		});

	// no way to get the vector of pairs back into a sorted map

	cout << "\nCustom sort (value)\n";
	for (auto const& pair : _gradesVec) {
		cout << '\t' << pair.first << ": " << pair.second << '\n';
	}

	// sort vector
	// sort opposites of vector
}

void demo_slice() {
	vector<int> nums = { -1, -3, 5, 3, 6 };

	// from -3 to 3
	vector<int> sliced(nums.begin() + 1, nums.end() - 1);
	cout << vecToStr(sliced) << '\n';
}

void demo_set() {
	// create empty set
	unordered_set<string> fruits;

	fruits.insert("banana");
	fruits.insert("apple");
	fruits.insert("pear");

	bool hasOrange = fruits.find("orange") != fruits.end();
	cout << (hasOrange ? "has orange" : "no orange") << endl;


	// create set from existing array (vector or set or ...)
	set<string> copy(fruits.begin(), fruits.end());

}

int main() {

	demo_vector();
	// demo_transform();
	// demo_map();
	// demo_sort();
	// demo_slice();
	// demo_set();

	return 0;
}