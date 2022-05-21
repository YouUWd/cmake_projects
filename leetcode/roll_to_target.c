/*
这里有 d 个一样的骰子，每个骰子上都有 f 个面，分别标号为 1, 2, ..., f。

我们约定：掷骰子的得到总点数为各骰子面朝上的数字的总和。

如果需要掷出的总点数为 target，请你计算出有多少种不同的组合情况（所有的组合情况总共有 f^d 种），模 10^9 + 7 后返回。

示例 1：
输入：d = 1, f = 6, target = 3
输出：1

示例 2：
输入：d = 2, f = 6, target = 7
输出：6

示例 3：
输入：d = 2, f = 5, target = 10
输出：1

示例 4：
输入：d = 1, f = 2, target = 3
输出：0

示例 5：
输入：d = 30, f = 30, target = 500
输出：222616187


提示：

1 <= d, f <= 30
1 <= target <= 1000
 */
#include <stdio.h>

/**
 *
 * @param d 骰子数
 * @param f 面数
 * @param target 总点数
 * @return
 */
int numRollsToTarget(int d, int f, int target) {
    if (d == 1) {
        int ret = f >= target ? 1 : 0;
//        printf("<> %d %d => %d\n", d, target, ret);
        return ret;
    }
    int ret = 0;
    for (int i = 1; i < target && i <= f; ++i) {
        ret += numRollsToTarget(d - 1, f, target - i);;
    }
    printf(">> %d %d => %d\n", d, target, ret);
    return ret;
}

int main() {
//    printf("%d\n", numRollsToTarget(1, 6, 3));
//    printf("%d\n", numRollsToTarget(2, 6, 7));
//    printf("%d\n", numRollsToTarget(2, 5, 10));
//    printf("%d\n", numRollsToTarget(1, 2, 3));
    printf("%d\n", numRollsToTarget(3, 4, 5));
    printf("%d\n", numRollsToTarget(3, 4, 6));
    printf("%d\n", numRollsToTarget(30, 30, 500));
}