#include <cstdio>
#include <list> //https://en.cppreference.com/w/cpp/container/list
#include <functional> //https://en.cppreference.com/w/cpp/utility/functional/function


// Example of two template functions
template <class T>
void printValueToStdout(T& value)
{
    printf("%d\n", value);
}

template <class T>
void increaseValue(T& value)
{
    value += 1;
}



// Good approach when public method 'applyFunctionToItemsInParallelMode' launches private one 'auxRecParMethod'
template <class T>
class MyList: public std::list<T> 
{
    MyList() {} a
    void auxRecParMethod(auto iterator, const std::function<void(T&)> & givenFunc)
    {
        if(iterator == this->end())
            return;
        
        #pragma omp task // In each task: 'iterator', givenFunc are firstprivate variables
            this->auxRecParMethod(++iterator, givenFunc);
            
        givenFunc(*iterator); // Applying given function
    }
    
public:
    // This constructor just applies the consturctor of parent class
    MyList(std::initializer_list<T> initValuesList) : std::list<T>(initValuesList) {}
    
    // Get constant 'function pointer' reference to any fucntion
    // That returns void and has only one argument "T &"
    void applyFunctionToItemsInParallelMode(const std::function<void(T&)> & givenFuncion) {
        #pragma omp parallel
            #pragma omp single
                this->auxRecParMethod(this->begin(), givenFuncion);
    }
    
    ~MyList() {}
};



int main()
{
    MyList smallList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    smallList.applyFunctionToItemsInParallelMode(increaseValue<int>);
    smallList.applyFunctionToItemsInParallelMode(printValueToStdout<int>);
    
    return 0;
}
