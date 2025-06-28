typedef unsigned char boolean; /* values are TRUE or FALSE */
typedef unsigned char byte; /* values are 0-255 */
typedef byte *byteptr; /* pointer to byte */
typedef char *string; /* pointer to ASCII character string */
typedef unsigned short word16; /* values are 0-65535 */
typedef unsigned long word32; /* values are 0-4294967295 */

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif /* if TRUE not already defined */

#ifndef min /* if min macro not already defined */
#define min(a, b)((a) < (b) ? (a) : (b))
#define max(a, b)((a) > (b) ? (a) : (b))
#endif /* if min macro not already defined */

#define IDEAKEYSIZE 16
#define IDEABLOCKSIZE 8
#define IDEAROUNDS 8
#define IDEAKEYLEN (6 * IDEAROUNDS + 4)

typedef struct {
  word16 ek[IDEAKEYLEN], dk[IDEAKEYLEN];
}
idea_ctx;
/* End includes for IDEA.C */

#ifdef IDEA32 /* Use >16-bit temporaries */
#define low16(x)((x) & 0xFFFF)
typedef unsigned int uint16; /* at LEAST 16 bits, maybe more */
#else
#define low16(x)(x) /* this is only ever applied to uint16's */
typedef word16 uint16;
#endif


#ifdef SMALL_CACHE
static uint16 mul(register uint16 a, register uint16 b) {
  register word32 p;
  p = (word32) a * b;
  if (p) {
    b = low16(p);
    a = p >> 16;
    return (b - a) + (b < a);
  } else if (a) {
    return 1 - b;
  } else {
    return 1 - a;
  }
} /* mul */


#endif /* SMALL_CACHE */
static uint16 mulInv(uint16 x) {
  uint16 t0, t1;
  uint16 q, y;
  if (x <= 1)
    return x; /* 0 and 1 are self-inverse */
  t1 = 0x10001 L / x; /* Since x >= 2, this fits into 16 bits */
  y = 0x10001 L % x;
  if (y == 1)
    return low16(1 - t1);
  t0 = 1;
  do {
    q = x / y;
    x = x % y;
    t0 += q * t1;
    if (x == 1)
      return t0;
    q = y / x;
    y = y % x;
    t1 += q * t0;
  } while (y != 1);
  return low16(1 - t1);
} /* mukInv */


static void ideaExpandKey(byte const *userkey, word16 *EK) {
  int i, j;
  for (j = 0; j < 8; j++) {
    EK[j] = (userkey[0] << 8) + userkey[1];
    userkey += 2;
  }
  for (i = 0; j < IDEAKEYLEN; j++) {
    i++;
    EK[i + 7] = EK[i & 7] << 9 | EK[i + 1 & 7] >> 7;
    EK += i & 8;
    i &= 7;
  }
} /* ideaExpandKey */


static void ideaInvertKey(word16 const *EK, word16 DK[IDEAKEYLEN]) {
  int i;
  uint16 t1, t2, t3;
  word16 temp[IDEAKEYLEN];
  word16 * p = temp + IDEAKEYLEN;
  t1 = mulInv(*EK++);
  t2 = - *EK++;
  t3 = - *EK++;
  *--p = mulInv(*EK++);
  *--p = t3;
  *--p = t2;
  *--p = t1;
  for (i = 0; i < IDEAROUNDS - 1; i++) {
    t1 = *EK++;
    *--p = *EK++;
    *--p = t1;
    t1 = mulInv(*EK++);
    t2 = - *EK++;
    t3 = - *EK++;
    *--p = mulInv(*EK++);
    *--p = t2;
    *--p = t3;
    *--p = t1;
  }
  t1 = *EK++;
  *--p = *EK++;
  *--p = t1;
  t1 = mulInv(*EK++);
  t2 = - *EK++;
  t3 = - *EK++;
  *--p = mulInv(*EK++);
  *--p = t3;
  *--p = t2;
  *--p = t1;

  /* Copy and destroy temp copy */
  memcpy(DK, temp, sizeof(temp));
  for (i = 0; i < IDEAKEYLEN; i++)
    temp[i] = 0;
} /* ideaInvertKey */

#ifdef SMALL_CACHE
#define MUL(x, y)(x = mul(low16(x), y))
#else /* !SMALL_CACHE */
#ifdef AVOID_JUMPS
#define MUL(x, y)\
  (x = low16(x - 1), t16 = low16((y) - 1), \
    t32 = (word32) x * t16 + x + t16 + 1, \
    x = low16(t32), \
    t16 = t32 >> 16, \
    x = (x - t16) + (x < t16))

#else /* !AVOID_JUMPS (default) */
#define MUL(x, y)\\
  ((t16 = (y))\ ?
    \
    (x = low16(x))\ ?
    \
    t32 = (word32) x * t16, \\
    x = low16(t32), \\
    t16 = t32 >> 16, \\
    x = (x - t16) + (x < t16)\\ :
    \
    (x = 1 - t16)\\ :
    \
    (x = 1 - x))
#endif
#endif

static void ideaCipher(byte *inbuf, byte *outbuf, word16 *key) {
  register uint16 x1, x2, x3, x4, s2, s3;
  word16 * in , * out;

  #ifndef SMALL_CACHE
  register uint16 t16; /* Temporaries needed by MUL macro */
  register word32 t32;
  #endif

  int r = IDEAROUNDS; in = (word16* ) inbuf;
  x1 = *in++;
  x2 = *in++;
  x3 = *in++;
  x4 = *in;

  #ifndef HIGHFIRST
  x1 = (x1 >> 8) | (x1 << 8);
  x2 = (x2 >> 8) | (x2 << 8);
  x3 = (x3 >> 8) | (x3 << 8);
  x4 = (x4 >> 8) | (x4 << 8);
  #endif

  do {
    MUL(x1, *key++);
    x2 += *key++;
    x3 += *key++;
    MUL(x4, *key++);
    s3 = x3;
    x3 ^= x1;
    MUL(x3, *key++);
    s2 = x2;
    x2 ^= x4;
    x2 += x3;
    MUL(x2, *key++);
    x3 += x2;
    x1 ^= x2;
    x4 ^= x3;
    x2 ^= s3;
    x3 ^= s2;
  } while (--r);

  MUL(x1, *key++);
  x3 += *key++;
  x2 += *key++;
  MUL(x4, *key);
  out = (word16*) outbuf;

  #ifdef HIGHFIRST
    *out++ = x1;
    *out++ = x3;
    *out++ = x2;
    *out = x4;
  #else /* !HIGHFIRST */
    *out++ = (x1 >> 8) | (x1 << 8);
    *out++ = (x3 >> 8) | (x3 << 8);
    *out++ = (x2 >> 8) | (x2 << 8);
    *out = (x4 >> 8) | (x4 << 8);
  #endif
} /* ideaCipher */


void idea_key(idea_ctx *c, unsigned char *key) {
  ideaExpandKey(key, c -> ek);
  ideaInvertKey(c -> ek, c -> dk);
}

void idea_enc(idea_ctx * c, unsigned char *data, int blocks) {
  int i;
  unsigned char * d = data;
  for (i = 0; i < blocks; i++) {
    ideaCipher(d, d, c -> ek);
    d += 8;
  }
}

void idea_dec(idea_ctx * c, unsigned char *data, int blocks) {
  int i;
  unsigned char *d = data;
  for (i = 0; i < blocks; i++) {
    ideaCipher(d, d, c -> dk);
    d += 8;
  }
}

#include <stdio.h>
#ifndef BLOCKS
#ifndef KBYTES
#define KBYTES 1024
#endif
#define BLOCKS(64 * KBYTES)
#endif
int main(void) {
  /* Test driver for IDEA cipher */
  int i, j, k;
  idea_ctx c;
  byte userkey[16];
  word16 EK[IDEAKEYLEN], DK[IDEAKEYLEN];
  byte XX[8], YY[8], ZZ[8];
  word32 long_block[10]; /* 5 blocks */
  long l;
  char *lbp;

  /* Make a sample user key for testing... */
  for (i = 0; i < 16; i++)
    userkey[i] = i + 1;
  idea_key(&c, userkey);

  /* Make a sample plaintext pattern for testing... */
  for (k = 0; k < 8; k++)
    XX[k] = k;
  idea_enc(&c, XX, 1); /* encrypt */
  lbp = (unsigned char* ) long_block;

  for (i = 0; i < 10; i++)
    long_block[i] = i;
  idea_enc(&c, lbp, 5);

  for (i = 0; i < 10; i += 2)
    printf("Block %01d = %08lx %08lx.\n", i / 2, long_block[i],
      long_block[i + 1]);
  idea_dec(&c, lbp, 3);
  idea_dec(&c, lbp + 24, 2);

  for (i = 0; i < 10; i += 2)
    printf("Block %01d = %08lx %08lx.\n", i / 2, long_block[i],
      long_block[i + 1]);

  return 0; /* normal exit */
} /* main */