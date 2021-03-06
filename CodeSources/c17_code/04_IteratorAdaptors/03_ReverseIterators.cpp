import <vector>;
import <iostream>;
import <iterator>;
import <format>;

using namespace std;

template<typename Iter>
auto myFind(Iter begin, Iter end, const typename iterator_traits<Iter>::value_type& value)
{
	for (auto iter{ begin }; iter != end; ++iter) {
		if (*iter == value) { return iter; }
	}
	return end;
}

int main()
{
	vector myVector{ 11, 22, 33, 22, 11 };

	auto it1{ myFind(begin(myVector), end(myVector), 22) };		    // type of it1 is vector<int>::iterator
	auto it2{ myFind(rbegin(myVector), rend(myVector), 22) };		// type of it2 is vector<int>::reverse_iterator

	if (it1 != end(myVector) && it2 != rend(myVector)) {
		cout << format("Found at position {} going forward.", distance(begin(myVector), it1)) << endl;
		cout << format("Found at position {} going backward.", distance(begin(myVector), --it2.base())) << endl;
	} else {
		cout << "Failed to find." << endl;
	}
}
