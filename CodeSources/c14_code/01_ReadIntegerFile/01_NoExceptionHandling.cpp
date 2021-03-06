import <fstream>;
import <iostream>;
import <vector>;
import <string>;
import <string_view>;

using namespace std;

vector<int> readIntegerFile(string_view filename)
{
	ifstream inputStream { filename.data() };

	// Read the integers one-by-one and add them to a vector.
	vector<int> integers;
	int temp;
	while (inputStream >> temp) {
		integers.push_back(temp);
	}
	return integers;
}

int main()
{
	const string filename{ "IntegerFile.txt" };
	vector<int> myInts{ readIntegerFile(filename) };

	for (const auto& element : myInts) {
		cout << element << " ";
	}
	cout << endl;
}
