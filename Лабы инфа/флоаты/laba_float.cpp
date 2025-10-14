#include <chrono>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;

int rand_uns(int min, int max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() / 1e6;
}

void binary_vision(unsigned int a)
{
    for (int i=0; i<32; i++)
    {
        cout<<((a>>31-i)&1);
        a<<=(i+1);
        a>>=(i+1);
    }
    cout<<endl;
}

double f(double x)
{
    return x*x;
}
union F
{
    unsigned int i;
    float f;
} f1;
int main()
{
    ofstream ff("test.csv", ios::out);
    f1.f = 16500000.0;
    /* //для второго задания
    for(int i=1; i<40; i++)
    {
        f1.f*=10;
        cout<<f1.f<<" ";
        binary_vision(f1.i);
    }
    */
    /* //третье задание
    f1.f = 16500000.0;
    while((f1.f+1)-f1.f>=1){ //16777216.00-16777215.00=0
        cout<<f1.f<<endl;
        f1.f++;
    }
    */
    double lr=0.0, mr=0.0, rr=0.0;
    for (int j=1; j<=100; j++)
    {
        double lr=0.0, mr=0.0, rr=0.0;
        for(int i=1; i<=j; i++)
        {
            lr += f(i-1);
            mr += f(i-0.5);
            rr += f(i);
        }
        ff << lr/j/j/j << " ";
        ff << mr/j/j/j << " ";
        ff << rr/j/j/j << " ";
        ff << endl;/*
        cout<<lr/j/j/j<<endl;
        cout<<mr/j/j/j<<endl;
        cout<<rr/j/j/j<<endl;
        cout<<endl;*/
    }
}
