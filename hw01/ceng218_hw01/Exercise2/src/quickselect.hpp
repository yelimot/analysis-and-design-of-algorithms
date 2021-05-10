#ifndef QUICKSELECT_HPP
#define QUICKSELECT_HPP

#include <cstdlib>
#include <vector>
#include <algorithm>

template<typename T, typename Cmp>
void quicsort_generic(std::vector<T> &v, const Cmp &cmp);

// -------------------------- Template Implementations ----------------------------

template<typename T, typename Cmp>
int partition(std::vector<T> &v, int lo, int hi, const Cmp &cmp) {
    int i = lo;
    int j = hi + 1;

    while (true) {
        while (cmp(v[++i], v[lo]))
            if (i == hi) break;

        while (cmp(v[lo], v[--j]))
            if (j == lo) break;

        if (i >= j) break;
        std::swap(v[i], v[j]);
    }

    std::swap(v[lo], v[j]);
    return j;
}

template<typename T, typename Cmp>
void quickselect_r(std::vector<T> &v, int lo, int hi, int num, Cmp &cmp) {

    int index = partition(v, lo, hi, cmp);

    if (index > num) {
        quickselect_r(v, lo, index - 1, num, cmp);
    } else if (index < num) {
        quickselect_r(v, index + 1, hi, num, cmp);
    }
}

template<typename T, typename Cmp>
void quickselect_generic(std::vector<T> &v, int num, const Cmp &cmp) {
    std::random_shuffle(v.begin(), v.end());

    if (num <= v.size())
        for (int i = 1; i < num; i++)
            quickselect_r(v, 0, v.size()-1, i, cmp);
}

#endif
