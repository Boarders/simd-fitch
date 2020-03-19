#include <emmintrin.h>
#include <smmintrin.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void mmfitch (int len, uint64_t* bv1, uint64_t* bv2, uint64_t* res);
int f (int);

int main (){
  uint64_t l[]   __attribute__((aligned (16))) = {3, 7, 3, 11, 3};
  uint64_t r[]   __attribute__((aligned (16))) = {2, 5, 3, 15, 2};
  uint64_t res[] __attribute__((aligned (16))) = {0, 0, 0, 0 , 0};
  //  res = &l[0];
  int len = 3;
  mmfitch(len, &l[0], &r[0], &res[0]);
  for (int i = 0; i < f(len); i ++){
    printf("%" PRIu64 " ", res[i]);
    }
  printf("\n");
}


void mmfitch (int len, uint64_t* bv1, uint64_t* bv2, uint64_t* res){
  for (int i = 0; i < len; i++){
    __m128i lvals = _mm_loadu_si128((__m128i*) bv1);
    __m128i rvals = _mm_loadu_si128((__m128i*) bv2);
    __m128i __mres;
    if (!_mm_testz_si128(lvals, rvals)){
        // if there is an intersection then return it.
      __mres = _mm_and_si128(lvals, rvals);
      }
    else {
      // otherwise take the union,
      __mres = _mm_or_si128 (lvals, rvals);
    }
    _mm_store_si128((__m128i*) res, __mres);
    bv1 +=2;
    bv2 +=2;
    res +=2;
  }
}

int f (int num) {
  if (num%2==0){
    return num*2;
  }
  else {
    return num*2 - 1;
  }
}
    
  
  
  
  
