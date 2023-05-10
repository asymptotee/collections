#include <stdio.h>
#include "bin_search.h"

int bin_search(int *arr, int x, int size) {
    int left=0,right=size-1,mid=0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] == x) {
            return mid;
        } else if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}