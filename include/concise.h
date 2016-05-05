#include <iostream>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "conciseutil.h"

template<bool wah_mode>
class WordIterator;

/**
 * wah_mode:
 * true for a WAH bitset,
 * false for a Concise bitset,
 */
template<bool wah_mode = false>
class ConciseSet {

public:

	/**
	 * Creates an empty integer set
	 */
	ConciseSet() :
			words(), last(-1), lastWordIndex(-1) {
	}

	ConciseSet(const ConciseSet& cs) :
			words(cs.words), last(cs.last), lastWordIndex(cs.lastWordIndex) {
	}

	bool isEmpty() const {
		return lastWordIndex == -1;
	}

	size_t sizeInBytes() const {
		return (words.size() + 1) * sizeof(uint32_t);
	}

	void swap(ConciseSet<wah_mode> & other) {
		this->words.swap(other.words);
		uint32_t tmplast = this->last;
		this->last = other.last;
		other.last = tmplast;

		int32_t tmplwi = this->lastWordIndex;
		this->lastWordIndex = other.lastWordIndex;
		other.lastWordIndex = tmplwi;
	}

	ConciseSet<wah_mode> logicaland(const ConciseSet<wah_mode> & other) const {
		if (isEmpty() || other.isEmpty())
			return ConciseSet<wah_mode>();
		ConciseSet res;
		res.words.resize(
				1
						+ std::min(
								(uint32_t)(
										this->lastWordIndex
												+ other.lastWordIndex + 2),
								maxLiteralLengthDivision(
										std::max(this->last, other.last))
										<< (wah_mode ? 1 : 0)));

		// scan "this" and "other"
		WordIterator<wah_mode> thisItr(*this);
		WordIterator<wah_mode> otherItr(other);
		while (true) {
			if (!thisItr.IsLiteral) {
				if (!otherItr.IsLiteral) {
					int minCount = std::min(thisItr.count, otherItr.count);
					res.appendFill(minCount, thisItr.word & otherItr.word);
					if (!thisItr.prepareNext(minCount)
							| !otherItr.prepareNext(minCount)) // NOT ||
						break;
				} else {
					res.appendLiteral(thisItr.toLiteral() & otherItr.word);
					thisItr.word--;
					if (!thisItr.prepareNext(1) | !otherItr.prepareNext()) // do NOT use "||"
						break;
				}
			} else if (!otherItr.IsLiteral) {
				res.appendLiteral(thisItr.word & otherItr.toLiteral());
				otherItr.word--;
				if (!thisItr.prepareNext() | !otherItr.prepareNext(1)) // do NOT use  "||"
					break;
			} else {
				res.appendLiteral(thisItr.word & otherItr.word);
				if (!thisItr.prepareNext() | !otherItr.prepareNext()) // do NOT use  "||"
					break;
			}
		}

		bool invalidLast = true;

		// remove trailing zeros
		res.trimZeros();
		if (res.isEmpty())
			return res;

		// compute the greatest element
		if (invalidLast)
			res.updateLast();

		// compact the memory
		res.shrink_to_fit();

		return res;
	}

	ConciseSet<wah_mode> logicalor(const ConciseSet<wah_mode> & other) const {
		if (this->isEmpty())
			return ConciseSet<wah_mode>(other);
		if (other.isEmpty())
			return ConciseSet<wah_mode>(*this);
		ConciseSet res;
		res.words.resize(
				1
						+ std::min(
								(uint32_t)(
										this->lastWordIndex
												+ other.lastWordIndex + 2),
								maxLiteralLengthDivision(
										std::max(this->last, other.last))
										<< (wah_mode ? 1 : 0)));

		// scan "this" and "other"
		WordIterator<wah_mode> thisItr(*this);
		WordIterator<wah_mode> otherItr(other);
		while (true) {
			if (!thisItr.IsLiteral) {
				if (!otherItr.IsLiteral) {
					int minCount = std::min(thisItr.count, otherItr.count);
					res.appendFill(minCount, thisItr.word | otherItr.word);
					if (!thisItr.prepareNext(minCount)
							| !otherItr.prepareNext(minCount)) // NOT ||
						break;
				} else {
					res.appendLiteral(thisItr.toLiteral() | otherItr.word);
					thisItr.word--;
					if (!thisItr.prepareNext(1) | !otherItr.prepareNext()) // do NOT use "||"
						break;
				}
			} else if (!otherItr.IsLiteral) {
				res.appendLiteral(thisItr.word | otherItr.toLiteral());
				otherItr.word--;
				if (!thisItr.prepareNext() | !otherItr.prepareNext(1)) // do NOT use  "||"
					break;
			} else {
				res.appendLiteral(thisItr.word | otherItr.word);
				if (!thisItr.prepareNext() | !otherItr.prepareNext()) // do NOT use  "||"
					break;
			}
		}

		bool invalidLast = true;

		res.last = std::max(this->last, other.last);
		invalidLast = false;
		invalidLast |= thisItr.flush(res);
		invalidLast |= otherItr.flush(res);

		// remove trailing zeros
		res.trimZeros();
		if (res.isEmpty())
			return res;

		// compute the greatest element
		if (invalidLast)
			res.updateLast();

		// compact the memory
		res.shrink_to_fit();

		return res;

	}

	void clear() {
		reset();
	}

	void add(uint32_t e) {
		// range check
		if (e > MAX_ALLOWED_INTEGER) {
			std::cerr << "max integer allowed is " << MAX_ALLOWED_INTEGER << std::endl;
			throw std::runtime_error("out of bound value");
		}
		// the element can be simply appended
		if ((int32_t) e > last) {
			append(e);
			return;
		}
		if ((int32_t) e == last)
			return;
		assert(false); // we do not test this case SHIT
		// check if the element can be put in a literal word
		uint32_t blockIndex = maxLiteralLengthDivision(e);
		uint32_t bitPosition = maxLiteralLengthModulus(e);
		for (int i = 0; i <= lastWordIndex && blockIndex >= 0; i++) {
			uint32_t w = words[i];
			if (isLiteral(w)) {
				// check if the current literal word is the "right" one
				if (blockIndex == 0) {
					// bit already set
					if ((w & (1 << bitPosition)) != 0)
						return;

					// By adding the bit we potentially create a sequence:
					// -- If the literal is made up of all zeros, it definitely
					//    cannot be part of a sequence (otherwise it would not have
					//    been created). Thus, we can create a 1-bit literal word
					// -- If there are MAX_LITERAL_LENGTH - 2 set bits, by adding
					//    the new one we potentially allow for a 1's sequence
					//    together with the successive word
					// -- If there are MAX_LITERAL_LENGTH - 1 set bits, by adding
					//    the new one we potentially allow for a 1's sequence
					//    together with the successive and/or the preceding words
					if (!wah_mode) {
						uint32_t bitCount = getLiteralBitCount(w);
						if (bitCount >= MAX_LITERAL_LENGTH - 2)
							break;
					} else {
						if (containsOnlyOneBit(~w) || w == ALL_ONES_LITERAL)
							break;
					}

					// set the bit
					words[i] |= 1 << bitPosition;
					return;
				}

				blockIndex--;
			} else {
				if (wah_mode) {
					if (isOneSequence(w) && (blockIndex <= getSequenceCount(w)))
						return;
				} else {
					// if we are at the beginning of a sequence, and it is
					// a set bit, the bit already exists
					if (blockIndex == 0
							&& (getLiteral(w) & (1 << bitPosition)) != 0)
						return;

					// if we are in the middle of a sequence of 1's, the bit already exist
					if ((blockIndex > 0) && (blockIndex <= getSequenceCount(w))
							&& isOneSequence(w))
						return;
				}
				// next word
				blockIndex -= getSequenceCount(w) + 1;
			}
		}

		// the bit is in the middle of a sequence or it may cause a literal to
		// become a sequence, thus the "easiest" way to add it is by ORing
		ConciseSet<wah_mode> tmp;
		tmp.add(e);
		ConciseSet<wah_mode> newbitmap = this->logicalor(tmp);
		this->swap(newbitmap);
	}

	void describe() const {
		printf("{cardinality = %d, \n", size());
		for (int i = 0; i <= lastWordIndex; i++) {

			const uint32_t w = words[i];

			const uint32_t t = w & UINT32_C(0xC0000000); // the first two bits...
			switch (t) {
			case UINT32_C(0x80000000):	// LITERAL
			case UINT32_C(0xC0000000):	// LITERAL
				// check if the current literal word is the "right" one
				printf("{literal word %u}\n", getLiteralBits(w));

				break;
			case UINT32_C(0x00000000):	// ZERO SEQUENCE
				printf("{zero sequence:");
				if (!wah_mode) {
					printf(
							"concise word with single 1-bit at %d (none if -1), \n",
							((w >> 25) - 1));
				}
				printf(" length= %u 31-bit words} \n", getSequenceCount(w) + 1);
				break;
			case UINT32_C(0x40000000):	// ONE SEQUENCE
				printf("{one sequence:");
				if (!wah_mode) {
					printf(
							"concise word with single 0-bit at %d (none if -1), \n",
							((UINT32_C(0x0000001F) & (w >> 25)) - 1));

				}
				printf(" length= %u 31-bit words }\n", getSequenceCount(w) + 1);
				break;
			default:
				assert(false);
			}
		}

		printf("}\n");
	}

	bool contains(uint32_t o) const {
		if (isEmpty() || ((int32_t) o > last) || (o > MAX_ALLOWED_INTEGER)) {
			return false;
		}

		// check if the element is within a literal word
		int32_t block = (int32_t) maxLiteralLengthDivision(o);
		uint32_t bit = maxLiteralLengthModulus(o);
		assert(block * 31 + bit == o);

		for (int i = 0; i <= lastWordIndex; i++) {

			const uint32_t w = words[i];
			const uint32_t t = w & UINT32_C(0xC0000000); // the first two bits...
			switch (t) {
			case UINT32_C(0x80000000):	// LITERAL
			case UINT32_C(0xC0000000):	// LITERAL
				// check if the current literal word is the "right" one
				if (block == 0)
					return (w & (1 << bit)) != 0;
				block--;
				break;
			case UINT32_C(0x00000000):	// ZERO SEQUENCE
				if (!wah_mode)
					if ((block == 0) && ((w >> 25) - 1) == bit)
						return true;
				block -= getSequenceCount(w) + 1;
				if (block < 0)
					return false;
				break;
			case UINT32_C(0x40000000):	// ONE SEQUENCE
				if (!wah_mode)
					if ((block == 0)
							&& (((UINT32_C(0x0000001F) & (w >> 25)) - 1))
									== bit)
						return false;
				block -= getSequenceCount(w) + 1;
				if (block < 0)
					return true;
				break;
			}
		}
		// no more words
		return false;
	}

	uint32_t size() const {
		uint32_t size = 0;
		for (int i = 0; i <= lastWordIndex; i++) {
			uint32_t w = words[i];
			if (isLiteral(w)) {
				size += getLiteralBitCount(w);
			} else {
				if (isZeroSequence(w)) {
					if (!isSequenceWithNoBits(w))
						size++;
				} else {
					size += maxLiteralLengthMultiplication(
							getSequenceCount(w) + 1);
					if (!isSequenceWithNoBits(w))
						size--;
				}
			}
		}
		return size;
	}

	std::vector<uint32_t> words;

	/**
	 * Most significant set bit within the uncompressed bit string.
	 */
	int32_t last;

	/**
	 * Index of the last word in words
	 */
	int32_t lastWordIndex;

	/**
	 * Resets to an empty set
	 */
	void reset() {
		words.clear();
		words.shrink_to_fit();
		last = -1;
		lastWordIndex = -1;
	}

	uint32_t getLiteral(uint32_t word) {
		if (isLiteral(word))
			return word;

		if (wah_mode)
			return isZeroSequence(word) ? ALL_ZEROS_LITERAL : ALL_ONES_LITERAL;

		// get bits from 30 to 26 and use them to set the corresponding bit
		// NOTE: "1 << (word >> 25)" and "1 << ((word >> 25) & 0x0000001F)" are equivalent
		// NOTE: ">> 1" is required since 00000 represents no bits and 00001 the LSB bit set
		uint32_t literal = (1 << (word >> 25)) >> 1;
		return isZeroSequence(word) ?
				(ALL_ZEROS_LITERAL | literal) : (ALL_ONES_LITERAL & ~literal);
	}

	void clearBitsAfterInLastWord(int lastSetBit) {
		words[lastWordIndex] &= ALL_ZEROS_LITERAL
				| (UINT32_C(0xFFFFFFFF) >> (31 - lastSetBit));
	}

	void ensureCapacity(size_t index) {
		if (words.size() > index)
			return;
		words.resize(index + 1);
	}

	void shrink_to_fit() {
		words.shrink_to_fit();
	}

	void trimZeros() {
		// loop over ALL_ZEROS_LITERAL words
		uint32_t w;
		do {
			w = words[lastWordIndex];
			if (w == ALL_ZEROS_LITERAL) {
				lastWordIndex--;
			} else if (isZeroSequence(w)) {
				if (wah_mode || isSequenceWithNoBits(w)) {
					lastWordIndex--;
				} else {
					// convert the sequence in a 1-bit literal word
					words[lastWordIndex] = getLiteral(w);
					return;
				}
			} else {
				// one sequence or literal
				return;
			}
			if (lastWordIndex < 0) {
				reset();
				return;
			}
		} while (true);
	}

	void append(uint32_t i) {
		// special case of empty set
		if (isEmpty()) {
			uint32_t zeroBlocks = maxLiteralLengthDivision(i);
			if (zeroBlocks == 0) {
				words.resize(1);
				lastWordIndex = 0;
			} else if (zeroBlocks == 1) {
				words.resize(2);
				lastWordIndex = 1;
				words[0] = ALL_ZEROS_LITERAL;
			} else {
				words.resize(2);
				lastWordIndex = 1;
				words[0] = zeroBlocks - 1;
			}
			last = i;
			words[lastWordIndex] = ALL_ZEROS_LITERAL
					| (1 << maxLiteralLengthModulus(i));
			return;
		}

		// position of the next bit to set within the current literal
		uint32_t bit = maxLiteralLengthModulus(last) + i - last;

		// if we are outside the current literal, add zeros in
		// between the current word and the new 1-bit literal word
		if (bit >= MAX_LITERAL_LENGTH) {
			int zeroBlocks = maxLiteralLengthDivision(bit) - 1;
			bit = maxLiteralLengthModulus(bit);
			if (zeroBlocks == 0) {
				ensureCapacity(lastWordIndex + 1);
			} else {
				ensureCapacity(lastWordIndex + 2);
				appendFill(zeroBlocks, 0);
			}
			appendLiteral(ALL_ZEROS_LITERAL | 1 << bit);
		} else {
			words[lastWordIndex] |= 1 << bit;
			if (words[lastWordIndex] == ALL_ONES_LITERAL) {
				lastWordIndex--;
				appendLiteral(ALL_ONES_LITERAL);
			}
		}

		// update other info
		last = i;
	}

	void appendLiteral(uint32_t word) {
		// when we have a zero sequence of the maximum lenght (that is,
		// 00.00000.1111111111111111111111111 = 0x01FFFFFF), it could happen
		// that we try to append a zero literal because the result of the given operation must be an
		// empty set. Whitout the following test, we would have increased the
		// counter of the zero sequence, thus obtaining 0x02000000 that
		// represents a sequence with the first bit set!
		if (lastWordIndex == 0 && word == ALL_ZEROS_LITERAL
				&& words[0] == UINT32_C(0x01FFFFFF))
			return;

		// first addition
		if (lastWordIndex < 0) {
			words[lastWordIndex = 0] = word;
			return;
		}

		const uint32_t lastWord = words[lastWordIndex];
		if (word == ALL_ZEROS_LITERAL) {
			if (lastWord == ALL_ZEROS_LITERAL)
				words[lastWordIndex] = 1;
			else if (isZeroSequence(lastWord))
				words[lastWordIndex]++;
			else if (!wah_mode && containsOnlyOneBit(getLiteralBits(lastWord)))
				words[lastWordIndex] = 1
						| ((1 + __builtin_ctz(lastWord)) << 25);
			else
				words[++lastWordIndex] = word;
		} else if (word == ALL_ONES_LITERAL) {
			if (lastWord == ALL_ONES_LITERAL)
				words[lastWordIndex] = SEQUENCE_BIT | 1;
			else if (isOneSequence(lastWord))
				words[lastWordIndex]++;
			else if (!wah_mode && containsOnlyOneBit(~lastWord))
				words[lastWordIndex] = SEQUENCE_BIT | 1
						| ((1 + __builtin_ctz(~lastWord)) << 25);
			else
				words[++lastWordIndex] = word;
		} else {
			words[++lastWordIndex] = word;
		}
	}

	void appendFill(uint32_t length, uint32_t fillType) {

		fillType &= SEQUENCE_BIT;

		// it is actually a literal...
		if (length == 1) {
			appendLiteral(fillType == 0 ? ALL_ZEROS_LITERAL : ALL_ONES_LITERAL);
			return;
		}

		// empty set
		if (lastWordIndex < 0) {
			words[lastWordIndex = 0] = fillType | (length - 1);
			return;
		}

		uint32_t lastWord = words[lastWordIndex];
		if (isLiteral(lastWord)) {
			if (fillType == 0 && lastWord == ALL_ZEROS_LITERAL) {
				words[lastWordIndex] = length;
			} else if (fillType == SEQUENCE_BIT
					&& lastWord == ALL_ONES_LITERAL) {
				words[lastWordIndex] = SEQUENCE_BIT | length;
			} else if (!wah_mode) {
				if (fillType == 0
						&& containsOnlyOneBit(getLiteralBits(lastWord))) {
					words[lastWordIndex] = length
							| ((1 + __builtin_ctz(lastWord)) << 25);
				} else if (fillType == SEQUENCE_BIT
						&& containsOnlyOneBit(~lastWord)) {
					words[lastWordIndex] = SEQUENCE_BIT | length
							| ((1 + __builtin_ctz(~lastWord)) << 25);
				} else {
					words[++lastWordIndex] = fillType | (length - 1);
				}
			} else {
				words[++lastWordIndex] = fillType | (length - 1);
			}
		} else {
			if ((lastWord & UINT32_C(0xC0000000)) == fillType)
				words[lastWordIndex] += length;
			else
				words[++lastWordIndex] = fillType | (length - 1);
		}
	}

	void updateLast() {
		last = 0;
		for (int32_t i = 0; i <= lastWordIndex; i++) {
			uint32_t w = words[i];
			if (isLiteral(w))
				last += MAX_LITERAL_LENGTH;
			else
				last += maxLiteralLengthMultiplication(getSequenceCount(w) + 1);
		}

		uint32_t w = words[lastWordIndex];
		if (isLiteral(w))
			last -= __builtin_clz(getLiteralBits(w));
		else
			last--;
	}

};

template<bool wah_mode = false>
class WordIterator {
public:
	/**
	 * Initialize data
	 */
	WordIterator(const ConciseSet<wah_mode> & p) :
			IsLiteral(false), parent(p), index(-1), word(0), count(0) {
		prepareNext();
	}

	/**
	 * @return true if there is no current word
	 */
	bool exhausted() {
		return index > parent.lastWordIndex;
	}

	bool prepareNext(int c) {
		count -= c;
		if (count == 0)
			return prepareNext();
		return true;
	}

	bool prepareNext() {
		if (!wah_mode && IsLiteral && count > 1) {
			count--;
			IsLiteral = false;
			word = getSequenceWithNoBits(parent.words[index]) - 1;
			return true;
		}

		index++;
		if (index > parent.lastWordIndex)
			return false;
		word = parent.words[index];
		IsLiteral = isLiteral(word);
		if (!IsLiteral) {
			count = getSequenceCount(word) + 1;
			if (!wah_mode && !isSequenceWithNoBits(word)) {
				IsLiteral = true;
				int bit = (1 << ((word >> 25)%32)) >> 1;
				word = isZeroSequence(word) ?
						(ALL_ZEROS_LITERAL | bit) : (ALL_ONES_LITERAL & ~bit);
			}
		} else {
			count = 1;
		}
		return true;
	}

	uint32_t toLiteral() {
		return ALL_ZEROS_LITERAL
				| (uint32_t)(((int32_t) word << 1) >> MAX_LITERAL_LENGTH);
	}

	/** true if {@link #word} is a literal */
	bool IsLiteral;
	const ConciseSet<wah_mode> & parent;

	/** current word index */
	int32_t index;
	/** copy of the current word */
	uint32_t word;

	/** number of blocks in the current word (1 for literals, > 1 for sequences) */
	uint32_t count;

	bool flush(ConciseSet<wah_mode>& s) {
		// nothing to flush
		if (exhausted())
			return false;

		// try to "compress" the first few words
		do {
			if (IsLiteral)
				s.appendLiteral(word);
			else
				s.appendFill(count, word);
		} while (prepareNext() && s.words[s.lastWordIndex] != word);

		// copy remaining words "as-is"
		int32_t delta = parent.lastWordIndex - index + 1;
		for (int i = 0; i < delta; ++i) {
			s.words[s.lastWordIndex + 1 + i] = parent.words[index + i];
		}
		s.lastWordIndex += delta;
		s.last = parent.last;
		return true;
	}
};
