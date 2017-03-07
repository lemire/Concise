#ifndef CONCISEUTIL_H
#define CONCISEUTIL_H
#include <cstdint>

/**
 * The highest representable integer.
 */
constexpr static uint32_t MAX_ALLOWED_INTEGER =
    31 * (UINT32_C(1) << 25) + 30; // 1040187422

/**
 * Maximum number of representable bits within a literal
 */
constexpr static uint32_t MAX_LITERAL_LENGTH = UINT32_C(31);

/**
 * Literal that represents all bits set to 1 (and MSB = 1)
 */
constexpr static uint32_t ALL_ONES_LITERAL = UINT32_C(0xFFFFFFFF);

/**
 * Literal that represents all bits set to 0 (and MSB = 1)
 */
constexpr static uint32_t ALL_ZEROS_LITERAL = UINT32_C(0x80000000);

/**
 * All bits set to 1 and MSB = 0
 */
constexpr static uint32_t ALL_ONES_WITHOUT_MSB = UINT32_C(0x7FFFFFFF);

/**
 * Sequence bit
 */
constexpr static uint32_t SEQUENCE_BIT = UINT32_C(0x40000000);

/**
 * Calculates the modulus division by 31 in a faster way than using n % 31
 */
static inline uint32_t maxLiteralLengthModulus(uint32_t n) {
  return n % 31;
  // following code is a bad idea. Compilers can compiler n % 31 to something
  // faster.
  /**
  uint32_t m = (n & UINT32_C(0xC1F07C1F)) + ((n >> 5) & UINT32_C(0xC1F07C1F));
  m = (m >> 15) + (m & UINT32_C(0x00007FFF));
  if (m <= 31)
      return m == 31 ? 0 : m;
  m = (m >> 5) + (m & UINT32_C(0x0000001F));
  if (m <= 31)
      return m == 31 ? 0 : m;
  m = (m >> 5) + (m & UINT32_C(0x0000001F));
  if (m <= 31)
      return m == 31 ? 0 : m;
  m = (m >> 5) + (m & UINT32_C(0x0000001F));
  if (m <= 31)
      return m == 31 ? 0 : m;
  m = (m >> 5) + (m & UINT32_C(0x0000001F));
  if (m <= 31)
      return m == 31 ? 0 : m;
  m = (m >> 5) + (m & UINT32_C(0x0000001F));
  return m == 31 ? 0 : m;
  **/
}

/**
 * Calculates the multiplication by 31 in a faster way than using n * 31
 */
static inline uint32_t maxLiteralLengthMultiplication(uint32_t n) {
  return (n << 5) - n; // a good compiler should do this on its own
}

/**
 * Calculates the division by 31
 */
static inline uint32_t maxLiteralLengthDivision(uint32_t n) { return n / 31; }

/**
 * Checks whether a word is a literal one
 */
static inline bool isLiteral(uint32_t word) {
  // "word" must be 1*
  // NOTE: this is faster than "return (word & 0x80000000) == 0x80000000"
  return (word & UINT32_C(0x80000000)) != 0;
}

/**
 * Checks whether a word contains a sequence of 1's
 */
static inline bool isOneSequence(uint32_t word) {
  // "word" must be 01*
  return (word & UINT32_C(0xC0000000)) == SEQUENCE_BIT;
}

/**
 * Checks whether a word contains a sequence of 0's
 */
static inline bool isZeroSequence(uint32_t word) {
  // "word" must be 00*
  return (word & UINT32_C(0xC0000000)) == 0;
}

/**
 * Checks whether a word contains a sequence of 0's with no set bit, or 1's
 * with no unset bit.
 */
static inline bool isSequenceWithNoBits(uint32_t word) {
  // "word" must be 0?00000*
  return (word & UINT32_C(0xBE000000)) == UINT32_C(0x00000000);
}

/**
 * Gets the number of blocks of 1's or 0's stored in a sequence word
 */
template <bool wah_mode>
static inline uint32_t getSequenceCount(uint32_t word) {
  // get the 25 LSB bits
  return word & (wah_mode? UINT32_C(0x3FFFFFFF) : UINT32_C(0x01FFFFFF));
}


/**
 * Clears the (un)set bit in a sequence
 */
static inline uint32_t getSequenceWithNoBits(uint32_t word) {
  // clear 29 to 25 LSB bits
  return (word & UINT32_C(0xC1FFFFFF));
}
/**
 * Returns true when the given 31-bit literal string (namely,
 * with MSB set) contains only one set bit
 */
static inline bool containsOnlyOneBit(uint32_t literal) {
  return (literal & (literal - 1)) == 0;
}

/**
 * Gets the position of the flipped bit within a sequence word. If the
 * sequence has no set/unset bit, returns -1.
 */
static inline int getFlippedBit(uint32_t word) {
  // get bits from 30 to 26
  // NOTE: "-1" is required since 00000 represents no bits and 00001 the LSB bit
  // set
  return ((word >> 25) & UINT32_C(0x0000001F)) - 1;
}

static inline uint32_t concise_xor(uint32_t literal1, uint32_t literal2) {
  return ALL_ZEROS_LITERAL | (literal1 ^ literal2);
}
static inline uint32_t concise_andnot(uint32_t literal1, uint32_t literal2) {
  return ALL_ZEROS_LITERAL | (literal1 & (~literal2));
}

static inline uint32_t concise_and(uint32_t literal1, uint32_t literal2) {
  return ALL_ZEROS_LITERAL | (literal1 & literal2);
}

/**
 * Gets the bits contained within the literal word
 */
static inline uint32_t getLiteralBits(uint32_t word) {
  return ALL_ONES_WITHOUT_MSB & word;
}
/**
 * Gets the number of set bits within the literal word
 */
static inline int getLiteralBitCount(uint32_t word) {
  return __builtin_popcount(getLiteralBits(word));
}

static inline bool isLiteralZero(uint32_t word) {
  return getLiteralBits(word) == 0;
}

#endif
