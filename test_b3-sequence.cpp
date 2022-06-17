#include <iostream>
#include <stdio.h>
using namespace std;
#define NUM 32
int sequence[50] = {1, 14, 34, 103, 119, 124, 133, 288, 405, 619,
                    944, 1265, 1729, 2428, 3242, 3694, 4902, 7060, 8499, 10903,
                    12862, 16361, 17445, 23994, 29730, 35034, 39238, 43787, 53754, 57983,
                    70389, 79980, 95587, 112063, 120126, 129823, 160914, 181296, 193779, 210446,
                    245521, 283467, 306447, 325880, 375834, 413231, 458307, 506306, 546900, 612212};
bool mark[2000000] = {0};
int main()
{
    freopen("out.txt", "w", stdout);
    for (int i = 0; i < NUM; i++)
        for (int j = i; j < NUM; j++)
            for (int k = j; k < NUM; k++)
            {
                int temp = sequence[i] + sequence[j] + sequence[k];
                // if (temp == 1836636)
                // {
                //     cout << temp << " " << i << " " << j << " " << k << endl;
                //     return 0;
                // }
                if (mark[temp])
                {
                    cout << temp << " " << i << " " << j << " " << k << endl;
                    goto wrong;
                }
                else
                {
                    mark[temp] = true;
                    cout << temp << " " << i << " " << j << " " << k << endl;
                }
            }
    // for (int i = 0; i < NUM; i++)
    //     for (int j = i; j < NUM; j++)
    //     {
    //         int temp = sequence[i] + sequence[j];
    //         if (mark[temp])
    //         {
    //             goto wrong;
    //         }
    //         else
    //         {
    //             mark[temp] = true;
    //             cout << temp << " " << i << " " << j << endl;
    //         }
    //     }
    cout << "right" << endl;
    return 0;
    
wrong:
    cout << "wrong" << endl;
    return 0;
}