#include "buddy.c"
#include <bits/stdc++.h>
using namespace std;

void test1(void) {
  uint8_t *p0, *p1, *p2;
  static uint8_t memory[3 * 1048576];
  int pending_block;
  alloc_init(memory, 600);
  assert((p0 = (uint8_t *)alloc_malloc(1)) != NULL);
  memset(p0, 0, 1);
  assert((p1 = (uint8_t *)alloc_malloc(2)) != NULL);
  memset(p1, 0, 2);
  assert((p2 = (uint8_t *)alloc_malloc(64)) != NULL);
  memset(p2, 0, 64);
  assert(alloc_free(p0));
  assert(alloc_free(p1));
  assert(alloc_free(p2));
  alloc_done(&pending_block);
  assert(pending_block == 0);
}

void test2(void) {
  uint8_t *p0, *p1;
  static uint8_t memory[3 * 1048576];
  alloc_init(memory, 500);
  assert((p0 = (uint8_t *)alloc_malloc(200)) != NULL);
  assert((p1 = (uint8_t *)alloc_malloc(100)) != NULL);
}

void test3(void) {
  static uint8_t memory[1000000000];
  alloc_init(memory, 100000000);
  std::vector<void *> ptrs;
  for (size_t i = 0; i < 10000; ++i) {
    int *p;
    assert(p = (int *)alloc_malloc(4));
    *p = 1;
    ptrs.push_back(p);
  }

  for (auto x : ptrs)
    assert(*(int *)x == 1);

  for (auto x : ptrs)
    assert(alloc_free(x));
  int x;
  alloc_done(&x);
  assert(x == 0);
  ptrs.clear();
  alloc_init(memory, 100000000);

  for (size_t i = 0; i < 10000; ++i) {
    int *p;
    assert(p = (int *)alloc_malloc(4));
    *p = 2;
    ptrs.push_back(p);
  }

  for (auto x : ptrs)
    assert(*(int *)x == 2);

  for (auto x : ptrs)
    assert(alloc_free(x));
  alloc_done(&x);
  assert(x == 0);
}

int main(void) {
  test1();
  test2();
  test3();
}
