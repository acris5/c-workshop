#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

class Image{
private:

public:
    Mat p2img;
    Image()=default;
    ~Image() = default;
    Image(const Image& copy)// copy constructor
    {
        copy.p2img.copyTo(p2img);
    }
    Image& operator=(const Image& copy)// copy assignment operator
    {
        if(this != &copy)
        {
            copy.p2img.copyTo(p2img);
        }
        return *this;
    }

    Image (Image&& temp)=default;// move constructor
    Image& operator=(Image&& temp)=default;// move assignment operator
    bool Load(const char* imgfile);
};

bool Image::Load(const char* imgfile)
{
    p2img=imread(imgfile, CV_LOAD_IMAGE_COLOR);
    if(! p2img.data ) return false;
    else
        return true;
}

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

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main()
{
    //cout << "Hello World!" << endl;

    //namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.

    string dir = string("dinos");
    LinkedList dinos;
    vector<string> files = vector<string>();
    getdir(dir,files);
    for (unsigned int i = 0;i < files.size();i++) {
            node temp;
            temp.img->Load(files[i].c_str());
            dinos.insertNode(&temp,1);
        }


    //imshow( "Display window", image );                   // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}

