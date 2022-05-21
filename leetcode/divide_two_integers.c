// https://leetcode-cn.com/problems/divide-two-integers/
#include <stdio.h>
#include <limits.h>


int divide1(int dividend, int divisor) {
    if (divisor == 0) {
        return 0;
    }
    if (divisor == INT_MIN) {
        return dividend == INT_MIN ? 1 : 0;
    }
    if (divisor == 1) {
        return dividend;
    }
    if (divisor == -1) {
        return dividend == INT_MIN ? INT_MAX : -dividend;
    }
    int ret = 0;
    if ((dividend ^ divisor) >= 0) {
        int ori = dividend;
        while (((dividend -= divisor) ^ ori) >= 0 || dividend == 0) {
            if (ret == INT_MAX) {
                return INT_MAX;
            }
            ret++;
        }
    } else {
        return -divide1(dividend, -divisor);
    }
    return ret;
}

int quickAdd(int y, int z, int x) {
    // x 和 y 是负数，z 是正数
    // 需要判断 z * y >= x 是否成立
    int result = 0, add = y;
    while (z) {
        if (z & 1) {
            // 需要保证 result + add >= x
            if (result < x - add) {
                return 0;
            }
            result += add;
        }
        if (z != 1) {
            // 需要保证 add + add >= x
            if (add < x - add) {
                return 0;
            }
            add += add;
        }
        // 不能使用除法
        z >>= 1;
    }
    return 1;
}

int divide2(int dividend, int divisor) {
    if (divisor == 0) {
        return 0;
    }
    if (divisor == INT_MIN) {
        return dividend == INT_MIN ? 1 : 0;
    }
    if (divisor == 1) {
        return dividend;
    }
    if (divisor == -1) {
        return dividend == INT_MIN ? INT_MAX : -dividend;
    }

    int ret = 0;
    if ((dividend ^ divisor) >= 0) {
        int ori = dividend;
        while (((dividend -= divisor) ^ ori) >= 0 || dividend == 0) {
            if (ret == INT_MAX) {
                return INT_MAX;
            }
            ret++;
        }
    } else {
        return -divide2(dividend, -divisor);
    }
    return ret;
}

int divide(int dividend, int divisor) {
    // 考虑被除数为最小值的情况
    if (dividend == INT_MIN) {
        if (divisor == 1) {
            return INT_MIN;
        }
        if (divisor == -1) {
            return INT_MAX;
        }
    }
    // 考虑除数为最小值的情况
    if (divisor == INT_MIN) {
        return dividend == INT_MIN ? 1 : 0;
    }
    // 考虑被除数为 0 的情况
    if (dividend == 0) {
        return 0;
    }

    // 一般情况，使用二分查找
    // 将所有的正数取相反数，这样就只需要考虑一种情况
    int rev = 0;
    if (dividend > 0) {
        dividend = -dividend;
        rev = !rev;
    }
    if (divisor > 0) {
        divisor = -divisor;
        rev = !rev;
    }


    int left = 1, right = INT_MAX, ret = 0;
    while (left <= right) {
        // 注意溢出，并且不能使用除法
        int mid = left + ((right - left) >> 1);
        int check = quickAdd(divisor, mid, dividend);
        if (check) {
            ret = mid;
            // 注意溢出
            if (mid == INT_MAX) {
                break;
            }
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return ret;
}

int main() {
    printf("%d\n", divide(10, 3));
    printf("%d\n", divide(7, -3));
//    printf("%d\n", divide(1, 1));
//    printf("%d\n", divide(1, -1));
//    printf("%d\n", divide(INT_MAX, 1));
//    printf("%d\n", divide(INT_MAX, -1));
//    printf("%d\n", divide(INT_MIN, -1));
//    printf("%d\n", divide(INT_MIN, 1));
//    printf("%d\n", divide(-2147483648, -1));
//    printf("%d\n", divide(-2147483648, 2));
//    printf("%d\n", divide(-2147483648, -3));
//    printf("%d\n", quickAdd(-3, 4, -10));
//    printf("%d\n", quickAdd(-3, 3, -10));
//    int i = 0;
//    printf("%d\n", i);
//    i = !i;
//    printf("%d\n", i);
//    i = !i;
//    printf("%d\n", i);
//    return 0;
}