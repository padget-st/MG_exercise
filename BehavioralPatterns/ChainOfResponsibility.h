#pragma once
#include <regex>
#include <iostream>
#include <string>
#include <memory>
#include <charconv>

class StringValidator
{
public:
	virtual ~StringValidator() = default;
	virtual StringValidator* setNext(StringValidator* nextValidator) = 0;
	virtual std::string validate(const std::string&) = 0;
};

class BaseValidator : public StringValidator
{
protected:
	StringValidator* m_next{ nullptr };
public:
	virtual ~BaseValidator() { delete m_next; }

	StringValidator* setNext(StringValidator* nextValidator) override
	{
		m_next = nextValidator;
		return m_next;
	}

	virtual std::string validate(const std::string& testString) override
	{
		if (m_next)
		{
			return m_next->validate(testString);
		}
		return "Success";
	}
};

class NotEmptyValidator : public BaseValidator
{
public:
	NotEmptyValidator() = default;
	std::string validate(const std::string& testString) override
	{
		std::cout << "Checking if empty...\n";
		if (testString.empty())
		{
			return "Please, enter a value\n";
		}

		return  BaseValidator::validate(testString);
	}
};

class LenghtValidator : public BaseValidator
{
private:
	int m_minlength{ 0 };
public:
	LenghtValidator(int length) : m_minlength{ length } {};

	std::string validate(const std::string& testString) override
	{
		std::cout << "Checking string length...\n";
		if (testString.length() < m_minlength)
		{
			return "Please, enter a value longer than "
				+ std::to_string(m_minlength) + "\n";
		}

		return  BaseValidator::validate(testString);
	}
};

class RegexValidator : public BaseValidator
{
private:
	std::string m_patternName;
	std::string m_regexString;
public:
	RegexValidator(std::string patternName, std::string regexString)
		: m_patternName{ std::move(patternName) }, m_regexString{ std::move(regexString) }
	{}

	std::string validate(const std::string& testString) override
	{
		std::cout << "Checking regex match...\n";
		if (!std::regex_match(testString, std::regex(m_regexString)))
		{
			return "Doesn't match the format " + m_patternName + "\n";
		}

		return  BaseValidator::validate(testString);
	}
};