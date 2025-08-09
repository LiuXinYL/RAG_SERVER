
#include <stdio.h>
#include <stdlib.h>

// 测试函数：检查值是否在范围内
int is_value_in_range(int range_start, int range_len, int value) {
    if (range_len <= 0) {
        return 0;  // 无效范围
    }
    
    int range_end = range_start + range_len - 1;
    
    if (value >= range_start && value <= range_end) {
        return 1;  // 在范围内
    } else {
        return 0;  // 不在范围内
    }
}

// 测试函数：计算两个数的和
int add_numbers(int a, int b) {
    return a + b;
}

// 测试函数：字符串长度检查
int check_string_length(const char* str, int max_length) {
    if (str == NULL) {
        return -1;  // 空指针
    }
    
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    
    if (length <= max_length) {
        return 1;  // 长度符合要求
    } else {
        return 0;  // 长度超出限制
    }
}
