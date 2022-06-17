#include "Murmurhash_3.h"
#include "hash.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;
struct bhbf
{
    int sum;
    int count;
};
template <uint32_t cell_num, uint32_t class_num, int k> //k是哈希个数
class Bh_Bloom_Filter
{
public:
    vector<int> sequence = {1, 14, 34, 103, 119, 124, 133, 288, 405, 619,
                            944, 1265, 1729, 2428, 3242, 3694};
    int seed[7] = {5, 7, 11, 13, 31, 37, 61};
    unordered_map<int, int> decode1 = {{1, 0}, {14, 1}, {34, 2}, {103, 3}, {119, 4}, {124, 5}, {133, 6}, {288, 7}, {405, 8}, {619, 9}, {944, 10}, {1265, 11}, {1729, 12}, {2428, 13}, {3242, 14}, {3694, 15}};
    unordered_map<int, vector<int>> decode2 = {{2, {0, 0}}, {15, {0, 1}}, {35, {0, 2}}, {104, {0, 3}}, {120, {0, 4}}, {125, {0, 5}}, {134, {0, 6}}, {289, {0, 7}}, {406, {0, 8}}, {620, {0, 9}}, {945, {0, 10}}, {1266, {0, 11}}, {1730, {0, 12}}, {2429, {0, 13}}, {3243, {0, 14}}, {3695, {0, 15}}, {28, {1, 1}}, {48, {1, 2}}, {117, {1, 3}}, {133, {1, 4}}, {138, {1, 5}}, {147, {1, 6}}, {302, {1, 7}}, {419, {1, 8}}, {633, {1, 9}}, {958, {1, 10}}, {1279, {1, 11}}, {1743, {1, 12}}, {2442, {1, 13}}, {3256, {1, 14}}, {3708, {1, 15}}, {68, {2, 2}}, {137, {2, 3}}, {153, {2, 4}}, {158, {2, 5}}, {167, {2, 6}}, {322, {2, 7}}, {439, {2, 8}}, {653, {2, 9}}, {978, {2, 10}}, {1299, {2, 11}}, {1763, {2, 12}}, {2462, {2, 13}}, {3276, {2, 14}}, {3728, {2, 15}}, {206, {3, 3}}, {222, {3, 4}}, {227, {3, 5}}, {236, {3, 6}}, {391, {3, 7}}, {508, {3, 8}}, {722, {3, 9}}, {1047, {3, 10}}, {1368, {3, 11}}, {1832, {3, 12}}, {2531, {3, 13}}, {3345, {3, 14}}, {3797, {3, 15}}, {238, {4, 4}}, {243, {4, 5}}, {252, {4, 6}}, {407, {4, 7}}, {524, {4, 8}}, {738, {4, 9}}, {1063, {4, 10}}, {1384, {4, 11}}, {1848, {4, 12}}, {2547, {4, 13}}, {3361, {4, 14}}, {3813, {4, 15}}, {248, {5, 5}}, {257, {5, 6}}, {412, {5, 7}}, {529, {5, 8}}, {743, {5, 9}}, {1068, {5, 10}}, {1389, {5, 11}}, {1853, {5, 12}}, {2552, {5, 13}}, {3366, {5, 14}}, {3818, {5, 15}}, {266, {6, 6}}, {421, {6, 7}}, {538, {6, 8}}, {752, {6, 9}}, {1077, {6, 10}}, {1398, {6, 11}}, {1862, {6, 12}}, {2561, {6, 13}}, {3375, {6, 14}}, {3827, {6, 15}}, {576, {7, 7}}, {693, {7, 8}}, {907, {7, 9}}, {1232, {7, 10}}, {1553, {7, 11}}, {2017, {7, 12}}, {2716, {7, 13}}, {3530, {7, 14}}, {3982, {7, 15}}, {810, {8, 8}}, {1024, {8, 9}}, {1349, {8, 10}}, {1670, {8, 11}}, {2134, {8, 12}}, {2833, {8, 13}}, {3647, {8, 14}}, {4099, {8, 15}}, {1238, {9, 9}}, {1563, {9, 10}}, {1884, {9, 11}}, {2348, {9, 12}}, {3047, {9, 13}}, {3861, {9, 14}}, {4313, {9, 15}}, {1888, {10, 10}}, {2209, {10, 11}}, {2673, {10, 12}}, {3372, {10, 13}}, {4186, {10, 14}}, {4638, {10, 15}}, {2530, {11, 11}}, {2994, {11, 12}}, {3693, {11, 13}}, {4507, {11, 14}}, {4959, {11, 15}}, {3458, {12, 12}}, {4157, {12, 13}}, {4971, {12, 14}}, {5423, {12, 15}}, {4856, {13, 13}}, {5670, {13, 14}}, {6122, {13, 15}}, {6484, {14, 14}}, {6936, {14, 15}}, {7388, {15, 15}}};
    unordered_map<int, vector<int>> decode3 = {{3, {0, 0, 0}}, {16, {0, 0, 1}}, {36, {0, 0, 2}}, {105, {0, 0, 3}}, {121, {0, 0, 4}}, {126, {0, 0, 5}}, {135, {0, 0, 6}}, {290, {0, 0, 7}}, {407, {0, 0, 8}}, {621, {0, 0, 9}}, {946, {0, 0, 10}}, {1267, {0, 0, 11}}, {1731, {0, 0, 12}}, {2430, {0, 0, 13}}, {3244, {0, 0, 14}}, {3696, {0, 0, 15}}, {29, {0, 1, 1}}, {49, {0, 1, 2}}, {118, {0, 1, 3}}, {134, {0, 1, 4}}, {139, {0, 1, 5}}, {148, {0, 1, 6}}, {303, {0, 1, 7}}, {420, {0, 1, 8}}, {634, {0, 1, 9}}, {959, {0, 1, 10}}, {1280, {0, 1, 11}}, {1744, {0, 1, 12}}, {2443, {0, 1, 13}}, {3257, {0, 1, 14}}, {3709, {0, 1, 15}}, {69, {0, 2, 2}}, {138, {0, 2, 3}}, {154, {0, 2, 4}}, {159, {0, 2, 5}}, {168, {0, 2, 6}}, {323, {0, 2, 7}}, {440, {0, 2, 8}}, {654, {0, 2, 9}}, {979, {0, 2, 10}}, {1300, {0, 2, 11}}, {1764, {0, 2, 12}}, {2463, {0, 2, 13}}, {3277, {0, 2, 14}}, {3729, {0, 2, 15}}, {207, {0, 3, 3}}, {223, {0, 3, 4}}, {228, {0, 3, 5}}, {237, {0, 3, 6}}, {392, {0, 3, 7}}, {509, {0, 3, 8}}, {723, {0, 3, 9}}, {1048, {0, 3, 10}}, {1369, {0, 3, 11}}, {1833, {0, 3, 12}}, {2532, {0, 3, 13}}, {3346, {0, 3, 14}}, {3798, {0, 3, 15}}, {239, {0, 4, 4}}, {244, {0, 4, 5}}, {253, {0, 4, 6}}, {408, {0, 4, 7}}, {525, {0, 4, 8}}, {739, {0, 4, 9}}, {1064, {0, 4, 10}}, {1385, {0, 4, 11}}, {1849, {0, 4, 12}}, {2548, {0, 4, 13}}, {3362, {0, 4, 14}}, {3814, {0, 4, 15}}, {249, {0, 5, 5}}, {258, {0, 5, 6}}, {413, {0, 5, 7}}, {530, {0, 5, 8}}, {744, {0, 5, 9}}, {1069, {0, 5, 10}}, {1390, {0, 5, 11}}, {1854, {0, 5, 12}}, {2553, {0, 5, 13}}, {3367, {0, 5, 14}}, {3819, {0, 5, 15}}, {267, {0, 6, 6}}, {422, {0, 6, 7}}, {539, {0, 6, 8}}, {753, {0, 6, 9}}, {1078, {0, 6, 10}}, {1399, {0, 6, 11}}, {1863, {0, 6, 12}}, {2562, {0, 6, 13}}, {3376, {0, 6, 14}}, {3828, {0, 6, 15}}, {577, {0, 7, 7}}, {694, {0, 7, 8}}, {908, {0, 7, 9}}, {1233, {0, 7, 10}}, {1554, {0, 7, 11}}, {2018, {0, 7, 12}}, {2717, {0, 7, 13}}, {3531, {0, 7, 14}}, {3983, {0, 7, 15}}, {811, {0, 8, 8}}, {1025, {0, 8, 9}}, {1350, {0, 8, 10}}, {1671, {0, 8, 11}}, {2135, {0, 8, 12}}, {2834, {0, 8, 13}}, {3648, {0, 8, 14}}, {4100, {0, 8, 15}}, {1239, {0, 9, 9}}, {1564, {0, 9, 10}}, {1885, {0, 9, 11}}, {2349, {0, 9, 12}}, {3048, {0, 9, 13}}, {3862, {0, 9, 14}}, {4314, {0, 9, 15}}, {1889, {0, 10, 10}}, {2210, {0, 10, 11}}, {2674, {0, 10, 12}}, {3373, {0, 10, 13}}, {4187, {0, 10, 14}}, {4639, {0, 10, 15}}, {2531, {0, 11, 11}}, {2995, {0, 11, 12}}, {3694, {0, 11, 13}}, {4508, {0, 11, 14}}, {4960, {0, 11, 15}}, {3459, {0, 12, 12}}, {4158, {0, 12, 13}}, {4972, {0, 12, 14}}, {5424, {0, 12, 15}}, {4857, {0, 13, 13}}, {5671, {0, 13, 14}}, {6123, {0, 13, 15}}, {6485, {0, 14, 14}}, {6937, {0, 14, 15}}, {7389, {0, 15, 15}}, {42, {1, 1, 1}}, {62, {1, 1, 2}}, {131, {1, 1, 3}}, {147, {1, 1, 4}}, {152, {1, 1, 5}}, {161, {1, 1, 6}}, {316, {1, 1, 7}}, {433, {1, 1, 8}}, {647, {1, 1, 9}}, {972, {1, 1, 10}}, {1293, {1, 1, 11}}, {1757, {1, 1, 12}}, {2456, {1, 1, 13}}, {3270, {1, 1, 14}}, {3722, {1, 1, 15}}, {82, {1, 2, 2}}, {151, {1, 2, 3}}, {167, {1, 2, 4}}, {172, {1, 2, 5}}, {181, {1, 2, 6}}, {336, {1, 2, 7}}, {453, {1, 2, 8}}, {667, {1, 2, 9}}, {992, {1, 2, 10}}, {1313, {1, 2, 11}}, {1777, {1, 2, 12}}, {2476, {1, 2, 13}}, {3290, {1, 2, 14}}, {3742, {1, 2, 15}}, {220, {1, 3, 3}}, {236, {1, 3, 4}}, {241, {1, 3, 5}}, {250, {1, 3, 6}}, {405, {1, 3, 7}}, {522, {1, 3, 8}}, {736, {1, 3, 9}}, {1061, {1, 3, 10}}, {1382, {1, 3, 11}}, {1846, {1, 3, 12}}, {2545, {1, 3, 13}}, {3359, {1, 3, 14}}, {3811, {1, 3, 15}}, {252, {1, 4, 4}}, {257, {1, 4, 5}}, {266, {1, 4, 6}}, {421, {1, 4, 7}}, {538, {1, 4, 8}}, {752, {1, 4, 9}}, {1077, {1, 4, 10}}, {1398, {1, 4, 11}}, {1862, {1, 4, 12}}, {2561, {1, 4, 13}}, {3375, {1, 4, 14}}, {3827, {1, 4, 15}}, {262, {1, 5, 5}}, {271, {1, 5, 6}}, {426, {1, 5, 7}}, {543, {1, 5, 8}}, {757, {1, 5, 9}}, {1082, {1, 5, 10}}, {1403, {1, 5, 11}}, {1867, {1, 5, 12}}, {2566, {1, 5, 13}}, {3380, {1, 5, 14}}, {3832, {1, 5, 15}}, {280, {1, 6, 6}}, {435, {1, 6, 7}}, {552, {1, 6, 8}}, {766, {1, 6, 9}}, {1091, {1, 6, 10}}, {1412, {1, 6, 11}}, {1876, {1, 6, 12}}, {2575, {1, 6, 13}}, {3389, {1, 6, 14}}, {3841, {1, 6, 15}}, {590, {1, 7, 7}}, {707, {1, 7, 8}}, {921, {1, 7, 9}}, {1246, {1, 7, 10}}, {1567, {1, 7, 11}}, {2031, {1, 7, 12}}, {2730, {1, 7, 13}}, {3544, {1, 7, 14}}, {3996, {1, 7, 15}}, {824, {1, 8, 8}}, {1038, {1, 8, 9}}, {1363, {1, 8, 10}}, {1684, {1, 8, 11}}, {2148, {1, 8, 12}}, {2847, {1, 8, 13}}, {3661, {1, 8, 14}}, {4113, {1, 8, 15}}, {1252, {1, 9, 9}}, {1577, {1, 9, 10}}, {1898, {1, 9, 11}}, {2362, {1, 9, 12}}, {3061, {1, 9, 13}}, {3875, {1, 9, 14}}, {4327, {1, 9, 15}}, {1902, {1, 10, 10}}, {2223, {1, 10, 11}}, {2687, {1, 10, 12}}, {3386, {1, 10, 13}}, {4200, {1, 10, 14}}, {4652, {1, 10, 15}}, {2544, {1, 11, 11}}, {3008, {1, 11, 12}}, {3707, {1, 11, 13}}, {4521, {1, 11, 14}}, {4973, {1, 11, 15}}, {3472, {1, 12, 12}}, {4171, {1, 12, 13}}, {4985, {1, 12, 14}}, {5437, {1, 12, 15}}, {4870, {1, 13, 13}}, {5684, {1, 13, 14}}, {6136, {1, 13, 15}}, {6498, {1, 14, 14}}, {6950, {1, 14, 15}}, {7402, {1, 15, 15}}, {102, {2, 2, 2}}, {171, {2, 2, 3}}, {187, {2, 2, 4}}, {192, {2, 2, 5}}, {201, {2, 2, 6}}, {356, {2, 2, 7}}, {473, {2, 2, 8}}, {687, {2, 2, 9}}, {1012, {2, 2, 10}}, {1333, {2, 2, 11}}, {1797, {2, 2, 12}}, {2496, {2, 2, 13}}, {3310, {2, 2, 14}}, {3762, {2, 2, 15}}, {240, {2, 3, 3}}, {256, {2, 3, 4}}, {261, {2, 3, 5}}, {270, {2, 3, 6}}, {425, {2, 3, 7}}, {542, {2, 3, 8}}, {756, {2, 3, 9}}, {1081, {2, 3, 10}}, {1402, {2, 3, 11}}, {1866, {2, 3, 12}}, {2565, {2, 3, 13}}, {3379, {2, 3, 14}}, {3831, {2, 3, 15}}, {272, {2, 4, 4}}, {277, {2, 4, 5}}, {286, {2, 4, 6}}, {441, {2, 4, 7}}, {558, {2, 4, 8}}, {772, {2, 4, 9}}, {1097, {2, 4, 10}}, {1418, {2, 4, 11}}, {1882, {2, 4, 12}}, {2581, {2, 4, 13}}, {3395, {2, 4, 14}}, {3847, {2, 4, 15}}, {282, {2, 5, 5}}, {291, {2, 5, 6}}, {446, {2, 5, 7}}, {563, {2, 5, 8}}, {777, {2, 5, 9}}, {1102, {2, 5, 10}}, {1423, {2, 5, 11}}, {1887, {2, 5, 12}}, {2586, {2, 5, 13}}, {3400, {2, 5, 14}}, {3852, {2, 5, 15}}, {300, {2, 6, 6}}, {455, {2, 6, 7}}, {572, {2, 6, 8}}, {786, {2, 6, 9}}, {1111, {2, 6, 10}}, {1432, {2, 6, 11}}, {1896, {2, 6, 12}}, {2595, {2, 6, 13}}, {3409, {2, 6, 14}}, {3861, {2, 6, 15}}, {610, {2, 7, 7}}, {727, {2, 7, 8}}, {941, {2, 7, 9}}, {1266, {2, 7, 10}}, {1587, {2, 7, 11}}, {2051, {2, 7, 12}}, {2750, {2, 7, 13}}, {3564, {2, 7, 14}}, {4016, {2, 7, 15}}, {844, {2, 8, 8}}, {1058, {2, 8, 9}}, {1383, {2, 8, 10}}, {1704, {2, 8, 11}}, {2168, {2, 8, 12}}, {2867, {2, 8, 13}}, {3681, {2, 8, 14}}, {4133, {2, 8, 15}}, {1272, {2, 9, 9}}, {1597, {2, 9, 10}}, {1918, {2, 9, 11}}, {2382, {2, 9, 12}}, {3081, {2, 9, 13}}, {3895, {2, 9, 14}}, {4347, {2, 9, 15}}, {1922, {2, 10, 10}}, {2243, {2, 10, 11}}, {2707, {2, 10, 12}}, {3406, {2, 10, 13}}, {4220, {2, 10, 14}}, {4672, {2, 10, 15}}, {2564, {2, 11, 11}}, {3028, {2, 11, 12}}, {3727, {2, 11, 13}}, {4541, {2, 11, 14}}, {4993, {2, 11, 15}}, {3492, {2, 12, 12}}, {4191, {2, 12, 13}}, {5005, {2, 12, 14}}, {5457, {2, 12, 15}}, {4890, {2, 13, 13}}, {5704, {2, 13, 14}}, {6156, {2, 13, 15}}, {6518, {2, 14, 14}}, {6970, {2, 14, 15}}, {7422, {2, 15, 15}}, {309, {3, 3, 3}}, {325, {3, 3, 4}}, {330, {3, 3, 5}}, {339, {3, 3, 6}}, {494, {3, 3, 7}}, {611, {3, 3, 8}}, {825, {3, 3, 9}}, {1150, {3, 3, 10}}, {1471, {3, 3, 11}}, {1935, {3, 3, 12}}, {2634, {3, 3, 13}}, {3448, {3, 3, 14}}, {3900, {3, 3, 15}}, {341, {3, 4, 4}}, {346, {3, 4, 5}}, {355, {3, 4, 6}}, {510, {3, 4, 7}}, {627, {3, 4, 8}}, {841, {3, 4, 9}}, {1166, {3, 4, 10}}, {1487, {3, 4, 11}}, {1951, {3, 4, 12}}, {2650, {3, 4, 13}}, {3464, {3, 4, 14}}, {3916, {3, 4, 15}}, {351, {3, 5, 5}}, {360, {3, 5, 6}}, {515, {3, 5, 7}}, {632, {3, 5, 8}}, {846, {3, 5, 9}}, {1171, {3, 5, 10}}, {1492, {3, 5, 11}}, {1956, {3, 5, 12}}, {2655, {3, 5, 13}}, {3469, {3, 5, 14}}, {3921, {3, 5, 15}}, {369, {3, 6, 6}}, {524, {3, 6, 7}}, {641, {3, 6, 8}}, {855, {3, 6, 9}}, {1180, {3, 6, 10}}, {1501, {3, 6, 11}}, {1965, {3, 6, 12}}, {2664, {3, 6, 13}}, {3478, {3, 6, 14}}, {3930, {3, 6, 15}}, {679, {3, 7, 7}}, {796, {3, 7, 8}}, {1010, {3, 7, 9}}, {1335, {3, 7, 10}}, {1656, {3, 7, 11}}, {2120, {3, 7, 12}}, {2819, {3, 7, 13}}, {3633, {3, 7, 14}}, {4085, {3, 7, 15}}, {913, {3, 8, 8}}, {1127, {3, 8, 9}}, {1452, {3, 8, 10}}, {1773, {3, 8, 11}}, {2237, {3, 8, 12}}, {2936, {3, 8, 13}}, {3750, {3, 8, 14}}, {4202, {3, 8, 15}}, {1341, {3, 9, 9}}, {1666, {3, 9, 10}}, {1987, {3, 9, 11}}, {2451, {3, 9, 12}}, {3150, {3, 9, 13}}, {3964, {3, 9, 14}}, {4416, {3, 9, 15}}, {1991, {3, 10, 10}}, {2312, {3, 10, 11}}, {2776, {3, 10, 12}}, {3475, {3, 10, 13}}, {4289, {3, 10, 14}}, {4741, {3, 10, 15}}, {2633, {3, 11, 11}}, {3097, {3, 11, 12}}, {3796, {3, 11, 13}}, {4610, {3, 11, 14}}, {5062, {3, 11, 15}}, {3561, {3, 12, 12}}, {4260, {3, 12, 13}}, {5074, {3, 12, 14}}, {5526, {3, 12, 15}}, {4959, {3, 13, 13}}, {5773, {3, 13, 14}}, {6225, {3, 13, 15}}, {6587, {3, 14, 14}}, {7039, {3, 14, 15}}, {7491, {3, 15, 15}}, {357, {4, 4, 4}}, {362, {4, 4, 5}}, {371, {4, 4, 6}}, {526, {4, 4, 7}}, {643, {4, 4, 8}}, {857, {4, 4, 9}}, {1182, {4, 4, 10}}, {1503, {4, 4, 11}}, {1967, {4, 4, 12}}, {2666, {4, 4, 13}}, {3480, {4, 4, 14}}, {3932, {4, 4, 15}}, {367, {4, 5, 5}}, {376, {4, 5, 6}}, {531, {4, 5, 7}}, {648, {4, 5, 8}}, {862, {4, 5, 9}}, {1187, {4, 5, 10}}, {1508, {4, 5, 11}}, {1972, {4, 5, 12}}, {2671, {4, 5, 13}}, {3485, {4, 5, 14}}, {3937, {4, 5, 15}}, {385, {4, 6, 6}}, {540, {4, 6, 7}}, {657, {4, 6, 8}}, {871, {4, 6, 9}}, {1196, {4, 6, 10}}, {1517, {4, 6, 11}}, {1981, {4, 6, 12}}, {2680, {4, 6, 13}}, {3494, {4, 6, 14}}, {3946, {4, 6, 15}}, {695, {4, 7, 7}}, {812, {4, 7, 8}}, {1026, {4, 7, 9}}, {1351, {4, 7, 10}}, {1672, {4, 7, 11}}, {2136, {4, 7, 12}}, {2835, {4, 7, 13}}, {3649, {4, 7, 14}}, {4101, {4, 7, 15}}, {929, {4, 8, 8}}, {1143, {4, 8, 9}}, {1468, {4, 8, 10}}, {1789, {4, 8, 11}}, {2253, {4, 8, 12}}, {2952, {4, 8, 13}}, {3766, {4, 8, 14}}, {4218, {4, 8, 15}}, {1357, {4, 9, 9}}, {1682, {4, 9, 10}}, {2003, {4, 9, 11}}, {2467, {4, 9, 12}}, {3166, {4, 9, 13}}, {3980, {4, 9, 14}}, {4432, {4, 9, 15}}, {2007, {4, 10, 10}}, {2328, {4, 10, 11}}, {2792, {4, 10, 12}}, {3491, {4, 10, 13}}, {4305, {4, 10, 14}}, {4757, {4, 10, 15}}, {2649, {4, 11, 11}}, {3113, {4, 11, 12}}, {3812, {4, 11, 13}}, {4626, {4, 11, 14}}, {5078, {4, 11, 15}}, {3577, {4, 12, 12}}, {4276, {4, 12, 13}}, {5090, {4, 12, 14}}, {5542, {4, 12, 15}}, {4975, {4, 13, 13}}, {5789, {4, 13, 14}}, {6241, {4, 13, 15}}, {6603, {4, 14, 14}}, {7055, {4, 14, 15}}, {7507, {4, 15, 15}}, {372, {5, 5, 5}}, {381, {5, 5, 6}}, {536, {5, 5, 7}}, {653, {5, 5, 8}}, {867, {5, 5, 9}}, {1192, {5, 5, 10}}, {1513, {5, 5, 11}}, {1977, {5, 5, 12}}, {2676, {5, 5, 13}}, {3490, {5, 5, 14}}, {3942, {5, 5, 15}}, {390, {5, 6, 6}}, {545, {5, 6, 7}}, {662, {5, 6, 8}}, {876, {5, 6, 9}}, {1201, {5, 6, 10}}, {1522, {5, 6, 11}}, {1986, {5, 6, 12}}, {2685, {5, 6, 13}}, {3499, {5, 6, 14}}, {3951, {5, 6, 15}}, {700, {5, 7, 7}}, {817, {5, 7, 8}}, {1031, {5, 7, 9}}, {1356, {5, 7, 10}}, {1677, {5, 7, 11}}, {2141, {5, 7, 12}}, {2840, {5, 7, 13}}, {3654, {5, 7, 14}}, {4106, {5, 7, 15}}, {934, {5, 8, 8}}, {1148, {5, 8, 9}}, {1473, {5, 8, 10}}, {1794, {5, 8, 11}}, {2258, {5, 8, 12}}, {2957, {5, 8, 13}}, {3771, {5, 8, 14}}, {4223, {5, 8, 15}}, {1362, {5, 9, 9}}, {1687, {5, 9, 10}}, {2008, {5, 9, 11}}, {2472, {5, 9, 12}}, {3171, {5, 9, 13}}, {3985, {5, 9, 14}}, {4437, {5, 9, 15}}, {2012, {5, 10, 10}}, {2333, {5, 10, 11}}, {2797, {5, 10, 12}}, {3496, {5, 10, 13}}, {4310, {5, 10, 14}}, {4762, {5, 10, 15}}, {2654, {5, 11, 11}}, {3118, {5, 11, 12}}, {3817, {5, 11, 13}}, {4631, {5, 11, 14}}, {5083, {5, 11, 15}}, {3582, {5, 12, 12}}, {4281, {5, 12, 13}}, {5095, {5, 12, 14}}, {5547, {5, 12, 15}}, {4980, {5, 13, 13}}, {5794, {5, 13, 14}}, {6246, {5, 13, 15}}, {6608, {5, 14, 14}}, {7060, {5, 14, 15}}, {7512, {5, 15, 15}}, {399, {6, 6, 6}}, {554, {6, 6, 7}}, {671, {6, 6, 8}}, {885, {6, 6, 9}}, {1210, {6, 6, 10}}, {1531, {6, 6, 11}}, {1995, {6, 6, 12}}, {2694, {6, 6, 13}}, {3508, {6, 6, 14}}, {3960, {6, 6, 15}}, {709, {6, 7, 7}}, {826, {6, 7, 8}}, {1040, {6, 7, 9}}, {1365, {6, 7, 10}}, {1686, {6, 7, 11}}, {2150, {6, 7, 12}}, {2849, {6, 7, 13}}, {3663, {6, 7, 14}}, {4115, {6, 7, 15}}, {943, {6, 8, 8}}, {1157, {6, 8, 9}}, {1482, {6, 8, 10}}, {1803, {6, 8, 11}}, {2267, {6, 8, 12}}, {2966, {6, 8, 13}}, {3780, {6, 8, 14}}, {4232, {6, 8, 15}}, {1371, {6, 9, 9}}, {1696, {6, 9, 10}}, {2017, {6, 9, 11}}, {2481, {6, 9, 12}}, {3180, {6, 9, 13}}, {3994, {6, 9, 14}}, {4446, {6, 9, 15}}, {2021, {6, 10, 10}}, {2342, {6, 10, 11}}, {2806, {6, 10, 12}}, {3505, {6, 10, 13}}, {4319, {6, 10, 14}}, {4771, {6, 10, 15}}, {2663, {6, 11, 11}}, {3127, {6, 11, 12}}, {3826, {6, 11, 13}}, {4640, {6, 11, 14}}, {5092, {6, 11, 15}}, {3591, {6, 12, 12}}, {4290, {6, 12, 13}}, {5104, {6, 12, 14}}, {5556, {6, 12, 15}}, {4989, {6, 13, 13}}, {5803, {6, 13, 14}}, {6255, {6, 13, 15}}, {6617, {6, 14, 14}}, {7069, {6, 14, 15}}, {7521, {6, 15, 15}}, {864, {7, 7, 7}}, {981, {7, 7, 8}}, {1195, {7, 7, 9}}, {1520, {7, 7, 10}}, {1841, {7, 7, 11}}, {2305, {7, 7, 12}}, {3004, {7, 7, 13}}, {3818, {7, 7, 14}}, {4270, {7, 7, 15}}, {1098, {7, 8, 8}}, {1312, {7, 8, 9}}, {1637, {7, 8, 10}}, {1958, {7, 8, 11}}, {2422, {7, 8, 12}}, {3121, {7, 8, 13}}, {3935, {7, 8, 14}}, {4387, {7, 8, 15}}, {1526, {7, 9, 9}}, {1851, {7, 9, 10}}, {2172, {7, 9, 11}}, {2636, {7, 9, 12}}, {3335, {7, 9, 13}}, {4149, {7, 9, 14}}, {4601, {7, 9, 15}}, {2176, {7, 10, 10}}, {2497, {7, 10, 11}}, {2961, {7, 10, 12}}, {3660, {7, 10, 13}}, {4474, {7, 10, 14}}, {4926, {7, 10, 15}}, {2818, {7, 11, 11}}, {3282, {7, 11, 12}}, {3981, {7, 11, 13}}, {4795, {7, 11, 14}}, {5247, {7, 11, 15}}, {3746, {7, 12, 12}}, {4445, {7, 12, 13}}, {5259, {7, 12, 14}}, {5711, {7, 12, 15}}, {5144, {7, 13, 13}}, {5958, {7, 13, 14}}, {6410, {7, 13, 15}}, {6772, {7, 14, 14}}, {7224, {7, 14, 15}}, {7676, {7, 15, 15}}, {1215, {8, 8, 8}}, {1429, {8, 8, 9}}, {1754, {8, 8, 10}}, {2075, {8, 8, 11}}, {2539, {8, 8, 12}}, {3238, {8, 8, 13}}, {4052, {8, 8, 14}}, {4504, {8, 8, 15}}, {1643, {8, 9, 9}}, {1968, {8, 9, 10}}, {2289, {8, 9, 11}}, {2753, {8, 9, 12}}, {3452, {8, 9, 13}}, {4266, {8, 9, 14}}, {4718, {8, 9, 15}}, {2293, {8, 10, 10}}, {2614, {8, 10, 11}}, {3078, {8, 10, 12}}, {3777, {8, 10, 13}}, {4591, {8, 10, 14}}, {5043, {8, 10, 15}}, {2935, {8, 11, 11}}, {3399, {8, 11, 12}}, {4098, {8, 11, 13}}, {4912, {8, 11, 14}}, {5364, {8, 11, 15}}, {3863, {8, 12, 12}}, {4562, {8, 12, 13}}, {5376, {8, 12, 14}}, {5828, {8, 12, 15}}, {5261, {8, 13, 13}}, {6075, {8, 13, 14}}, {6527, {8, 13, 15}}, {6889, {8, 14, 14}}, {7341, {8, 14, 15}}, {7793, {8, 15, 15}}, {1857, {9, 9, 9}}, {2182, {9, 9, 10}}, {2503, {9, 9, 11}}, {2967, {9, 9, 12}}, {3666, {9, 9, 13}}, {4480, {9, 9, 14}}, {4932, {9, 9, 15}}, {2507, {9, 10, 10}}, {2828, {9, 10, 11}}, {3292, {9, 10, 12}}, {3991, {9, 10, 13}}, {4805, {9, 10, 14}}, {5257, {9, 10, 15}}, {3149, {9, 11, 11}}, {3613, {9, 11, 12}}, {4312, {9, 11, 13}}, {5126, {9, 11, 14}}, {5578, {9, 11, 15}}, {4077, {9, 12, 12}}, {4776, {9, 12, 13}}, {5590, {9, 12, 14}}, {6042, {9, 12, 15}}, {5475, {9, 13, 13}}, {6289, {9, 13, 14}}, {6741, {9, 13, 15}}, {7103, {9, 14, 14}}, {7555, {9, 14, 15}}, {8007, {9, 15, 15}}, {2832, {10, 10, 10}}, {3153, {10, 10, 11}}, {3617, {10, 10, 12}}, {4316, {10, 10, 13}}, {5130, {10, 10, 14}}, {5582, {10, 10, 15}}, {3474, {10, 11, 11}}, {3938, {10, 11, 12}}, {4637, {10, 11, 13}}, {5451, {10, 11, 14}}, {5903, {10, 11, 15}}, {4402, {10, 12, 12}}, {5101, {10, 12, 13}}, {5915, {10, 12, 14}}, {6367, {10, 12, 15}}, {5800, {10, 13, 13}}, {6614, {10, 13, 14}}, {7066, {10, 13, 15}}, {7428, {10, 14, 14}}, {7880, {10, 14, 15}}, {8332, {10, 15, 15}}, {3795, {11, 11, 11}}, {4259, {11, 11, 12}}, {4958, {11, 11, 13}}, {5772, {11, 11, 14}}, {6224, {11, 11, 15}}, {4723, {11, 12, 12}}, {5422, {11, 12, 13}}, {6236, {11, 12, 14}}, {6688, {11, 12, 15}}, {6121, {11, 13, 13}}, {6935, {11, 13, 14}}, {7387, {11, 13, 15}}, {7749, {11, 14, 14}}, {8201, {11, 14, 15}}, {8653, {11, 15, 15}}, {5187, {12, 12, 12}}, {5886, {12, 12, 13}}, {6700, {12, 12, 14}}, {7152, {12, 12, 15}}, {6585, {12, 13, 13}}, {7399, {12, 13, 14}}, {7851, {12, 13, 15}}, {8213, {12, 14, 14}}, {8665, {12, 14, 15}}, {9117, {12, 15, 15}}, {7284, {13, 13, 13}}, {8098, {13, 13, 14}}, {8550, {13, 13, 15}}, {8912, {13, 14, 14}}, {9364, {13, 14, 15}}, {9816, {13, 15, 15}}, {9726, {14, 14, 14}}, {10178, {14, 14, 15}}, {10630, {14, 15, 15}}, {11082, {15, 15, 15}}};
    struct bhbf cell[cell_num];
    vector<pair<int, int>> p; //用于储存query时得到的k个cell，first是原来下标，second是对应的count
    vector<int> comcode;      //暂时存放求交集后所属集合号
    vector<int> codelist;  //每个数对应的所属集合号
    vector<int> result; //存放交集结果的

    static bool cmp(const pair<int, int> a, const pair<int, int> b)
    {
        return a.second < b.second;
    }
    //还要实现一个哈希表
    void init()
    {
        for (int i = 0; i < cell_num; i++)
        {
            cell[i].sum = 0;
            cell[i].count = 0;
            //cell[i].valid = 1;
        }
    }

    void insert(string key, int set_id)
    {
        int d = sequence[set_id];
        for (int i = 0; i < k; i++)
        {
            int temp = MurmurHash64A(key.c_str(), 31, seed[i]) % cell_num;
            cell[temp].count++;
            cell[temp].sum += d;
            // cout << temp << " " << cell[temp].count << " " << cell[temp].sum << endl;
        }
    }
    int query(string key)
    {
        p.clear();
        comcode.clear();
        for (int i = 0; i < k; i++)
        {
            int temp = MurmurHash64A(key.c_str(), 31, seed[i]) % cell_num;
            p.push_back(make_pair(temp, cell[temp].count));
        }
        sort(p.begin(), p.end(), cmp);
        // for (int i = 0; i < k; i++)
        // {
        //     cout << p[i].first << " " << p[i].second << " " << cell[p[i].first].sum << endl;
        // }
        // cout << endl;

        int start = 0;
        for (int i = 0; i < k; i++)
        {
            if (p[i].second == 0)
            {
                return -1; //表示无解
            }
            else if (p[i].second > 0 && p[i].second <= 3)
            {
                codelist.clear();
                int temp = p[i].second;
                int s = cell[p[i].first].sum;
                if (temp == 1)
                {
                    codelist.push_back(decode1[s]);
                }
                else if (temp == 2)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        codelist.push_back(decode2[s][j]);
                        // cout << "codelist2: " << decode2[s][j] << endl;
                    }
                }
                else if (temp == 3)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        codelist.push_back(decode3[s][j]);
                        // cout << "codelist3: " << decode3[s][j] << endl;
                    }
                }
                if (i == 0)
                {
                    comcode.assign(codelist.begin(), codelist.end()); //comcode<-codelist
                    // for (int j = 0;j<comcode.size();j++)
                    //     cout << "comcode: " << comcode[j] << endl;
                }
                else
                {
                    //求交集之前要先排序，但在设计哈希表时应该就是从小到大排的
                    set_intersection(comcode.begin(), comcode.end(), codelist.begin(), codelist.end(), back_inserter(result));
                    comcode.assign(result.begin(), result.end());
                    result.clear();
                    if (comcode.size() == 0)
                    {
                        return -1;
                    }
                    // for (int j = 0;j<comcode.size();j++)
                    //     cout << "comcode: " << comcode[j] << endl;
                }
            }
            else
            {
                start = i;
                // cout << "start: " << start << endl;
                break; //按照count排的序
            }
        }
        if (comcode.size() == 1)
        {
            // cout << "enter 1" << endl;
            return comcode[0]; //即对应的sequence数组下标
        }
        else
        {
            if (p[start].second > 4 && comcode.size() > 0) //没有符合条件的cell
                return comcode[0];
            // for (int i = 0; i < comcode.size(); i++)
            //     cout << comcode[i] << endl;
            for (int i = 0; i < comcode.size(); i++)
            {                       //一个个试comcode里的元素
                int d = comcode[i]; //尝试的dj
                bool flag = true;
                for (int j = start; j < k; j++)
                {
                    if (p[j].second == 4)
                    { //对于有4个元素的cell试着减去一个
                        int temp = cell[p[j].first].sum - sequence[d];
                        //decode：根据temp作为和看能不能找到对应的3个数，如果找不到flag置false,直接break
                        unordered_map<int, vector<int>>::iterator iter = decode3.find(temp);
                        if (iter == decode3.end())
                        {
                            flag = false;
                            break;
                        }
                    }
                }
                if (flag)
                { //找到了
                    // cout << "enter 2" << endl;
                    // cout << "d: " << d << endl;
                    return d;
                }
            }
            //全>=4
            return -2; //unknown
        }
    }
};