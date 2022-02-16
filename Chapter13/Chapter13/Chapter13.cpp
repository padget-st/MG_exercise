#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <vector>

void testIO()
{
    std::cout << "\nEnter numbers:\n";

    if (!std::cin)
    {
        std::cerr << "Standard input is in a bad state!";
        return;
    }

    int sum{};

    while (!std::cin.bad())
    {
        int number{};
        std::cin >> number;

        if (std::cin)
        {
            sum += number;
        }
        else if(std::cin.eof())
        {
            break;
        }
        else if(std::cin.fail())
        {
            std::cin.clear();
            std::string badToken{};
            std::cin >> badToken;
            std::cerr << "Warning! Bad input: " << badToken << std::endl;
        }
    }
    std::cout << "The sum is " << sum;
}

std::string readName(std::istream& in)
{
    std::string name{};
    int next{};
    while (in)
    {
        next = in.get();
        if (!in || next == std::char_traits<char>::eof())
        {
            break;
        }
        name += static_cast<char>(next);
    }
    return name;
}

/*std::string readName(std::istream& in)
{
    std::string name;
    char next{};
    while (in.get(next))
    {
        name += next;
    }
    return name;
}*/

void getNameAndNumber()
{
    std::string name{};
    int number{};
    char ch{};
    std::cin >> std::noskipws;
    while (std::cin >> ch)
    {
        if (isdigit(ch))
        {
            std::cin.unget();
            if (std::cin.fail())
            {
                std::cerr << "unget() failed";
            }
            break;
        }
        name += ch;
    }

    if (std::cin)
    {
        std::cin >> number;
    }

    if (!std::cin)
    {
        std::cerr << "failed while reading";
        return;
    }

    std::cout << name << " " << number;
}

void testGetline()
{
    const size_t buffSize{ 10 };
    char buffer[buffSize]{ 0 };
    std::cin.getline(buffer, buffSize);
    std::cout << buffer;
}

void testStrStream()
{
    std::stringstream outStream;

    while (std::cin)
    {
        std::string nextToken;
        std::cout << "Next token: ";
        std::cin >> nextToken;
        if (!std::cin || nextToken == "done")
        {
            break;
        }
        outStream << nextToken << "\t";
    }
    std::cout << "Result: " << outStream.str() << std::endl;

    std::cout << "The first two tokens: ";

    std::string token{};

    for (size_t i{}; i < 2 && outStream >> token; i++)
    {
        std::cout << token << " ";
    }
}

void testDir()
{
    std::filesystem::path p1{ "C:/windows/win.ini" };
    std::filesystem::directory_entry dir{ p1 };
    if (dir.exists() && dir.is_regular_file())
    {
        std::cout << "File size: " << dir.file_size();
    }
}

void testDirStruct(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path))
    {
        return;
    }

    std::filesystem::directory_iterator begin{ path };
    std::filesystem::directory_iterator end{};
    for (auto iter{ begin }; begin != end; ++iter)
    {
        const std::string spacer(0 * 2, ' ');

        auto& entry{ *iter };

        if (std::filesystem::is_regular_file(entry))
        {
            std::cout << spacer << "File: " << entry.path().string() << " " << std::filesystem::file_size(entry) << std::endl;
        }
        else if (std::filesystem::is_directory(entry))
        {
            std::cout << spacer << "Dir: " << entry.path().string() << std::endl;
        }
    }

}

class Person
{
public:
    // Two-parameter constructor automatically creates initials and
    // delegates the work to the three-parameter constructor.
    Person(std::string firstName, std::string lastName)
        : Person{ std::move(firstName), std::move(lastName),
        std::format("{}{}", firstName[0], lastName[0]) }
    {
    }

    Person() = default;

    Person(std::string firstName, std::string lastName, std::string initials)
        : m_firstName{ std::move(firstName) }
        , m_lastName{ std::move(lastName) }
        , m_initials{ std::move(initials) }
    {
    }

    const std::string& getFirstName() const { return m_firstName; }
    void setFirstName(std::string firstName) { m_firstName = std::move(firstName); }

    const std::string& getLastName() const { return m_lastName; }
    void setLastName(std::string lastName) { m_lastName = std::move(lastName); }

    const std::string& getInitials() const { return m_initials; }
    void setInitials(std::string initials) { m_initials = std::move(initials); }

    void output() const
    {
        std::cout << m_firstName << " " << m_lastName << " (" << m_initials << ")" << std::endl;
    }

    void output(std::ostream& out) const
    {
        if (out)
        {
            out << m_firstName << " " << m_lastName << " (" << m_initials << ")" << std::endl;
        }

        if (out.fail())
        {
            std::cerr << "ostream failed";
        }
    }

    //// Only this single line of code is needed to add support
    //// for all six comparison operators.
    [[nodiscard]] auto operator<=>(const Person&) const = default;

private:
    std::string m_firstName;
    std::string m_lastName;
    std::string m_initials;
};

void testPersonOutput() //exercise 1 and 2
{
    Person pers("john", "petrucci");
    //pers.output();
    pers.output(std::cout);

    std::ofstream outFile{ "Person.pr" };
    pers.output(outFile);

    std::ostringstream outStr;
    pers.output(outStr);
    std::cout << outStr.str();
}

class Database
{
public:
    virtual ~Database() = default;

    void add(const Person& person)
    {
        m_data.push_back(person);
    }

    void save(std::filesystem::path& dir)
    {
        for (auto& person : m_data)
        {
            std::filesystem::path file{ dir };
            file /= person.getInitials();
            file += ".person";
            std::ofstream outFile{ file, std::ios_base::trunc };
            if (outFile)
            {
                    outFile << std::quoted(person.getFirstName())
                        << std::quoted(person.getLastName())
                        << std::quoted(person.getInitials())
                        << std::endl;
            }
        }
    }

    void load(std::filesystem::path& dir)
    {
        std::filesystem::directory_iterator begin{ dir };
        std::filesystem::directory_iterator end{};
        for (auto iter{ begin }; iter != end; iter++)
        {
            auto& entry{ *iter };
            if (!entry.path().has_extension()
                || entry.path().extension() != ".person")
            {
                continue;
            }
            loadFile(entry);
        }
    }

    void loadFile(std::filesystem::path file)
    {
        std::ifstream inFile{ file };
        if (inFile)
        {
            while (inFile)
            {
                std::string line{};
                std::getline(inFile, line);

                if (line.empty())
                {
                    continue;
                }

                std::istringstream inLine{ line };
                std::string firstName, lastName, initials;
                inLine >> std::quoted(firstName) >> std::quoted(lastName) >> std::quoted(initials);

                if (inLine.bad())
                {
                    std::cerr << "Reading error. Wrong data." << std::endl;
                    continue;
                }
                m_data.push_back(Person(firstName, lastName, initials));
            }
        }
    }

    void clear()
    {
        m_data.clear();
    }

    void outputAll() const
    {
        for (auto& person : m_data)
        {
            person.output();
        }
    }

private:
    std::vector<Person> m_data;
};

int main()
{
    Person person1("John", "Petrucci Jr.");
    Person person2("Steve", "Vai");
    Person person3("Joe", "Satriani");

    Database db;
    db.add(person1);
    db.add(person2);
    db.add(person3);

    std::filesystem::path dir{ "D:/exer/MG_exercise/Chapter13/Chapter13" };

    db.save(dir);

    db.clear();
    db.load(dir);
    db.outputAll();
}
