/*
### [1\. 两数之和](https://leetcode-cn.com/problems/two-sum/)

Difficulty: **简单**


给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出 **和为目标值** _`target`_  的那 **两个** 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

**示例 1：**

```
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
```

**示例 2：**

```
输入：nums = [3,2,4], target = 6
输出：[1,2]
```

**示例 3：**

```
输入：nums = [3,3], target = 6
输出：[0,1]
```

**提示：**

*   `2 <= nums.length <= 10<sup>4</sup>`
*   `-10<sup>9</sup> <= nums[i] <= 10<sup>9</sup>`
*   `-10<sup>9</sup> <= target <= 10<sup>9</sup>`
*   **只会存在一个有效答案**

**进阶：**你可以想出一个时间复杂度小于 `O(n<sup>2</sup>)` 的算法吗？

 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "uthash.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    for (int i = 0; i < numsSize; ++i) {
        int a = nums[i];
        for (int j = i + 1; j < numsSize; ++j) {
            int b = nums[j];
            if (a + b == target) {
                int *ret = malloc(sizeof(int) * 2);
                ret[0] = i, ret[1] = j;
                *returnSize = 2;
                return ret;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}


struct hashTable {
    int key;
    int val;
    UT_hash_handle hh;
};

struct hashTable *hashtable;

struct hashTable *find(int k) {
    struct hashTable *tmp;
    HASH_FIND_INT(hashtable, &k, tmp);
    return tmp;
}

void put(int k, int v) {
    struct hashTable *it = find(k);
    if (it == NULL) {
        struct hashTable *tmp = malloc(sizeof(struct hashTable));
        tmp->key = k, tmp->val = v;
        HASH_ADD_INT(hashtable, key, tmp);
    } else {
        it->val = v;
    }
}


int *twoSum2(int *nums, int numsSize, int target, int *returnSize) {
    hashtable = NULL;
    for (int i = 0; i < numsSize; ++i) {
        struct hashTable *h = find(target - nums[i]);
        if (h == NULL) {
            put(nums[i], i);
            continue;
        }
        int *ret = malloc(sizeof(int) * 2);
        ret[0] = h->val, ret[1] = i;
        *returnSize = 2;
        return ret;

    }
    *returnSize = 0;
    return NULL;
}

int *twoSum3(int *nums, int numsSize, int target, int *returnSize) {

    int *bit;
    bit = malloc(sizeof(int) * numsSize);
    memset(bit, -1, sizeof(int) * numsSize);

    for (int i = 0; i < numsSize; ++i) {
        if (bit[(target - nums[i]) % numsSize] >= 0) {
            int *ret = malloc(sizeof(int) * 2);
            ret[0] = bit[target - nums[i]], ret[1] = i;
            *returnSize = 2;
            return ret;
        }
        bit[nums[i] % numsSize] = i;
    }
    *returnSize = 0;
    return NULL;
}

int main() {
    int p[4] = {2, 7, 11, 15};
    int *returnSize = malloc(sizeof(int) * 1);
    int *ret = twoSum3(p, 4, 9, returnSize);
    if (returnSize[0] != 0)
        printf("%d %d \n", ret[0], ret[1]);
    else
        printf("%d %d\n", returnSize[0], ret);

}