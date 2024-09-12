#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include "common.hpp"

#ifdef TEST_PROXY

#ifdef MULTI_FUNCS
#define DEFINE_FUNC(name)                                                      \
    int name() { return x += 1; }
#else 
#define DEFINE_FUNC(name) 
#endif

#define DEFINE_CLASS(name, id)                                                 \
    struct name##_##id                                                         \
    {                                                                          \
        int _[EXTRA_SIZE];                                                     \
        int x;                                                                 \
        name##_##id(int x) : x(x) {}                                           \
        int add() { return x += id; }                                          \
        DEFINE_FUNC(add1)                                                      \
        DEFINE_FUNC(add2)                                                      \
        DEFINE_FUNC(add3)                                                      \
        DEFINE_FUNC(add4)                                                      \
        DEFINE_FUNC(add5)                                                      \
        DEFINE_FUNC(add6)                                                      \
        DEFINE_FUNC(add7)                                                      \
        DEFINE_FUNC(add8)                                                      \
        DEFINE_FUNC(add9)                                                      \
        DEFINE_FUNC(add10)                                                     \
        DEFINE_FUNC(add11)                                                     \
        DEFINE_FUNC(add12)                                                     \
        DEFINE_FUNC(add13)                                                     \
        DEFINE_FUNC(add14)                                                     \
        DEFINE_FUNC(add15)                                                     \
    };

#else

#ifdef MULTI_FUNCS
#define DEFINE_FUNC(name)                                                      \
    int name() override { return x += 1; }
#else 
#define DEFINE_FUNC(name) 
#endif

#define DEFINE_CLASS(name, id)                                                 \
    struct name##_##id : public base                                           \
    {                                                                          \
        int _[EXTRA_SIZE];                                                     \
        int x;                                                                 \
        name##_##id(int x) : x(x) {}                                           \
        int add() override { return x += id; }                                 \
        DEFINE_FUNC(add1)                                                      \
        DEFINE_FUNC(add2)                                                      \
        DEFINE_FUNC(add3)                                                      \
        DEFINE_FUNC(add4)                                                      \
        DEFINE_FUNC(add5)                                                      \
        DEFINE_FUNC(add6)                                                      \
        DEFINE_FUNC(add7)                                                      \
        DEFINE_FUNC(add8)                                                      \
        DEFINE_FUNC(add9)                                                      \
        DEFINE_FUNC(add10)                                                     \
        DEFINE_FUNC(add11)                                                     \
        DEFINE_FUNC(add12)                                                     \
        DEFINE_FUNC(add13)                                                     \
        DEFINE_FUNC(add14)                                                     \
        DEFINE_FUNC(add15)                                                     \
    };

#endif
#include "class.inc"
#undef DEFINE_CLASS
#undef DEFINE_FUNC

#ifdef TEST_PROXY

type class_factory(int id)
{
#define DEFINE_CLASS(name, id)                                                 \
    case id:                                                                   \
        return pro::make_proxy<Addable>(name##_##id{id});
    switch (id)
    {
#include "class.inc"
    }
    throw std::runtime_error("unknown id");
#undef DEFINE_CLASS
}

#else

type class_factory(int id)
{
#define DEFINE_CLASS(name, id)                                                 \
    case id:                                                                   \
        return std::make_unique<name##_##id>(id);
    switch (id)
    {
#include "class.inc"
    }
    throw std::runtime_error("unknown id");
#undef DEFINE_CLASS
}

#endif

int main(void)
{
    std::vector<decltype(class_factory(0))> cls_vec(TESTN);
    std::cout << sizeof(decltype(class_factory(0))) << std::endl;
    std::cout << sizeof(cls_0) << std::endl;
    for (int i = 0; i < TESTN; i++)
        cls_vec[i] = class_factory(i % 16);

    for (int i = 0; i < WARMUP; i++)
        test_dynamic_dispatch(cls_vec);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < TEST; i++)
        test_dynamic_dispatch(cls_vec);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << std::endl;

    long long now = 0;
    std::for_each(cls_vec.begin(), cls_vec.end(), [&now](auto &e) { now += e->add(); });
    std::cout << now << std::endl;
}
