#include <iostream>
#include <vector>
#include <string>

template<typename Comparator>
void sort(std::vector<int>& arr, Comparator cmp)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        for (size_t j = i+1; j < arr.size(); j++)
        {
            if(cmp(arr[j], arr[i]))
                std::swap(arr[j], arr[i]);
        }
        
    }
}

bool less(int lhs, int rhs)
{
    return lhs < rhs;
}

bool greater(int lhs, int rhs)
{
    return lhs > rhs;
}

// Functor - struct with operator ()
struct lessFunctor
{
    bool operator()(int a, int b) const
    {
        return a < b;
    }  
};

// Lambda function 
// -> return type, not required
// auto less = [] (int lhs, int rhs) -> bool
// {
//     return lhs < rhs;
// }

void print(const std::vector<int>& arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
    
}

// Template specialization
/*

*/
template<typename T>
void fun(const T obj)
{
    std::cout << "template func\n";
}

template<>
void fun(int num)
{
    std::cout << "int type specialization\n";
}

template<typename T>
struct Test
{
    void fun() {std::cout << "og template\n";}
    T obj;
};

template<>
struct Test<int>
{
    void fun() {std::cout << "int template\n";}
    int obj;
};

// std::optional - object of class, that holds an object, or is empty
// Moje da izpolzvam na proekta, za formulata, vmesto da durja hasValue kato flag

template<typename T>
class Option
{
public:
    Option() : value(), hasValue(false) {};
    Option(const T& value) : value(value), hasValue(true) {};

    template<typename U>
    Option(const U& otherValue) : value(value), hasValue(true) {};

    operator bool() const {return hasValue;}
    T& operator* {return value;}

    // Pishem go za da moje da go izpolzvame v konstantni obekti
    const T& operator* {return value;}

     T* operator->() (return &value;)
    const T* operator->() (return &value;)

private:
    T value;
    bool hasValue;
};


Option<int> findFirstGreater(const std::vector<int>& arr, int target)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        if(arr[i] > target)
            return Option<int>(arr[i]);
    }

    return Option<int>();
}

template<typename T>
void printOption(const Option<T>& optInt)
{
    if(optInt)
        std::cout << *optInt;
}


template<typename T>
class Option<T&>
{
public:
    Option() : value(nullptr) {};
    Option(const T& value) : value(&value) {};

    operator bool() {return value !=nullptr;}
    T& operator*() {return *value;}
    const T& operator*() {return *value;}

    T* operator->() (return value;)
    const T* operator->() (return value;)
private:
    T* value;
};

template<>
class Option<void>
{
public:
    operator bool() {return false;}
    void operator*() = delete;
};

/*
Move Semantics

- Po dobre e da ne se pishat na izpiti, zashtoto se vzima tochki ako sa napisani greshno
a ne nosqt dopylnitelni 

Rule of Zero
- kogato nqmame dinamichna pamet, ne pishem nishto

Rule of Three
- Cpy Ctor, Operator=, Destructor

Rule of Five
- Three + Move Ctor, Move Operator=

rvalue - vsichko drugo - 2, 2.f, "fmi"
lvalue - ako e promenliav/ima ime, moje da poema stoinosti

-----------------------------------------------------------------

r referencii - &&
std::move() -> preobrazuvai lvalue kum rvalue reference, samo castva == static_cast<int&&>
- move ne mesti nishto

-----------------------------------------------------------------

void move(Vector&& other)
{
    this->pArr = other.pArr;
    this->size = other.size;
    this->capacity = other.capacity;

    other.pArr = nullptr;
    other.size = other.capacity = 0 ;
}

Vector::Vector(Vector&& other)
{
    // Nujno e da izvikame std::move() zashtoto other veche ima ime -> ne e rvalue reference
    move(std::move(other));
}

Vector& Vector::operator=(Vector&& other)
{
    if(this != &other)
    {
        clean();
        move(std::move(other));
    }
}

this-> pArr = std::exchange(other.pArr, nullptr)

*/

/*
VAJNOOOOOOOOOOOOOO
template<typename T>
void wtf(T&& obj)
- NE E RVALUE REFERENCE

wtf(num) -> shte raboti


void intRef(int&& ref)

intRef(3) -> raboti
intRef(num) -> NE RABOTI
*/


void rvalueFun(int&& rval)
{
    std::cout << rval;
}

int main()
{
//     std::vector<int> arr = {5,4,2,1,3};
//     sort(arr, less);

//     print(arr);

//     fun(2.5f);
//     fun(2);

//     int num = 1;
//     Option<const int&>someInfRef = num;

//     Option<std::string> optString = "ref";

    rvalueFun(2);

    int num = 3;
    rvalueFun(std::move(num));
}