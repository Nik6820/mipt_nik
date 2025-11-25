#include <iostream>

struct subforwardlist {

    int data;

    subforwardlist* next;

};
// ваш код сюда идет
#include <random>
#include <chrono>
using std::cout;
using std::endl;

bool init(subforwardlist **sfl){
    *sfl = NULL;
    return true;
}
bool push_back(subforwardlist **sfl, int d){
    if (*sfl==NULL){
        subforwardlist* new_list = new subforwardlist;
        new_list->next=NULL;
        new_list->data=d;
        *sfl=new_list;
        return true;
    }
    subforwardlist* new_list = new subforwardlist;
    new_list->next = NULL;
    new_list->data = d;
    subforwardlist* tmp = *sfl;
    while (tmp->next!=NULL){
        tmp = tmp->next;
    }
    tmp->next = new_list;
    return true;
}

int pop_back(subforwardlist **sfl){
    if (*sfl == NULL){
        return 0;
    }
    int d;
    subforwardlist* tmp = *sfl;
    if (tmp->next == NULL){
        d=tmp->data;
        delete tmp;
        *sfl=NULL;
        return d;
    }
    while(tmp->next->next!=NULL){
        tmp=tmp->next;
    }
    d=tmp->next->data;
    delete tmp->next;
    tmp->next=NULL;
    return d;
}

bool push_forward(subforwardlist **sfl, int d){
    if (*sfl==NULL){
        subforwardlist* new_list = new subforwardlist;
        new_list->next=NULL;
        new_list->data=d;
        *sfl=new_list;
        return true;
    }
    subforwardlist* new_list = new subforwardlist;
    new_list->next = *sfl;
    new_list->data = d;
    *sfl = new_list;
    return true;
}

int pop_forward(subforwardlist **sfl){
    if (*sfl == NULL){
        return 0;
    }
    int d;
    subforwardlist* tmp = *sfl;
    if (tmp->next == NULL){
        d=tmp->data;
        delete tmp;
        *sfl=NULL;
        return d;
    }
    *sfl=tmp->next;
    d=tmp->data;
    delete tmp;
    return d;
}
bool push_where(subforwardlist **sfl, unsigned int where, int d){
    if (where==0){
        push_forward(sfl, d);
        return true;
    }
    if (*sfl==NULL){
        subforwardlist* new_list = new subforwardlist;
        new_list->next=NULL;
        new_list->data=d;
        *sfl=new_list;
        return true;
    }
    subforwardlist* new_list = new subforwardlist;
    new_list->next = NULL;
    new_list->data = d;
    subforwardlist* tmp = *sfl;
    unsigned int count=1;
    while (count < where){
        tmp = tmp->next;
        count++;
    }
    subforwardlist* lst = tmp;
    lst=lst->next;
    new_list->next = lst;
    tmp->next = new_list;
    return true;
}

int erase_where(subforwardlist **sfl, unsigned int where){
    if (where==0){
        return pop_forward(sfl);
    }
    if (*sfl == NULL){
        return 0;
    }
    int d;
    subforwardlist* tmp = *sfl;
    if (tmp->next == NULL){
        d=tmp->data;
        delete tmp;
        *sfl=NULL;
        return d;
    }
    unsigned int count=1;
    while (count < where){
        tmp = tmp->next;
        count++;
    }
    subforwardlist* lst = tmp->next->next;
    d=tmp->next->data;
    delete tmp->next;
    tmp->next=NULL;
    tmp->next=lst;
    return d;
}

void clear(subforwardlist  **sfl){
    while(pop_forward(sfl));
}

unsigned int size(subforwardlist  *sfl){
    if (sfl==NULL){
        return 0;
    }
    subforwardlist* new_list = new subforwardlist;
    new_list->next = NULL;
    subforwardlist* tmp = sfl;
    unsigned int count=0;
    while (tmp->next!=NULL){
        count++;
        tmp = tmp->next;
    }
    return count;
}
int main()
{
    subforwardlist *sv;
    init(&sv);

    push_back(&sv, 1);
    push_back(&sv, 2);
    push_back(&sv, 3);
    push_back(&sv, 4);
    push_back(&sv, 5);
    push_back(&sv, 6);
    push_back(&sv, 7);
    push_back(&sv, 8);
    push_back(&sv, 9);
    push_where(&sv, 4, 10);
    erase_where(&sv, 4);

    cout << size(sv);



    return 0;
}