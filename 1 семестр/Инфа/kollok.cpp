/*using namespace std;
#include <iostream>

int main()
{
    int a[3][2]={{1,2},{3,4},{5,6}};
    int b[2][3];

    for (int i=0; i<3; i++){
        for(int j=0; j<2; j++){
            b[j][i]=a[i][j];
        }
    }



    for (int i=0; i<3; i++)
    {
        for(int j=0; j<2; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<'\n';
    }
    cout<<'\n';
    for (int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            cout<<b[i][j]<<" ";
        }
        cout<<'\n';
    }
}*/
/*
#include <iostream>
using std::cout;
using std::endl;
const int N = 10;
int main()
{
    int res, N = 10;
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < N; i++)
        res += a[i];
    cout << res;
    return 0;
}*/
#include <iostream>
using std::cout;
using std::endl;
int main()
{
    int min = -5, max = 5;
    for (unsigned int i = min; i < max; i++)
    {
        for (unsigned int i = min; i < max; i++)
            cout << '*';
        cout << endl;
    }
    return 0;
}
