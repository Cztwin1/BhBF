#include "bh_bloom_filter.h"
#include <chrono>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <unordered_set>

#define SETNUM 16
#define MAXN 100000
#define RATIO 4
#define K 4
std::string chars{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?"};
std::random_device rd;
std::mt19937 generator(rd());
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
    vector<pair<string, uint32_t>> data(MAXN);
    unordered_set<string> filter;
    double time = 0.0; //计时器
    for (int i = 0; i < MAXN; ++i)
    {
        string item;
        while (1)
        {
            item = rand_str(30);  //生成长为30的字符串作为key
            if (filter.find(item) == filter.end())
            {
                filter.insert(item);
                break;
            }
        }
        data[i].first = item;
        data[i].second = i % SETNUM;  //所属集合
    }
    auto cc = new Bh_Bloom_Filter<int(MAXN * RATIO), SETNUM, K>();

    cc->init();

    for (int i = 0; i < MAXN; ++i)
    {
        cc->insert(data[i].first, data[i].second);
    }

    int err_cnt = 0;
    for (int i = 0; i < MAXN; ++i)
    {
        chrono::time_point<chrono::high_resolution_clock> t1 = chrono::high_resolution_clock::now();
        int result = cc->query(data[i].first);
        chrono::time_point<chrono::high_resolution_clock> t2 = chrono::high_resolution_clock::now();
        time += ((t2 - t1).count() / 1000000000.0); //转换为s
        err_cnt += (result != data[i].second);
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