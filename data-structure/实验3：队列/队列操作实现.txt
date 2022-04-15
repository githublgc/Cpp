#include <iostream>
using namespace std;

typedef struct Qnode{
    int data;
    struct Qnode *next;
};

typedef struct LQueue{
    Qnode *front;
    Qnode *rear;
};

void initQueue(LQueue *q){
    q->front = q->rear = (Qnode *)malloc(sizeof(Qnode));
    q->front->next = NULL;
}

int empty(LQueue *t){
    return t->front->next == t->rear;
}

void push(LQueue *t, int x){
    Qnode *s = (Qnode *)malloc(sizeof(Qnode));
    s->data = x;
    s->next = NULL;
    t->rear->next = s;
    t->rear = s;
}

void pop(LQueue *t){
    if(empty(t)){
        cout << "LQueue is empty,can't pop.\n";
        return;
    }
    Qnode *q = t->front->next;
    t->front->next = q->next;
    free(q);
    if(t->rear == NULL)
        t->rear = t->front;
}

int getFront(LQueue *t){
    return t->front->next->data;
}

int getRear(LQueue *t){
    return t->rear->data;
}

int getSize(LQueue *t){
    Qnode *q = t->front->next;
    int k = 0;
    while(q){
        k++;
        q = q->next;
    }
    return k;
}

void printQueue(LQueue *t){
    Qnode *q = t->front->next;
    while(q){
        cout << q->data << " ";
        q = q->next;
    }
    cout << "\n";
}
int main(){
    LQueue L;
    initQueue(&L);
    cout << "Push data to Queue...\n";
    push(&L,2);
    push(&L,5);
    push(&L,4);
    push(&L,3);
    push(&L,6);
    push(&L,8);
    push(&L,10);
    push(&L,11);
    cout << "Push finished.\n";
    cout << "You have pushed such data:";
    printQueue(&L);
    cout << "Pop data out of Queue...\n";
    pop(&L);
    cout << "Pop finished.\n";
    cout << "Now the Queue have such data:";
    printQueue(&L);
    cout << "Get Queue's front data:" << getFront(&L) << endl;
    cout << "Get Queue's rear data:" << getRear(&L) << endl;
    cout << "Get Queue's size:" << getSize(&L) << endl;
    pop(&L);
    pop(&L);
    pop(&L);
    cout << "After poped 3 times:";
    printQueue(&L);
    cout << "Judge the Queue is null or not(0 means not null,others means null):" << empty(&L) << endl;
    pop(&L);
    pop(&L);
    pop(&L);
    pop(&L);
    cout << "After poped 4 times:";
    printQueue(&L);
    cout << "Judge the Queue is null or not(0 means not null,others means null):" << empty(&L) << endl;

    return 0;
}