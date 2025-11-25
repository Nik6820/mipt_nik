#include <iostream>
using std::cout;
using std::cin;
using std::endl;
struct Sequence
{
    int size;    // количество чисел
    int* data;   // указатель на начало массива с числами
};
void separate_odd_even(const Sequence* input, Sequence** odd, Sequence** even){
    *odd = new Sequence;
    *even = new Sequence;
    (*odd)->size=0;
    (*even)->size=0;
    (*odd)->data = new int[input->size];
    (*even)->data = new int[input->size];
    for (int i = 0; i < input->size; i++)
    {
        if (input->data[i]%2==1)
        {
            (*odd)->data[(*odd)->size]=input->data[i];
            (*odd)->size++;
        }
        else{
            (*even)->data[(*even)->size]=input->data[i];
            (*even)->size++;
        }
    }
    
}
void clear(Sequence* s){
    delete [] s->data;
    delete s;
}
int main()
{
    Sequence input;
    cin >> input.size;
    input.data = new int[input.size];
    for (int i = 0; i < input.size; i++)
        cin >> input.data[i];
    Sequence *odd, *even;
    separate_odd_even(&input, &odd, &even);
    for (int i = 0; i < odd->size; i++)
        cout << odd->data[i] << " ";
    cout << endl;
    for (int i = 0; i < even->size; i++)
        cout << even->data[i] << " ";    
    cout << endl;
    clear(odd);
    clear(even);
    delete[] input.data;
    return 0;
}