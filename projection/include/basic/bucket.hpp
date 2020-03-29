#include <float.h>
#include <math.h>

#include "DTB.hpp"

namespace proj {

void ProjB(const datatype* y, datatype* x, const int length, const double a) {
  union DtB* r1 = new DtB[length];
  union DtB* r1_ptr = r1;
  union DtB* r2 = ((y == x) ? (new DtB[length]) : (union DtB*)x);
  union DtB* r2_ptr = r2;
  int illength;
  double tau;
  int currentLength;
  int count = 0;
  int t[257] = {0};
  double s[257] = {0.};
  double minS[257];
  double maxS[257];
  union DtB* tmpswap;
  int* tmp;
  tmp = &t[0];
  tmp++;
  int bucketSize;
  int start;

  int i;
  int over = 0;

  illength = length;
  int depth = DATASIZE - 1;

  for (i = 0; i < 257; ++i) {
    minS[i] = DBL_MAX;
    maxS[i] = DBL_MIN;
  }

  for (i = 0; i < length; i++) {
    const datatype i_v = r1[i].val = y[i];
    const size_t i_b = r1[i].byte[depth];
    ++tmp[i_b];
    s[i_b] += i_v;
    minS[i_b] = std::min(minS[i_b], i_v);
    maxS[i_b] = std::max(maxS[i_b], i_v);
  }

  tau = -a;
  illength = length;
  for (depth = DATASIZE - 1; depth >= 0; depth--) {
    for (i = 1; i < 256; ++i) {  // Count sort.
      tmp[i] = tmp[i] + tmp[i - 1];
    }
    for (i = 0; i < illength; ++i) {
      r2[t[r1[i].byte[depth]]++] = r1[i];
    }

    tmpswap = r2;
    r2 = r1;
    r1 = tmpswap;
    currentLength = illength;

    for (i = 255; i >= 0; --i) {  // t[i] is the starting point of the i+1
                                  // values (because of the ++ )
      start = (i == 0) ? 0 : t[i - 1];
      bucketSize = currentLength - start;
      currentLength -= bucketSize;
      if (bucketSize == 0) {
        continue;
      }
      if (tau / count >
          maxS[i]) {  // Best possible remaining value is dominatied: end
        over = 1;
        break;
      }
      if ((tau + s[i]) / (count + bucketSize) <
          minS[i]) {  // try keeping the min of b
        tau += s[i];
        count += bucketSize;
        continue;
      }
      r1 += start;
      r2 += start;
      illength = bucketSize;
      break;
    }
    depth--;
    if (depth < 0 || over == 1 || i < 0) {
      break;
    }
    for (i = 0; i < 257; ++i) {
      t[i] = 0;
      s[i] = 0.;
      minS[i] = DBL_MAX;
      maxS[i] = DBL_MIN;
    }
    for (i = 0; i < illength; ++i) {
      const datatype i_v = r1[i].val;
      const size_t i_b = r1[i].byte[depth];
      ++tmp[i_b];
      s[i_b] += i_v;
      minS[i_b] = std::min(minS[i_b], i_v);
      maxS[i_b] = std::max(maxS[i_b], i_v);
    }
    depth++;
  }
  tau /= count;
  for (i = 0; i < length; i++) x[i] = (y[i] > tau ? y[i] - tau : 0.0);
  delete[] r1_ptr;
  if (y == x) delete[] r2_ptr; 
}

}  // namespace proj
