#include "common.hpp"

#include <vector>

void test_dynamic_dispatch(std::vector<type> &range)
{
    std::for_each(range.begin(), range.end(), [](auto &e) { e->add(); });
}
