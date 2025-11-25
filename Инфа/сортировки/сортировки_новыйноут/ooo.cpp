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
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}


int main()
{
    ofstream f("n2wO3.csv", ios::out);
    int a[20000];
    int b1[20000];
    int b2[20000];
    int b3[20000];
    for(int i=0; i<10000; i++) //заполнение массива
    {
        int x=rand_uns(-100000, 100000);
        a[i]=x;
    }
    for(int i=1; i<10000; i++)
    {
        int b[20000];
        for(int j=0; j<i; j++)
        {
            b1[j]=a[j];
            b2[j]=a[j];
            b3[j]=a[j];
        }
        cout<<i<<'\n';
        //start bubble
        double start=get_time();
        for(int k=0; k<i-1; k++)
        {
            for(int l=0; l<i-k-1; l++)
            {
                if(b1[l]>b1[l+1])
                {
                    int t=b1[l];
                    b1[l]=b1[l+1];
                    b1[l+1]=t;
                }
            }
        }
        double ed = get_time();
        f << ed-start  << " ";
        //end bubble
        f<<endl;
    }

}
