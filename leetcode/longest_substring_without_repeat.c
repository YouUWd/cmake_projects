/**
 * ### [3\. 无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)

Difficulty: **中等**


给定一个字符串 `s` ，请你找出其中不含有重复字符的 **最长子串 **的长度。

**示例 1:**

```
输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
```

**示例 2:**

```
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
```

**示例 3:**

```
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```

**示例 4:**

```
输入: s = ""
输出: 0
```

**提示：**

*   `0 <= s.length <= 5 * 10<sup>4</sup>`
*   `s` 由英文字母、数字、符号和空格组成


#### Solution

Language: ****

```
​
```
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int lengthOfLongestSubstring(char *s) {

    int ret = 0;
    for (int i = 0; i < strlen(s); ++i) {
        for (int j = i + 1; j < strlen(s); ++j) {
            int hit = 0;
            for (int k = j - 1; k >= i; --k) {
                if (s[j] == s[k]) {
                    hit = 1;
                    break;
                }
            }
            if (!hit) {
                ret = (j - i) > ret ? j - i : ret;
            } else {
                break;
            }
        }
    }
    return strlen(s) == 0 ? 0 : ret + 1;
}

int lengthOfLongestSubstring1(char *s) {
    char data[UCHAR_MAX] = {0};
    int ret = 0;
    size_t size = strlen(s);
    for (int start = 0; start < size; ++start) {
        memset(data, 0, sizeof(data));
        int t = 0;
        data[s[start]] = 1;
        for (int end = start + 1; end < size; ++end) {
            if (data[s[end]]) {
                break;
            } else {
                t++;
            }
            data[s[end]] = 1;
        }
        ret = ret > t ? ret : t;
    }
    return size == 0 ? 0 : ret + 1;
}

int lengthOfLongestSubstring2(char *s) {
    int start = 0, end = 0, maxlen = 0;
    char map[256] = {0};
    map[(int) *(s + start)] = 1;

    while (*(s + end) != 0) {
        maxlen = maxlen > (end - start + 1) ? maxlen : (end - start + 1);
        ++end;
        while (0 != map[(int) *(s + end)])//将要加入的新元素与map内元素冲突
        {
            map[(int) *(s + start)] = 0;
            ++start;
        }
        map[(int) *(s + end)] = 1;
    }

    return maxlen;
}

int lengthOfLongestSubstring3(char *s) {
    int ret = 0;
    char data[UCHAR_MAX] = {0};
    data[s[0]] = 1;
    size_t size = strlen(s);
    int start, end = 0;

    for (start = 0; start < size; ++start) {
        end++;
        while (data[s[end]] == 0 && end < size) {
            data[s[end]] = 1;
            end++;
        }
        data[s[start]] = 0;
        ret = ret > (end - start + 1) ? ret : (end - start + 1);
    }
    return ret;
}

int lengthOfLongestSubstring4(char *s) {
    int ret = 0;
    char data[UCHAR_MAX] = {0};
    size_t size = strlen(s);
    int start, end;
    for (start = 0; start < size; ++start) {
        data[s[start]] = 1;
        end = start;
        while (end < size) {
            end++;
            if (data[s[end]] == 1) {
                data[s[start]] = 0;
                break;
            } else {
                data[s[end]] = 1;
            }
        }
        ret = ret > (end - start + 1) ? ret : (end - start + 1);
        printf("%d->%d \n", start, (end - start));

    }
    return ret;
}

int lengthOfLongestSubstring5(char *s) {
    int max = 0, start = 0, end = 0;
    int map[UCHAR_MAX] = {0};
    map[s[0]] = 1;
    while (*(s + end)) {
        end++;
        printf("%c %c\n", s[start], s[end]);
        while (map[s[end]] == 0 && s[end]) {
            map[s[end]] = 1;
            end++;
        }
        if (s[end]) {
            if (s[end] == s[start]) {
                start++;
            } else {
                map[s[start]] = 0;
                end--;
            }
        }
        max = max > (end - start) ? max : (end - start);
    }
    return max;
}

int main() {
//    int data[] = {1, 2, 3, 4, 5};
//    for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
//        printf("%d %d\n", i, data[i]);
//    }
//    printf("=============================\n");
//    char s[] = "Hello";
//    for (int i = 0; i < sizeof(s); ++i) {
//        printf("%d %c\n", i, s[i]);
//    }
//    printf("=============================\n");
//    for (int i = 0; i < strlen(s); ++i) {
//        printf("%d %c\n", i, s[i]);
//    }
//    printf("=============================\n");
//    int i = 0;
//    while (*(s + i)) {
//        printf("%d %c\n", i, s[i]);
//        i++;
//    }
    printf("%d\n", lengthOfLongestSubstring5("abccabd"));
    return 0;
}