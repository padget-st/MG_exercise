//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//
//#ifdef _DEBUG
//    #ifndef DBG_NEW
//        #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//        #define new DBG_NEW
//    #endif
//#endif //_DEBUG

#include <iostream>
#include <vector>
#include <format>

class Dull //: public std::enable_shared_from_this<Dull>
{
private:
    int m_number;
public:
    Dull(int number) : m_number{ number }
    {
        std::cout << "\nConstructor - " << m_number << '\n';
    }

    int get() const
    {
        return m_number;
    }

    //std::shared_ptr<Dull> get_shared()
    //{
    //    return shared_from_this();
    //}

    ~Dull()
    {
        std::cout << "\nDestructor - " << m_number << '\n';
    }
};

char** allocateXYarray(std::size_t xDim, std::size_t yDim)
{
    char** xArray{ new char* [xDim] };
    for (std::size_t i{}; i < xDim; i++)
    {
        xArray[i] = new char[yDim];
    }
    return xArray;
}

//stack-based arrays only!
template<std::size_t N>
void doubleStack(int(&userArray)[N])
{
    for (std::size_t i{}; i < N; i++)
    {
        userArray[i] *= 2;
    }
}

wchar_t* toCaps(const wchar_t* text)
{
    std::size_t length{};
    while (text[length] != '\0') { length++; }

    wchar_t* newText{ new wchar_t[length] };

    for (std::size_t i{0}; i != length + 1; i++)
    {
        *(newText + i) = toupper(*(text + i));
    }

    return newText;
}

//manual allocator
int* my_alloc(int value)
{
    std::cout << '\n' << __func__ << '\n';
    return  new int {value};
}

//manual deallocator
void my_free(int* p)
{
    std::cout << '\n' << __func__ << '\n';
    delete p;
}

void newDeleteCheck()
{
    int** handler{ nullptr };
    handler = new int* { nullptr };
    *handler = new int{ 7 };
    std::cout << handler << " " << *handler << " " << **handler;
    delete* handler;
    *handler = nullptr;
    delete handler;
    handler = nullptr;
    delete handler;
}

void mallocFreeCheck()
{
    Dull* mallocDull{ (Dull*)malloc(sizeof(Dull)) };
    Dull* newDull{ new/*(std::nothrow)*/ Dull{1} };

    *mallocDull = Dull{ 3 };

    std::cout << "malloc: " << mallocDull->get() << '\n';
    std::cout << "new(nothrow): ";
    if (newDull)
    {
        std::cout << newDull->get() << '\n';
    }
    else
    {
        std::cout << "nullptr\n";
    }

    mallocDull->~Dull();
    free(mallocDull);
    delete newDull;
}

void stackBasedArrayCheck()
{
    int arr[]{ 1, 2, 3, 4 };
    doubleStack(arr);
    std::cout << arr[0] << " " << arr[3];
    int* freeArr{ new int[] {1, 2, 3, 4} };
    //doubleStack(freeArr); doesn't compile!
    std::cout << freeArr[0];
    delete[] freeArr;
}

void wideCharCheck()
{
    const wchar_t* string{ L"Hello, world!" };
    auto newString{ toCaps(string + 7) };

    for (std::size_t i{}; newString[i] != '\0'; i++)
    {
        std::cout << (char)*(newString + i);
    }
    //delete[] newString;
}

void memoryLeak()
{
    int* leakPtr{ new int{} };
    leakPtr = new int{ 1 };
}

void uniqueArrayCheck()
{
    auto arrUniquePtr{ std::make_unique<int[]>(5) };
    arrUniquePtr[3] = 4;
    std::cout << '\n' << arrUniquePtr[3];
}

void myAllocatorUniquePtrCheeck()
{
    std::unique_ptr<int, decltype(&my_free)> myDelUniquePtr{ my_alloc(42), my_free };
    std::shared_ptr<int> myDelSharedPtr{ my_alloc(42), my_free };
}

void sharedFromThisCheck()
{
    /*auto ptr1{ std::make_shared<Dull>(1) };
    auto ptr2{ ptr1->get_shared() };*/
}

void dataTransferTest()
{
    std::vector<int> v_source{ 1, 2, 3, 4, 5 };
    std::vector<int> v_destination(5);

    auto source_data{ reinterpret_cast<char*>(v_source.data()) };
    auto destination_data{ reinterpret_cast<char*>(v_destination.data()) };

    for (std::size_t i{}; i < v_source.size() * sizeof(int); i++)
    {
        *(destination_data + i) = *(source_data + i);
    }

    for (auto& elem : v_destination)
    {
        std::cout << elem << " ";
    }
}

void exercise7_1and2()
{
    std::size_t size{ 10 };
    std::vector<int> tempVector;

    for (std::size_t i{}; i < size; i++)
    {
        tempVector.push_back(i);
    }

    //tempVector[tempVector.size()-1] = 99;
    tempVector.back() = 99;

    for (const auto& elem : tempVector)
    {
        std::cout << elem << " ";
    }
}

//Excercise 7_3
class Point3D
{
private:
    int m_x{}, m_y{}, m_z{};
public:
    Point3D(int x, int y, int z)
        : m_x{ x }, m_y{ y }, m_z{ z }
    {}

    Point3D()
    {}

    void setX(int newX) { m_x = newX; }
    int getX() const { return m_x; }

    void setY(int newY) { m_y = newY; }
    int getY() const { return m_y; }

    void setZ(int newZ) { m_z = newZ; }
    int getZ() const { return m_z; }
};

void printPoint3D(const Point3D& point)
{
    std::cout << std::format("[{}, {}, {}]",
        point.getX(), point.getY(), point.getZ());
}

void exercise7_3()
{
    auto pointPtr{ std::make_unique<Point3D>(2, 2, 6) };
    printPoint3D(*pointPtr);
}

//fills the string 'str' with m's
void exercise7_4(std::string& str)
{
    for (auto& elem : str)
    {
        elem = 'm';
    }
}

int main()
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::string testStr{ "Banana" };
    exercise7_4(testStr);
    std::cout << testStr;
}

