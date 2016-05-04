#include <iostream>
#include <cassert>
#include <set>

#include "concise.h"

template<bool ewahmode>
void basictest() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	ConciseSet<ewahmode> test1;
	test1.add(1);
	assert(test1.contains(1));
	test1.add(2);
	assert(test1.contains(2));
	test1.add(3);
	assert(test1.contains(3));
	test1.add(100);
	assert(test1.contains(100));
	test1.add(1000);
	assert(test1.contains(1000));
	assert(test1.size() == 5);
	ConciseSet<ewahmode> test2;
	test2.add(0);
	assert(test2.contains(0));
	test2.add(2);
	assert(test2.contains(2));
	test2.add(3);
	assert(test2.contains(3));
	test2.add(100);
	assert(test2.contains(100));
	test2.add(3000);
	assert(test2.contains(3000));
	assert(test2.size() == 5);
	ConciseSet<ewahmode> tmp;
	tmp = test1.logicalor(test2);
	assert(tmp.size() == 7);
	tmp = test1.logicaland(test2);
	assert(tmp.size() == 3);
	tmp.add(100000);
	assert(tmp.size() == 4);
	tmp.shrink_to_fit();
}

template<bool ewahmode>
void longtest() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	ConciseSet<ewahmode> testc;
	for (int k = 0; k < 1000; ++k) {
		testc.add(k * 2);
		testc.add(k * 2 + 1);
	}
	assert(testc.size() == 2000);
	for (int k = 0; k < 1000; ++k) {
		assert(testc.contains(k * 2));
		assert(testc.contains(k * 2 + 1));
	}
	ConciseSet<ewahmode> test1;
	for (int k = 0; k < 1000; ++k) {
		test1.add(k * 2);
	}
	for (int k = 0; k < 1000; ++k) {
		assert(test1.contains(k * 2));
		assert(!test1.contains(k * 2 + 1));
	}
	assert(test1.size() == 1000);
	ConciseSet<ewahmode> shouldbetest1;
	shouldbetest1 = testc.logicaland(test1);
	assert(shouldbetest1.size() == 1000);
	for (int k = 0; k < 1000; ++k) {
		assert(shouldbetest1.contains(k * 2));
		assert(!shouldbetest1.contains(k * 2 + 1));
	}
	ConciseSet<ewahmode> test2;
	for (int k = 0; k < 1000; ++k) {
		test2.add(k * 2 + 1);
	}
	for (int k = 0; k < 1000; ++k) {
		assert(!test2.contains(k * 2));
		assert(test2.contains(k * 2 + 1));
	}
	assert(test2.size() == 1000);

	ConciseSet<ewahmode> tmp;
	tmp = test1.logicalor(test2);
	assert(tmp.size() == 2000);
	for (int k = 0; k < 1000; ++k) {
		assert(tmp.contains(k * 2));
		assert(tmp.contains(k * 2 + 1));
	}
	tmp = tmp.logicaland(test2);
	assert(tmp.size() == 1000);

	tmp = test1.logicaland(test2);
	assert(tmp.size() == 0);
}

static std::set<uint32_t> unite(std::set<uint32_t> s1, std::set<uint32_t> s2) {
	std::set < uint32_t > answer;
	for (std::set<uint32_t>::iterator i = s1.begin(); i != s1.end(); i++) {
		answer.insert(*i);
	}
	for (std::set<uint32_t>::iterator i = s2.begin(); i != s2.end(); i++) {
		answer.insert(*i);
	}
	return answer;
}

static std::set<uint32_t> intersect(std::set<uint32_t> s1,
		std::set<uint32_t> s2) {
	std::set < uint32_t > answer;
	for (std::set<uint32_t>::iterator i = s1.begin(); i != s1.end(); i++) {
		if (s2.find(*i) != s2.end()) {
			answer.insert(*i);
		}
	}
	return answer;
}

template<bool ewahmode>
static bool equals(std::set<uint32_t> s, ConciseSet<ewahmode> c) {
	if (s.size() != c.size())
		return false;
	for (std::set<uint32_t>::iterator i = s.begin(); i != s.end(); i++) {
		if (!c.contains(*i))
			return false;
	}
	return true;
}

template<bool ewahmode>
void variedtest() {

	std::cout << __PRETTY_FUNCTION__ << std::endl;

	ConciseSet<ewahmode> test1;
	std::set < uint32_t > set1;

	for (int k = 0; k < 1000; ++k) {
		test1.add(k);
		set1.insert(k);
	}
	for (int k = 1000; k < 2000; k += 2) {
		test1.add(k);
		set1.insert(k);
	}
	for (int k = 5000; k < 6000; k += 1) {
		test1.add(k);
		set1.insert(k);
	}
	for (int k = 6500; k < 8000; k += 1) {
		test1.add(k);
		set1.insert(k);
	}

	ConciseSet<ewahmode> test2;
	std::set < uint32_t > set2;
	for (int k = 0; k < 1100; k += 3) {
		test2.add(k);
		set2.insert(k);
	}
	for (int k = 1100; k < 2000; ++k) {
		test2.add(k);
		set2.insert(k);
	}
	for (int k = 5500; k < 6500; ++k) {
		test2.add(k);
		set2.insert(k);
	}
	for (int k = 7500; k < 8100; ++k) {
		test2.add(k);
		set2.insert(k);
	}
	std::set < uint32_t > trueunion = unite(set1, set2);
	std::set < uint32_t > trueinter = intersect(set1, set2);
	ConciseSet<ewahmode> union1;
	ConciseSet<ewahmode> union2;
	union1 = test1.logicalor(test2);
	union2 = test1.logicalor(test2);
	assert(equals(trueunion, union1));
	assert(equals(trueunion, union2));
	ConciseSet<ewahmode> intersect1;
	ConciseSet<ewahmode> intersect2;
	intersect1 = test1.logicaland(test2);
	intersect2 = test1.logicaland(test2);
	assert(equals(trueinter, intersect1));
	assert(equals(trueinter, intersect2));
}

int main() {
	basictest<true>();
	basictest<false>();
	longtest<true>();
	longtest<false>();
	variedtest<true>();
	variedtest<false>();

	std::cout << "code might be ok" << std::endl;

}
