#include <iostream>
using namespace std;
typedef int Elem;
class NodeList{
private:
    //insert Node declaration
    struct Node{
        Elem elem; //elem value
        Node *prev;
        Node *next;
    };
public:
    //insert Iterator declaration
    class Iterator{
    public:
        // reference to the element
        Elem &operator*(){
            return v->elem;
        }
        bool operator ==(const Iterator &p)const{
            return v==p.v;
        }
        bool operator !=(const Iterator &p) const{
            return v != p.v;
        }
        Iterator &operator ++(){
            v= v->next;
            return  *this;
        }
        Iterator &operator --(){
            v= v->prev;
            return *this;
        }
        friend class NodeList;// give NodeList access
    private:
        // Iterator private members
        Node *v; // pointer to the node
        //constrcutor is private so that
        //onyl NodeList is allowed to create new iterators
        Iterator(Node *u){
            v=u;
        }
    };
public:
    // NodeList
    NodeList(){
        n=0;
        header= new Node;
        trailer= new Node;
        header->next= trailer;
        trailer ->prev =header;
    }
    int size() const {
        return n;
    }
    bool empty() const{
        return(n==0);
    }
    Iterator begin() const{
        return Iterator(header->next);
    }
    Iterator end() const{
        return Iterator(trailer);
    }
    void insertFront(const Elem &e){
        insert(begin(),e);
    }
    void insertBack(const Elem &e){
        insert(end(),e);
    }
    //insert e before p
    void insert(const Iterator &p,const Elem &e){
        Node *w= p.v; //p's node
        Node *u= w->prev; //p's predecessor
        Node *v= new Node;
        v->elem= e;
        //link in v before w
        v->next= w;
        w->prev=v;
        //link in v after u
        v->prev=u;
        u->next=v;
        n++;
    }
    // delete node
    void eraseFront();
    void eraseBack();
    void erase(const Iterator &p);

private:
    // NodeList Private Members
    int n;// number of items
    Node *header; // head-of-list sentinel
    Node *trailer; // tail-of-list-sentinel
// end of NodeList class
};
// NodeSequence is child of NodeList
class NodeSequesnce:public NodeList{
public:
    //get position from index
    Iterator atIndex(int i) const{
        Iterator p= begin();
        for(int j=0;j<i;j++){
            ++p;
        }
        return p;
    }
    //get index from position
    int indexOf(const Iterator &p) const{
        Iterator q= begin();
        int j=0;
        while(q !=p){
            ++q;
            ++j;
        }
        return j;
    }
};
//
void bubbleSort1(NodeSequesnce &S) {
    int n= S.size();
    for(int i=0;i<n; i++){
        for(int j=1;j<n-i;j++){
            NodeSequesnce::Iterator prec= S.atIndex(j-1); //predecessor
            NodeSequesnce::Iterator succ= S.atIndex(j); // successor
            if(*prec> *succ){
                int tmp=*prec;
                *prec=*succ;
                *succ=tmp;
            }
        }
    }
}
void bubbleSort2(NodeSequesnce &S){
    int n=S.size();
    for(int i=0;i<n;i++){
        NodeSequesnce::Iterator prec=S.begin();
        for(int j=1;j<n-i;j++){
            NodeSequesnce::Iterator succ=prec;
            ++succ;
            if(*prec>*succ){
                int tmp= *prec;
                *prec=*succ;
                *succ=tmp;
            }
            ++prec;
        }
    }
}
int main() {
Elem *numbers= new Elem[4]{10,60,70,34};
NodeSequesnce data;
for(int i=0;i<4;i++){
    data.insertFront(numbers[i]);
}
    bubbleSort2(data);
for(NodeList::Iterator p= data.begin(); p!=data.end();++p){
    cout<<*p<<endl;
}

}
