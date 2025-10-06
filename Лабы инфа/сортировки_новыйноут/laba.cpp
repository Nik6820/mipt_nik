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

void Bubblesort(int* n, int i) {
    for (int k = 0; k < i - 1; k++)
    {
        for (int l = 0; l < i - k - 1; l++)
        {
            if (n[l] > n[l + 1])
            {
                int t = n[l];
                n[l] = n[l + 1];
                n[l + 1] = t;
            }
        }
    }
}

void Shakersort(int* n, int i) {
    for (int k = 0; k < i / 2; k++)
    {
        bool flag = true;
        for (int l = k; l < i - k - 1; l++)
        {
            if (n[l] > n[l + 1])
            {
                int t = n[l];
                n[l] = n[l + 1];
                n[l + 1] = t;
                flag = false;
            }
        }
        for (int o = i - k - 1; o > k; o--)
        {
            if (n[o] < n[o - 1])
            {
                int t = n[o];
                n[o] = n[o - 1];
                n[o - 1] = t;
                flag = false;
            }
        }
        if (flag)
            break;
    }
}
void Insertsort(int* n, int i) {
    for (int y = 0; y < i - 1; y++)
    {
        int mx = n[0];
        int ind = 0;
        for (int z = 0; z < i - y; z++)
        {
            if (n[z] >= mx)
            {
                mx = n[z];
                ind = z;
            }
        }
        int q = n[i - y - 1];
        n[i - y - 1] = n[ind];
        n[ind] = q;
    }
}
void Quicksort(int* arr, int left, int right) {
    if (left >= right) return;

    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    int t = arr[i+1];
    arr[i+1] = arr[right];
    arr[right] = t;

    Quicksort(arr, left, i);
    Quicksort(arr, i + 2, right);
}
void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int t = arr[i];
        arr[i] = arr[largest];
        arr[largest] = t;
        heapify(arr, n, largest);
    }
}
void Heapsort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int t = arr[0];
        arr[0] = arr[i];
        arr[i] = t;
        heapify(arr, i, 0);
    }
}
void mrg(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[20000], rightArr[20000];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void Mergesort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        Mergesort(arr, left, mid);
        Mergesort(arr, mid + 1, right);

        mrg(arr, left, mid, right);
    }
}
int main()
{
    ofstream f("Mergediff.csv", ios::out);
    int a[20000];
    int b1[20000];
    int b2[20000];
    int b3[20000];
    for (int i = 0; i < 3000; i++) //заполнение массива
    {
        int x = rand_uns(-100000, 100000);
        a[i] = x;
    }
    for (int i = 1; i < 3000; i++)
    {
        int b[20000];
        for (int j = 0; j < i; j++)
        {
            b1[j] = a[j];
            b2[j] = j;
            b3[j] = i-j;
        }
        cout << i << '\n';

        double start = get_time();
        //Quicksort(b1,0, i-1);
        //Bubblesort(b1, i);
        Mergesort(b1, 0, i-1);
        double ed = get_time();
        f << ed - start << " ";



        start = get_time();
        //Heapsort(b2, i);
        //Shakersort(b2, i);
        Mergesort(b2, 0, i-1);
        ed = get_time();
        f << ed - start << " ";



        start = get_time();
        //Mergesort(b3, 0, i-1);
        //Insertsort(b3, i);
        Mergesort(b3, 0, i-1);
        ed = get_time();
        f << ed - start << " ";


        f << endl;
    }

}
