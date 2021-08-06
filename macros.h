#include <stdio.h>
#include <math.h>

#define tst_debugging printf

#define true 1
#define false 0

#define c_assert(e) ((e) ? (true) : (tst_debugging("%s, %d: assertion ’%s’ failed\n", __FILE__, __LINE__, #e), false))

#define c_assert_float(v, min, max) \
  (c_assert(!isnan(v) && v > min && v < max ))

#define c_assert_vec2(v, min, max) \
  (c_assert(!isnan(v.x) && !isnan(v.y) && v.x > min && v.x < max && v.y > min && v.y < max))
