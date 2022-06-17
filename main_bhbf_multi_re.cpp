#include "bhbf_multi_re.h"
#include <chrono>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <unordered_set>

#define SETNUM 16
#define MAXN 100000
#define RATIO 12
#define K  4
std::string chars{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?"};
std::random_device rd;
std::mt19937 generator(rd());
vector<int> result[100000];
std::string rand_str(size_t length)
{
    const size_t char_size = chars.size();
    std::uniform_int_distribution<> random_int(0, char_size - 1);
    std::string output;
    for (size_t i = 0; i < length; ++i)
        output.push_back(chars[random_int(generator)]);
    return output;
}
void test_set()
{
    vector<pair<string, vector<int>>> data(MAXN);
    unordered_set<string> filter;
    double time = 0.0; //计时器

    for (int i = 0; i < MAXN; ++i)
    {
        string item;
        while (1)
        {
            item = rand_str(30);
            if (filter.find(item) == filter.end())
            {
                filter.insert(item);
                break;
            }
        }
        data[i].first = item;
        int num = i % 5 + 1;  //元素所在的集合的个数，1-5
        for (int j = 0; j < num; j++)
        {
            data[i].second.push_back((i + num * j) % SETNUM);
        }
        sort(data[i].second.begin(), data[i].second.end());
    }
    int err_cnt = 0;
    for (int r = 0; r < 3; r++) //三轮求交集
    {
        auto cc = new Bh_Bloom_Filter<int(MAXN * RATIO), SETNUM, K>();
        cc->init();
        for (int i = 0; i < MAXN; ++i)
        {
            cc->insert(data[i].first, data[i].second, r);
        }
        for (int i = 0; i < MAXN; ++i)
        {
            // if (i == 0)
            // {
            //     cout << i << ": ";
            //     for (int j = 0; j < data[i].second.size(); j++)
            //         cout << data[i].second[j] << " ";
            //     cout << endl;
            // }
            chrono::time_point<chrono::high_resolution_clock> t1 = chrono::high_resolution_clock::now();
            if (r == 0)
                result[i] = cc->query(data[i].first, r);
            // if (result != data[i].second){
            //     cout << i << endl;
            // }
            else
            {
                vector<int> temp1 = cc->query(data[i].first, r);
                vector<int> temp2;
                set_intersection(temp1.begin(), temp1.end(), result[i].begin(), result[i].end(), back_inserter(temp2));
                result[i].assign(temp2.begin(), temp2.end());
            }
            chrono::time_point<chrono::high_resolution_clock> t2 = chrono::high_resolution_clock::now();
            time += ((t2 - t1).count() / 1000000000.0); //转换为s
            if (r == 2)
                err_cnt += (result[i] != data[i].second);
        }
        delete cc;
    }
    double time_per_query = time * 1000000.0 / MAXN; //转换为微秒
    double error_rate = err_cnt * 1.0 / MAXN;
    cout << "Data size: " << MAXN << endl;
    cout << "Cell number/data size ratio: " << RATIO << endl;
    cout << "K: " << K << endl;

    cout << setiosflags(ios::fixed) << setprecision(5); //保留小数点后5位
    cout << "Error rate: " << error_rate << endl;
    cout << "Time per query: " << time_per_query << "us" << endl;

    // cout << "Error count: " << err_cnt << endl;
}

int main()
{
    test_set();

    return 0;
}