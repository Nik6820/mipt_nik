#include <iostream>
using std::cout;
using std::endl;
int main()
{
    int *p = new int[10];
    p[10] = 5; // p[-1000] ошибок не выдает)))
    return 0;
}
