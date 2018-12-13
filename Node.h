#include <iostream>
#include <vector>
using namespace std;

class Node{
    int color;
    vector<long long int> quota;
    
public:
    Node* left;
    Node* right;
    Node() : color(0), left(NULL), right(NULL) {}
    Node(long long int value, int n) : color(value), left(NULL), right(NULL) 
    {
        for(int i = 0; i < n; i++)
            quota.push_back(0);
    }
    void setColor(const int x) {this->color = x;}
    vector<long long int> getQuota() {return quota;}
    long long int getQuotaAt(int pos) {return quota[pos];}
    void setQuotaValue(int pos, long long int key) {quota[pos] = key;}
    void incQuota(int pos) {quota[pos]++;}
    void decQuota(int pos) {quota[pos]--;}
    long long int getSumOfQuota() 
    {
        long long int sum_of_elems = 0;
        for(std::vector<long long int>::iterator it = quota.begin(); it != quota.end(); ++it)
            sum_of_elems += *it;
        return sum_of_elems;
    }
    void printQuota() 
    {
        int size = quota.size();
        cout << "Quota of " << size << ":";
        for(int i = 0; i < size; i++)
        {
            cout << " " << quota[i];
        }
        cout << " Total: " << getSumOfQuota() << endl;
    }
    void makeGraph(int h, Node* parent)
    {
        if(h == 1)
            return;
        parent -> left = new Node(0, parent->quota.size());
        parent -> right = new Node(0, parent->quota.size());
        makeGraph(h - 1, parent -> left);
        makeGraph(h - 1, parent -> right);  
    }
    void printGraph(int h, Node* root)
    {
        for (int i=1; i<=h; i++)
        {
            printGivenLevel(i, root);
            cout << "\n";
        }
    }
     
    /* Print nodes at a given level */
    void printGivenLevel(int level, Node* root)
    {
        if (root == NULL)
            return;
        if (level == 1)
            cout << root->color;
        else if (level > 1)
        {
            printGivenLevel(level-1, root->left);
            printGivenLevel(level-1, root->right);
        }
    }

    ~Node()
    {
        delete left;
        delete right;
    }
};