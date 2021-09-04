export module KeyValuePair_nodule;

import <utility>;
import <iostream>;
import <string>;

export template <typename Key, typename Value>
class KeyValuePair
{
private:
	Key m_key;
	Value m_value;
public:
	KeyValuePair(const Key& key, const Value& value)
		: m_key{key}, m_value{value}
	{}

	const Key& getKey() const { return m_key; }
	void setKey(const Key& newKey) { m_key = newKey; }

	const Value& getValue() const { return m_value; }
	void setValue(const Value& newValue) { m_value = newValue; }
};

export template<>
class KeyValuePair<const char*, const char*>
{
private:
	std::string m_key;
	std::string m_value;
public:
	KeyValuePair(const char* key, const char* value)
		: m_key{ key }, m_value{ value }
	{}

	const std::string& getKey() const { return m_key; }
	void setKey(const char* newKey) { m_key = newKey; }

	const std::string& getValue() const { return m_value; }
	void setValue(const char* newValue) { m_value = newValue; }
};

export template<typename Key, typename Value>
void printKeyValuePair(const KeyValuePair<Key, Value>& pair)
{
	std::cout << "Key: " << pair.getKey() << ", value: "
		<< pair.getValue() << std::endl;
}