#ifndef CONCISEUTIL_H
#define CONCISEUTIL_H
#include <cstdint>

template <class T>
static inline int32_t max(T x, T y) {
    return x < y ? y : x;
}

template <class T>
static inline int32_t min(T x, T y) {
    return x < y ? x : y;
}


/**
 * The highest representable integer.
 * <p>
 * Its value is computed as follows. The number of bits required to
 * represent the longest sequence of 0's or 1's is
 * <tt>ceil(log<sub>2</sub>(({@link Integer#MAX_VALUE} - 31) / 31)) = 27</tt>.
 * Indeed, at least one literal exists, and the other bits may all be 0's or
 * 1's, that is <tt>{@link Integer#MAX_VALUE} - 31</tt>. If we use:
 * <ul>
 * <li> 2 bits for the sequence type;
 * <li> 5 bits to indicate which bit is set;
 * </ul>
 * then <tt>32 - 5 - 2 = 25</tt> is the number of available bits to
 * represent the maximum sequence of 0's and 1's. Thus, the maximal bit that
 * can be set is represented by a number of 0's equals to
 * <tt>31 * (1 << 25)</tt>, followed by a literal with 30 0's and the
 * MSB (31<sup>st</sup> bit) equal to 1
 */
constexpr static int32_t  MAX_ALLOWED_INTEGER = 31 * (INT32_C(1) << 25) + 30; // 1040187422


/**
 * Maximum number of representable bits within a literal
 */
constexpr static uint32_t  MAX_LITERAL_LENGTH = UINT32_C(31);

/**
 * Literal that represents all bits set to 1 (and MSB = 1)
 */
constexpr static uint32_t  ALL_ONES_LITERAL = UINT32_C(0xFFFFFFFF);

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
 * Calculates the modulus division by 31 in a faster way than using <code>n % 31</code>
 * <p>
 * This method of finding modulus division by an integer that is one less
 * than a power of 2 takes at most <tt>O(lg(32))</tt> time. The number of operations
 * is at most <tt>12 + 9 * ceil(lg(32))</tt>.
 * <p>
 * See <a
 * href="http://graphics.stanford.edu/~seander/bithacks.html">http://graphics.stanford.edu/~seander/bithacks.html</a>
 *
 * @param n
 *            number to divide
 * @return <code>n % 31</code>
 */
static inline uint32_t maxLiteralLengthModulus(uint32_t n) {
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
}



/**
 * Calculates the multiplication by 31 in a faster way than using <code>n * 31</code>
 *
 * @param n
 *            number to multiply
 * @return <code>n * 31</code>
 */
static inline uint32_t maxLiteralLengthMultiplication(uint32_t n) {
    return (n << 5) - n;
}

/**
 * Calculates the division by 31
 *
 * @param n
 *            number to divide
 * @return <code>n / 31</code>
 */
static inline uint32_t maxLiteralLengthDivision(uint32_t n) {
    return n / 31;
}




/**
 * Checks whether a word is a literal one
 *
 * @param word
 *            word to check
 * @return <code>true</code> if the given word is a literal word
 */
static inline bool isLiteral(uint32_t word) {
    // "word" must be 1*
    // NOTE: this is faster than "return (word & 0x80000000) == 0x80000000"
    return (word & UINT32_C(0x80000000)) != 0;
}

/**
 * Checks whether a word contains a sequence of 1's
 *
 * @param word
 *            word to check
 * @return <code>true</code> if the given word is a sequence of 1's
 */
static inline bool isOneSequence(uint32_t word) {
    // "word" must be 01*
    return (word & UINT32_C(0xC0000000)) == SEQUENCE_BIT;
}

/**
 * Checks whether a word contains a sequence of 0's
 *
 * @param word
 *            word to check
 * @return <code>true</code> if the given word is a sequence of 0's
 */
static inline bool isZeroSequence(uint32_t word) {
    // "word" must be 00*
    return (word & UINT32_C(0xC0000000)) == 0;
}

/**
 * Checks whether a word contains a sequence of 0's with no set bit, or 1's
 * with no unset bit.
 * <p>
 * <b>NOTE:</b> when {@link #simulateWAH} is <code>true</code>, it is
 * equivalent to (and as fast as) <code>!</code>{@link #isLiteral(int)}
 *
 * @param word
 *            word to check
 * @return <code>true</code> if the given word is a sequence of 0's or 1's
 *         but with no (un)set bit
 */
static inline bool isSequenceWithNoBits(uint32_t word) {
    // "word" must be 0?00000*
    return (word & UINT32_C(0xBE000000)) == UINT32_C(0x00000000);
}

/**
 * Gets the number of blocks of 1's or 0's stored in a sequence word
 *
 * @param word
 *            word to check
 * @return the number of blocks that follow the first block of 31 bits
 */
static inline int getSequenceCount(uint32_t word) {
    // get the 25 LSB bits
    return word & UINT32_C(0x01FFFFFF);
}

/**
 * Clears the (un)set bit in a sequence
 *
 * @param word
 *            word to check
 * @return the sequence corresponding to the given sequence and with no
 *         (un)set bits
 */
static inline uint32_t getSequenceWithNoBits(uint32_t word) {
    // clear 29 to 25 LSB bits
    return (word & UINT32_C(0xC1FFFFFF));
}
/**
 * Returns <code>true</code> when the given 31-bit literal string (namely,
 * with MSB set) contains only one set bit
 *
 * @param literal
 *            literal word (namely, with MSB unset)
 * @return <code>true</code> when the given literal contains only one set
 *         bit
 */
static inline bool containsOnlyOneBit(uint32_t literal) {
    return (literal & (literal - 1)) == 0;
}


/**
 * Gets the position of the flipped bit within a sequence word. If the
 * sequence has no set/unset bit, returns -1.
 * <p>
 * Note that the parameter <i>must</i> a sequence word, otherwise the
 * result is meaningless.
 *
 * @param word
 *            sequence word to check
 * @return the position of the set bit, from 0 to 31. If the sequence has no
 *         set/unset bit, returns -1.
 */
static inline int getFlippedBit(uint32_t word) {
    // get bits from 30 to 26
    // NOTE: "-1" is required since 00000 represents no bits and 00001 the LSB bit set
    return ((word >> 25) & UINT32_C(0x0000001F)) - 1;
}

/**
 * Gets the bits contained within the literal word
 *
 * @param word literal word
 * @return the literal word with the most significant bit cleared
 */
static inline int getLiteralBits(uint32_t word) {
    return ALL_ONES_WITHOUT_MSB & word;
}
/**
 * Gets the number of set bits within the literal word
 *
 * @param word
 *            literal word
 * @return the number of set bits within the literal word
 */
static inline int getLiteralBitCount(uint32_t word) {
    return __builtin_popcount(getLiteralBits(word));
}


#endif
