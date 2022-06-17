#include <cstring>
#include <iostream>
using namespace std;
int sequence[200] = {0};
bool mark[24000000] = {0};
bool mark2[24000000] = {0};
bool possible(int i, int j)
{
    for (int k = 0; k < i; k++)
        for (int l = k; l < i; l++)
        {
            int temp = sequence[k] + sequence[l] + j;
            if (mark[temp])
            {
                memset(mark2, 0, sizeof(mark2));
                return false;
            }
            else
            {
                mark2[temp] = 1;
            }
        }
    for (int k = 0; k < i; k++)
    {
        int temp = j * 2 + sequence[k];
        if (mark[temp])
        {
            memset(mark2, 0, sizeof(mark2));
            return false;
        }
        else
        {
            mark2[temp] = 1;
        }
    }
    int temp = j * 3;
    if (mark[temp])
    {
        memset(mark2, 0, sizeof(mark2));
        return false;
    }
    else
    {
        mark2[temp] = 1;
    }
    for (int k = 0; k < 24000000; k++)
        if (mark2[k])
            mark[k] = mark2[k];
    memset(mark2, 0, sizeof(mark2));
    return true;
}

int main()
{
    sequence[0] = 1;
    cout << sequence[0] << " ";
    sequence[1] = 14;
    cout << sequence[1] << " ";
    sequence[2] = 34;
    cout << sequence[2] << " ";
    sequence[3] = 103;
    cout << sequence[3] << " ";
    sequence[4] = 119;
    cout << sequence[4] << " ";
    for (int i = 0; i <= 4; i++)
        for (int j = i; j <= 4; j++)
            for (int k = j; k <= 4; k++)
            {
                int temp = sequence[i] + sequence[j] + sequence[k];
                mark[temp] = 1;
            }
    for (int i = 5; i < 200; i++)
    {
        for (int j = sequence[i - 1] + 1;; j++)
        {
            if (possible(i, j))
            {
                sequence[i] = j;
                cout << sequence[i] << ", ";
                if (i % 10 == 9)
                    cout << endl;
                break;
            }
        }
    }
    return 0;
}