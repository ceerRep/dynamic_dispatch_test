#pragma once

#include <memory>

#define TESTN 10000000
#define WARMUP 300
#define TEST 100
#define EXTRA_SIZE 15
#define MULTI_FUNCS

#define TEST_PROXY

#ifdef TEST_PROXY

#include "proxy/proxy.h"

#ifdef MULTI_FUNCS
#define DEFINE_FUNC(name) PRO_DEF_MEM_DISPATCH(Mem##name, name);
#else 
#define DEFINE_FUNC(name) 
#endif

DEFINE_FUNC(add1)
DEFINE_FUNC(add2)
DEFINE_FUNC(add3)
DEFINE_FUNC(add4)
DEFINE_FUNC(add5)
DEFINE_FUNC(add6)
DEFINE_FUNC(add7)
DEFINE_FUNC(add8)
DEFINE_FUNC(add9)
DEFINE_FUNC(add10)
DEFINE_FUNC(add11)
DEFINE_FUNC(add12)
DEFINE_FUNC(add13)
DEFINE_FUNC(add14)
DEFINE_FUNC(add15)

#undef DEFINE_FUNC

#ifdef MULTI_FUNCS
#define DEFINE_FUNC(name) ::add_convention<Mem##name, int(void)>
#else 
#define DEFINE_FUNC(name) 
#endif

PRO_DEF_MEM_DISPATCH(MemAdd, add);

struct Addable
    : pro::facade_builder ::add_convention<MemAdd, int(void)>
      DEFINE_FUNC(add1) DEFINE_FUNC(add2) DEFINE_FUNC(add3) DEFINE_FUNC(add4)
          DEFINE_FUNC(add5) DEFINE_FUNC(add6) DEFINE_FUNC(add7)
              DEFINE_FUNC(add8) DEFINE_FUNC(add9) DEFINE_FUNC(add10)
                  DEFINE_FUNC(add11) DEFINE_FUNC(add12) DEFINE_FUNC(add13)
                      DEFINE_FUNC(add14) DEFINE_FUNC(add15)::build
{
};

using type = pro::proxy<Addable>;

#else

#ifdef MULTI_FUNCS
#define DEFINE_FUNC(name) virtual int name() = 0;
#else 
#define DEFINE_FUNC(name) 
#endif

struct base
{
    virtual int add() = 0;
    DEFINE_FUNC(add1)
    DEFINE_FUNC(add2)
    DEFINE_FUNC(add3)
    DEFINE_FUNC(add4)
    DEFINE_FUNC(add5)
    DEFINE_FUNC(add6)
    DEFINE_FUNC(add7)
    DEFINE_FUNC(add8)
    DEFINE_FUNC(add9)
    DEFINE_FUNC(add10)
    DEFINE_FUNC(add11)
    DEFINE_FUNC(add12)
    DEFINE_FUNC(add13)
    DEFINE_FUNC(add14)
    DEFINE_FUNC(add15)
    virtual ~base() = default;
};

using type = std::unique_ptr<base>;

#endif

#undef DEFINE_FUNC

void test_dynamic_dispatch(std::vector<type> &range);
