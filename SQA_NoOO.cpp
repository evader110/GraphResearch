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
vector<int> startQuota;
stack< vector<int> > paintStack;
int countList = 0;

/* FUNCTIONS */
void createQuota(int n)
{
    for(int i = 0; i < n; i++)
        startQuota.push_back(1);
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

vector<int> copyQuotaByValue(vector<int> quota)
{
    vector<int> copyQuota;
    for(vector<int>::iterator it = quota.begin(); it != quota.end(); ++it)
        copyQuota.push_back(*it);
    return copyQuota;
}

vector<int> quotaSort(vector<int> quota)
{
    vector<int> sortedQuota = quota;
    sort(sortedQuota.begin(), sortedQuota.end());
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
        copy.erase(begin);
        return index;
    }

    return -1;
}

vector< vector<int> > balance(vector<int> quota, vector<int> sortedQuota)
{
    if(sortedQuota.size() > 0)
    {
        vector<int> copyQuota = copyQuotaByValue(quota);
        int leftStarting = 0;
        int sortedQuotaTotal = sortedQuota[leftStarting];
        int leftQuotaTotal = 1;
        vector<int> leftQuota = quota;
        leftQuota[findAndZero(copyQuota, sortedQuota[0])] = 1;
        if(sortedQuota[0] != 2)
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
        size = quota.size();
        vector<int> rightQuota = quota;
        for(int i = 0; i < size; i++)
            rightQuota[i] = quota[i] - leftQuota[i];
        vector<int> returnQuotas[2];
        returnQuotas[0] = leftQuota;
        returnQuotas[1] = rightQuota; 
        return returnQuotas;
    }
}

void paintGraphCorrectly(vector<int> quota)
{

    int size = quota.size();
    for(int i = 0; i < size; i++)
    {
        if(quota[i] == 1)
        {
            quota.erase(i);
            countList++;
            break;
        }
    }

    if(size <= 1)
    {
        vector< vector<int> > returnQuotas = balance(quota, quotaSort(root->getQuota()));
        paintStack.push(returnQuotas[0]);
        paintStack.push(returnQuotas[1]);

    }
}

int main()
{
    int caseSize = 4;
    createQuota(caseSize);
    paintStack.push(startQuota);
    while(!paintStack.empty())
    {
        vector<int> top = paintStack.top();
        paintStack.pop();
        paintGraphCorrectly(top);
    }
    return 0;
}