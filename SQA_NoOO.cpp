/*
    Ethan O'Dell
    7/11/2018
    --------------------------------------------------------------
    Non OO Split Quota Approach (SQA) - Best Case: 25

    Normal SQA but without Nodes or Recursion (For space complexity)
    Meant to be a very lightweight SQA for cases higher than 25 (OO SQA Limit)
    
    Process:
    1. Create Quota
    2. Paint Quota (Non OO)
       a. Dec the 1 value
       b. Balance algo
    3. Put two calls to Paint on the stack (Hope no overflow)
*/

/* LIBRARIES */
#include <iostream>
#include <vector>
#include <stack>
#include <math.h> 
#include <algorithm>
using namespace std;

/* RESOURCES */
stack< vector<int> > paintStack;
long long int countList = 0;

/* DEFINITIONS */
void createQuota(vector<int>& startQuota, int n);
void printQuota(vector<int>& quota);
vector<int> copyQuotaByValue(vector<int>& quota);
vector<int> quotaSort(vector<int> quota);
vector<vector<int> > balance(vector<int>& quota);
void paintGraphCorrectly(vector<int>& quota);

/* FUNCTIONS */
void createQuota(vector<int>& startQuota, int n)
{
    for(int i = 0; i < n; i++)
    {
        startQuota.push_back(1);
    }
    startQuota[0] = 1;
    if(n > 1)
    {
        int total = (pow(2,n) - 2);
        int e = floor(total / (n - 1));
        for(int i = 1; i < n; i++)
            startQuota[i] = e;
        int diff = total - (e*(n-1));
        for(int i = 1; i <= diff; i++)
            startQuota[i]++;
    }
}

vector<int> copyQuotaByValue(vector<int>& quota)
{
    vector<int> copyQuota;
    for(vector<int>::iterator it = quota.begin(); it != quota.end(); ++it)
        copyQuota.push_back(*it);
    return copyQuota;
}

vector<int> quotaSort(vector<int> quota)
{
    vector<int> sortedQuota = copyQuotaByValue(quota);
    sort(sortedQuota.begin(), sortedQuota.end());
    while(*quota.begin() == 0)
        sortedQuota.erase(sortedQuota.begin());
    return sortedQuota;
}

int findAndZero(vector<int> &copy, int key)
{
    int index = 0;
    vector<int>::iterator begin = copy.begin();
    vector<int>::iterator end = copy.end();

    while(begin < end)
    {
        if(*begin == key)
            break;
        index++;
        begin++;
    }

    if(begin != end)
    {
        copy[index] = 0;
        return index;
    }
    return -1;
}

vector<vector<int> > balance(vector<int>& quota)
{
    vector<int> sortedQuota = quotaSort(quota);
    if(sortedQuota.size() > 0)
    {
        vector<int> copyQuota = copyQuotaByValue(quota);
        int leftStarting = 0;
        int sortedQuotaTotal = sortedQuota[leftStarting];
        int leftQuotaTotal = 1;
        vector<int> leftQuota = copyQuota;
        leftQuota[findAndZero(copyQuota, sortedQuota[leftStarting])] = 1;
        if(sortedQuota[leftStarting] != 2)
        {
            leftStarting++;
            leftQuota[findAndZero(copyQuota, sortedQuota[leftStarting])] = sortedQuota[leftStarting] - 1; 
            sortedQuotaTotal += sortedQuota[leftStarting];
            leftQuotaTotal += sortedQuota[leftStarting] - 1;
        }
        leftStarting++;
        int size = sortedQuota.size();
        for(int i = leftStarting; i < size; i++)
        {
            sortedQuotaTotal += sortedQuota[i];
            int nextLeftQuotaValue;
            if((sortedQuotaTotal / 2) - leftQuotaTotal > 1)
                nextLeftQuotaValue = (sortedQuotaTotal / 2) - leftQuotaTotal;
            else
                nextLeftQuotaValue = sortedQuota[i]/2;
            leftQuota[findAndZero(copyQuota, sortedQuota[i])] = nextLeftQuotaValue;
            leftQuotaTotal += nextLeftQuotaValue;
        }
        size = leftQuota.size();
        vector<int> rightQuota(copyQuotaByValue(quota));
        for(int i = 0; i < size; i++)
            rightQuota[i] = quota[i] - leftQuota[i];
        vector<vector<int> > returnQuotas;
        returnQuotas.push_back(leftQuota);
        returnQuotas.push_back(rightQuota); 
        return returnQuotas;
    }
}

void paintGraphCorrectly(vector<int>& quota)
{
    int size = quota.size();
    for(int i = 0; i < size; i++)
    {
        if(quota[i] == 1)
        {
            quota.erase(quota.begin() + i);
            countList++;
            break;
        }
    }
    if(size > 1)
    {
        vector<vector<int> > returnQuotas = balance(quota);
        paintStack.push(returnQuotas[0]);
        paintStack.push(returnQuotas[1]);
    }
}

void printQuota(vector<int>& quota)
{
    vector<int>::iterator i;
    cout << "[ ";
    for(i = quota.begin(); i < quota.end(); i++)
    {
        cout << *i << " "; 
    }
    cout << "]" << endl;
}

int main()
{
    int caseSize = 30;
    for(int i = 1; i <= caseSize; i++)
    {
        vector<int> startQuota;
        
        createQuota(startQuota, i);
        paintStack.push(startQuota);
        cout << "Case " << i << ":" << endl;
        printQuota(startQuota);
        while(!paintStack.empty())
        {
            vector<int> top = paintStack.top();
            paintStack.pop();
            paintGraphCorrectly(top);
        }
        cout << countList << endl;
        countList = 0;
    }
    return 0;
}