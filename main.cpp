#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class Image{
private:
    Mat p2img;
public:
    Image();
    ~Image();
    bool Load(char* imgfile);
};

struct node{
    Image* img;
    node* next;
};

class LinkedList {
    private:
        node* head=nullptr;
        int listLength=0;
    public:
        LinkedList();
        ~LinkedList();
        bool insertNode( node* newNode, int position );
        bool removeNode( int position );
        void printListLength();
};

LinkedList::~LinkedList()
{
    while(head!=nullptr)
    {
        node* temp=head->next;
        delete head;
        head=temp;
    }
}
bool LinkedList::insertNode(node* newNode, int position)
{
    if (position<0 || listLength<(position-1)) return false;

    node* temp=head;
    node* prev=head;
    while (position-->0)
    {
         prev=temp;
         temp=temp->next;

    }
    node* temp2=new node;
    temp2->img=newNode->img;
    temp2->next=temp;
    if (temp == nullptr){
        temp = temp2;
    } else
    {
        prev->next=temp2;
    }
    listLength++;
    return true;
}
bool LinkedList::removeNode(int position){
    if (position<0 || listLength<position) return false;
    node* temp=head;
    while (--position>0)
    {
        temp=temp->next;
    }
    node* deltemp=temp->next;
    temp->next=deltemp->next;
    delete deltemp;
    listLength--;
    return true;
}
void LinkedList::printListLength(){
    cout << "List length:" << listLength << endl;
}

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

