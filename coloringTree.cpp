/*
    Ethan O'Dell
    02/09/2018
    -------------------------------------------------------------------
    Split Quota Approach

This algorithm solves the coloring problem by creating a quota, a list containing the number of Nodes that need to be colored for each color. 
The whole quota is created by giving the first color a value of one, and giving every other color a value of floor(((2^n) - 2) / (n - 1)). 
If any amount is leftover, increment each color from 2 to the nth color, but only incrementing the second and third color if the calculated value is even. 
Given the number of levels of a full binary tree, n. 
The list is traversed looking for a 1 in the quota and coloring the root in that color. 
From there, if the root has children, divide the root quota between the two children.
Dividing the root quota is done by finding an acceptable root for the left tree and using the same process to find a suitable root for right subtree. 
After suitable roots are found, divide the remaining nodes between each subtree.
Once subtrees have filled quotas, verify that the quotas are correct by checking if the total Nodes in the left and right subtree quotas are equal, 
    the total for each color equals the total Nodes in the root quota and that no value in the sub-quotas is larger than the lowest level.
If this is incorrect then decrement a non-root value from the larger quota and increment the same value from the smaller quota until either the maximum 
    possible is reached on the smaller side or until the two quotas hold the same number of nodes. If the maximum value is reached and imbalance still exists, 
    then find the next non-root value and repeat the process.
Once both subtrees have correct quotas, repeat from step 1 for the left child and the right child.
		
1 Determining a proper root is done by going through the quotas of the child and root and looking for a value that has not been assigned in the child’s quota that has a remainder that can fit in his brother’s tree. Which is determined by comparing the total minus one if it is less than or equal to 2^(level - 1)
2 Division is done through by dividing the parent quota value by 2 and putting the remainder into the other child’s quota. Then alternating between children and doing this process until all colors are assigned.
*/
#include <math.h> 
#include <algorithm>
#include "Node.h"

const int MAX_SIZE = 25;
int countList[MAX_SIZE]; 


/*
* Print the count list to show the load of each color
*/
void printCountList(int size)
{
    for(int i = 0; i < size; i++)
        cout << "Color " << i << ": " << countList[i] << endl;
}

/*
* Gives a perfect quota to any root passed 
*
* Parameters: Node* which is the root of the tree to be colored
*/
void createQuota(Node* root)
{
    root->setQuotaValue(0,1);
    int size = root->getQuota().size();
    if(root->getQuota().size() > 1)
    {
        long long int total = (pow(2,size) - 2);
        long long int e = floor(total / (size - 1) );
        for(int i = 1; i < size; i++)
            root->setQuotaValue(i, e);
        long long int diff = total - (e*(size-1));
        for(int i = 1; i <= diff; i++)
            root->incQuota(i);
    }
}

////////////////////////////////////   NEW CODE ///////////////////////////////////////////////////

void printVector(vector<long long int> quota)
{
    long long int sum_of_elems = 0;
    for(vector<long long int>::iterator it = quota.begin(); it != quota.end(); ++it)
        sum_of_elems += *it;
    int size = quota.size();
    cout << "Quota of " << size << ":";
    for(int i = 0; i < size; i++)
    {
        cout << " " << quota[i];
    }
    cout << " Total: " << sum_of_elems << endl;
}

vector<long long int> copyQuotaByValue(vector<long long int> quota)
{
    vector<long long int> copyQuota;
    for(vector<long long int>::iterator it = quota.begin(); it != quota.end(); ++it)
    {
        copyQuota.push_back(*it);
    }
    return copyQuota;
}

vector<long long int> quotaSort(vector<long long int> quota)
{
    vector<long long int> sortedQuota = quota;
    sort(sortedQuota.begin(), sortedQuota.end());
    while(sortedQuota[0] == 0)
        sortedQuota.erase(sortedQuota.begin());
    return sortedQuota;
}

int find(vector<long long int>::iterator begin, vector<long long int>::iterator end, long long int key)
{
    int index = 0;
    while(begin < end)
    {
        if(*begin == key)
        {
            return index;
        }
        index++;
        begin++;
    }
    return -1;
}

int findAndZero(vector<long long int> &copy, long long int key)
{
    int index = find(copy.begin(), copy.end(), key);
    if(index >= 0)
        copy[index] = 0;
    return index;
}

// As all things should be
void balance(Node* root, vector<long long int> sortedQuota)
{
    if(sortedQuota.size() > 0)
    {
        vector<long long int> copyQuota = copyQuotaByValue(root->getQuota());
        int leftStarting = 0;
        long long int sortedQuotaTotal = sortedQuota[leftStarting];
        long long int leftQuotaTotal = 1;
        root->left->setQuotaValue(findAndZero(copyQuota, sortedQuota[0]), 1);
        if(sortedQuota[0] != 2)
        {
            leftStarting++;
            root->left->setQuotaValue(findAndZero(copyQuota, sortedQuota[leftStarting]), sortedQuota[leftStarting] - 1);
            sortedQuotaTotal += sortedQuota[leftStarting];
            leftQuotaTotal += sortedQuota[leftStarting] - 1;
        }
        leftStarting++;
        int size = sortedQuota.size();
        for(int i = leftStarting; i < size; i++)
        {
            sortedQuotaTotal += sortedQuota[i];
            long long int nextLeftQuotaValue;
            if((sortedQuotaTotal / 2) - leftQuotaTotal > 1)
                nextLeftQuotaValue = (sortedQuotaTotal / 2) - leftQuotaTotal;
            else
                nextLeftQuotaValue = sortedQuota[i]/2;
            root->left->setQuotaValue(findAndZero(copyQuota, sortedQuota[i]), nextLeftQuotaValue);
            leftQuotaTotal += nextLeftQuotaValue;
        }
        size = root->getQuota().size();
        for(int i = 0; i < size; i++)
            root->right->setQuotaValue(i, root->getQuotaAt(i) - root->left->getQuotaAt(i));
    }
}

void paintGraphCorrectly(Node* root)
{
    int size = root->getQuota().size();
    for(int i = 0; i < size; i++)
    {
        if(root->getQuotaAt(i) == 1)
        {
            root->setColor(i);
            root->decQuota(i);
            countList[i]++;
            break;
        }
    }
    if(root->left != NULL)
    {
        
        balance(root, quotaSort(root->getQuota()));
        // cout << "Root: ";
        // root->printQuota();
        // cout << "Left: ";
        // root->left->printQuota();
        // cout << "Right: ";
        // root->right->printQuota();
        paintGraphCorrectly(root->left);
        paintGraphCorrectly(root->right);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int totalCasesPassed = 0;
    for(int i = 1; i <= MAX_SIZE; i++)
    {
        cout << "CASE: " << i << endl;
        Node* root = new Node(0,i);//Make a root node
        root->makeGraph(i, root);
        createQuota(root);
        long long int total = root->getSumOfQuota();
        // root->printQuota();
        for(int j = 0; j <i; j++)
            countList[j] = 0;
        paintGraphCorrectly(root);

        long long int totalColored = 0;
        for(int j = 0; j < i; j++)
            totalColored += countList[j];
        float percentRight = (float(totalColored)/total) * 100;
        if(totalColored/total)
        { 
            // totalCasesPassed++;
            cout << "Score of " << totalColored << "/" << total << " = " << percentRight << "%\n";
        } 
        else
            cout << "Failed at case: " << i << endl; 
        // printCountList();
        // root->printGraph(MAX_SIZE, root);
    }
    return 0;
}