#include <iostream>
#include <cassert>
#include <set>

#include "concise.h"

template <bool wahmode> void checkflush() {
  std::cout << "[[[" << __PRETTY_FUNCTION__ << "]]]" << std::endl;
  uint32_t data[] = {
      3755999175, 4294934513, 4292866299, 1073741825, 4293394431, 2952790015,
      3756582647, 2680160199, 3758030720, 4294967231, 2281422847, 3758175102,
      4294967295, 2180480895, 4294967232, 4208984063, 3489660896, 4294967295,
      4287102967, 4294967295, 4294966399, 4294949887, 4294967267, 4294900735,
      2147483903, 4294966272, 1073741828, 4294966303, 1073741833, 4294950911,
      3220963292, 4294967040, 1073741827, 4286545919, 1073741827, 4294963199,
      1644167169, 4276084735, 1073741825, 4278190079, 1174405127, 1107296278,
      4169072639, 2684289023, 1107296257, 3489660927, 1073741825, 1241513985,
      4294967287, 3766484991, 2280131696, 2279606018, 201326594,  4093640704,
      2415918081, 2680422384, 3091529696, 2406514692, 2147549564, 2147483648,
      4161142784, 2814443519, 3089215115, 2147483648, 4229955520, 2240213951,
      2365585408, 3758096416, 2147483648, 2147499008, 3724602370, 2147483692,
      4294967295, 33554434,   4227858432, 4294705155, 2415919103, 3231715328,
      2147512831, 2147483648, 2155871792, 2147483648, 2147548928, 2147552256,
      2,          4294967288, 2147483711, 42,         4261412864, 2147491839,
      3,          4294901760, 1073741829, 2148532223, 2,          3188489984,
      2198083456, 2147483648, 2147516288, 5,          4294967040, 4294967295,
      2214594559, 1107296314, 2147755391, 2802001856, 2147483648, 2161252320,
      4197981184, 2612015615, 4028616012, 2147585087, 2147483648, 4294967232,
      3221094407, 4035960832, 4275838855, 2281766776, 2384461861, 4294642816,
      4294967295, 2147499246, 1,          4026531840, 2147876991, 2163729394,
      2164260868, 2831155280, 2155626498, 2380267521, 2147483679, 2147516288,
      2155868160, 2147483648, 2147483679, 23,         2952790016, 4286578688,
      2147485695, 2147483648, 4294901760, 2147614719, 2147483648, 2147499904,
      4290772992, 2147485695, 2147483772, 4294967168, 4294967295, 2214592511,
      2147483648, 4278190080, 1073741825, 2147483663, 2214591488, 4278190080,
      4294967295, 2147483775, 3498082307, 3893362688, 2385780971, 2348810240,
      2218786304, 4294443013, 2153776127, 2147483648, 4294959104, 2147491839,
      4278321024, 4261670943, 4286955567, 3257925631, 2147483679, 1,
      4294901984, 4286775299, 2147680303, 2972715008, 4177535616, 2147483666,
      2147484640, 2147484152, 14,         4294705152, 2147484159, 2147483648,
      2147614592, 2147483648, 4294967288, 2181038079, 2147483648, 4294967040,
      3114287111, 2650800128, 2148598052, 2630811648, 2148401154, 2413864232,
      2268065822, 2147486832, 3772792576, 2147484128, 2,          3221225472,
      4294959105, 4294967295, 4278222847, 4294967295, 4160815047, 2216689663,
      2277904564, 3791810048, 2178941184, 1,          4278190080, 2155872255,
      4294937724, 1073741845, 3256877055, 2147488928, 1,          1107296550,
      2684354559, 2149548100, 2,          2149580796, 3237994496, 2152726496,
      4,          2181038048, 2147483648, 2164260848, 637534212,  4160847872,
      3087090751, 2147484544, 3284140032, 4294739967, 4294967295, 2669641727,
      2147483648, 2214461440, 2454715904, 2684354572, 4027027472, 3219382499,
      2,          1107296258, 2214592511, 27,         4261412864, 1073741831,
      2148007935, 10,         4290772992, 1073741827, 3221225471, 2,
      3758096384, 3204939783, 2147516408, 4294965248, 3220430849, 2147483648,
      2411724800, 2147485688, 3087008206, 2147483648, 4162813952, 4294967292,
      1073741834, 4294967071, 1845493762, 2650800079, 2148401664, 4294836224,
      2147484671, 26,         4227858432, 1073741825, 2147516415, 2,
      4294443008, 4294967295, 2214592511, 2147483648, 2264924160, 2198208512,
      2147991552, 14,         3758096384, 2148007935, 3,          4292870144,
      3221225471, 2,          1040187395, 2147485568, 3758161919, 2147975184,
      2,          4294967232, 2147485695, 4026531840, 2148925443, 4291817472,
      2147484611, 2279620608, 2147483768, 13,         4294967280, 1073741826,
      2147483655, 382,        3758096384, 1073741837, 2147549183, 64,
      4294965248, 1073741858, 49,         2147499008, 1,          3758128128,
      4161798143, 2,          2684354556, 2415902720, 2147516416, 2953838592,
      2550136856, 5,          4294836224, 2285920259, 3372236800, 2147857347,
      2151677951, 2147483648, 4294446080, 2445435391, 2273443312, 2174992384,
      4227921920, 2348929540, 1,          4227858432, 2281701375, 30,
      4290772992, 1073741831, 2147483651, 2147483648, 2153905152, 2147664944,
      2277554412, 2147745856, 2147483774, 2180907008, 2684403792, 2149548032,
      7,          4292870144, 2684354559, 2282291200, 4278190080, 2147545103,
      2151678232, 1,          2157968896, 3229351944, 2348810273, 2147643896,
      3221848256, 2157969601, 2148548608, 2148015104, 3187671041, 2147483648,
      436207628,  301989889,  4290772992, 4294967295, 2415919103, 1,
      2147498012, 2149056528, 2147483652, 2683830272, 2147483779, 3221062080,
      4027056127, 4294966911, 4294967295, 4194287615, 4294967295, 3489644543,
      4227858431, 4294606799, 4260364287, 4294967232, 1073741825, 3756523503,
      4294837247, 2681208831, 2147483711, 2147483648, 4294967280, 1073741830,
      4294967280, 1073741834, 4225732607, 4294442975, 4270284787, 4026531840,
      1107296262, 1442840578, 2113929217, 4294832127, 2147549183};
  const int N = sizeof(data) / sizeof(uint32_t);
  ConciseSet<wahmode> c;
  c.words.resize(N);
  for (int i = 0; i < N; ++i)
    c.words[++c.lastWordIndex] = data[i];
  ConciseSet<wahmode> res;
  res.words.resize(c.words.size());
  WordIterator<wahmode> thisItr(c);
  thisItr.flush(res);
  assert(c.lastWordIndex == res.lastWordIndex);
  assert(c.size() == res.size());
}

template <bool wahmode> void heaportest() {
  std::cout << "[[[" << __PRETTY_FUNCTION__ << "]]]" << std::endl;
  ConciseSet<wahmode> *test[3];
  ConciseSet<wahmode> test1;
  for (int k = 0; k < 100; k += 7)
    test1.add(k);
  ConciseSet<wahmode> test2;
  for (int k = 0; k < 100; k += 15)
    test2.add(k);
  ConciseSet<wahmode> test3;
  for (int k = 0; k < 100; k += 2)
    test3.add(k);
  test[0] = &test1;
  test[1] = &test2;
  test[2] = &test3;
  ConciseSet<wahmode> answer = ConciseSet<wahmode>::fast_logicalor(
      3, (const ConciseSet<wahmode> **)&test[0]);
  assert(answer.size() == 60);
  size_t longcounter = 0;
  for (auto i = answer.begin(); i != answer.end(); ++i)
    longcounter++;
  assert(longcounter == 60);
  ConciseSet<wahmode> tmp;
  size_t expectedandsize1 = answer.logicalandCount(test1);
  tmp = answer.logicaland(test1);
  assert(expectedandsize1 == tmp.size());
  assert(tmp.size() == test1.size());
  size_t expectedandsize2 = answer.logicalandCount(test2);
  tmp = answer.logicaland(test2);
  assert(expectedandsize2 == tmp.size());
  assert(tmp.size() == test2.size());
  size_t expectedandsize3 = answer.logicalandCount(test3);
  tmp = answer.logicaland(test3);
  assert(expectedandsize3 == tmp.size());
  assert(tmp.size() == test3.size());
}

template <bool wahmode> void basictest() {
  std::cout << "[[[" << __PRETTY_FUNCTION__ << "]]]" << std::endl;
  ConciseSet<wahmode> test1;
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
  ConciseSet<wahmode> test2;
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
  ConciseSet<wahmode> tmp;
  assert(test1.logicalorCount(test2) == 7);
  tmp = test1.logicalor(test2);
  assert(tmp.size() == 7);
  assert(test1.logicalandCount(test2) == 3);
  tmp = test1.logicaland(test2);
  assert(tmp.size() == 3);
  tmp.add(100000);
  assert(tmp.size() == 4);
  tmp.shrink_to_fit();
}

template <bool wahmode> void longtest() {
  std::cout << "[[[" << __PRETTY_FUNCTION__ << "]]]" << std::endl;

  ConciseSet<wahmode> testc;
  for (int k = 0; k < 1000; ++k) {
    testc.add(k * 2);
    testc.add(k * 2 + 1);
  }
  assert(testc.size() == 2000);
  for (int k = 0; k < 1000; ++k) {
    assert(testc.contains(k * 2));
    assert(testc.contains(k * 2 + 1));
  }
  ConciseSet<wahmode> test1;
  for (int k = 0; k < 1000; ++k) {
    test1.add(k * 2);
  }
  for (int k = 0; k < 1000; ++k) {
    assert(test1.contains(k * 2));
    assert(!test1.contains(k * 2 + 1));
  }
  assert(test1.size() == 1000);
  ConciseSet<wahmode> shouldbetest1;
  assert(testc.logicalandCount(test1) == 1000);
  shouldbetest1 = testc.logicaland(test1);
  assert(shouldbetest1.size() == 1000);
  for (int k = 0; k < 1000; ++k) {
    assert(shouldbetest1.contains(k * 2));
    assert(!shouldbetest1.contains(k * 2 + 1));
  }
  ConciseSet<wahmode> test2;
  for (int k = 0; k < 1000; ++k) {
    test2.add(k * 2 + 1);
  }
  for (int k = 0; k < 1000; ++k) {
    assert(!test2.contains(k * 2));
    assert(test2.contains(k * 2 + 1));
  }
  assert(test2.size() == 1000);

  ConciseSet<wahmode> tmp;
  assert(test1.logicalorCount(test2) == 2000);
  tmp = test1.logicalor(test2);
  assert(tmp.size() == 2000);
  for (int k = 0; k < 1000; ++k) {
    assert(tmp.contains(k * 2));
    assert(tmp.contains(k * 2 + 1));
  }
  assert(tmp.intersects(test2));
  assert(tmp.logicalandCount(test2) == 1000);
  tmp = tmp.logicaland(test2);
  assert(tmp.size() == 1000);
  assert(test1.intersects(test2) == false);
  assert(test1.logicalandCount(test2) == 0);
  tmp = test1.logicaland(test2);
  assert(tmp.size() == 0);
}

static std::set<uint32_t> subtract(std::set<uint32_t> h1,
                                   std::set<uint32_t> h2) {
  std::set<uint32_t> answer;
  answer.clear();
  for (std::set<uint32_t>::iterator i = h1.begin(); i != h1.end(); i++) {
    if (h2.find(*i) == h2.end())
      answer.insert(*i);
  }
  return answer;
}

static std::set<uint32_t> symmetrically_subtract(std::set<uint32_t> h1,
                                                 std::set<uint32_t> h2) {
  std::set<uint32_t> answer;
  answer.insert(h1.begin(), h1.end());
  for (std::set<uint32_t>::iterator i = h2.begin(); i != h2.end(); i++) {
    auto x = answer.find(*i);
    if (x == answer.end())
      answer.insert(*i);
    else
      answer.erase(x);
  }
  return answer;
}

static std::set<uint32_t> unite(std::set<uint32_t> s1, std::set<uint32_t> s2) {
  std::set<uint32_t> answer;
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
  std::set<uint32_t> answer;
  for (std::set<uint32_t>::iterator i = s1.begin(); i != s1.end(); i++) {
    if (s2.find(*i) != s2.end()) {
      answer.insert(*i);
    }
  }
  return answer;
}

template <bool wahmode>
static bool equals(std::set<uint32_t> s, ConciseSet<wahmode> c) {
  if (s.size() != c.size())
    return false;
  // we go one way
  for (std::set<uint32_t>::iterator i = s.begin(); i != s.end(); i++) {
    if (!c.contains(*i))
      return false;
  }
  // we go both ways
  std::set<uint32_t>::iterator a = s.begin();
  auto b = c.begin();
  for (; (a != s.end()) && (b != c.end()); a++, b++) {
    if (*a != *b) {
      return false;
    }
  }

  // we go another way
  for (auto i = c.begin(); i != c.end(); i++) {
    if (s.find(*i) == s.end()) {
      std::cout << " There is probably an issue with the ConciseSet iterators? "
                << std::endl;
      return false;
    }
  }
  return true;
}

template <bool wahmode> void toytest() {

  std::cout << "[[[" << __PRETTY_FUNCTION__ << "]]]" << std::endl;

  ConciseSet<wahmode> test1;
  std::set<uint32_t> set1;

  for (int k = 0; k < 30; k += 3) {
    test1.add(k);
    set1.insert(k);
  }

  ConciseSet<wahmode> test2;
  std::set<uint32_t> set2;
  for (int k = 0; k < 30; k += 5) {
    test2.add(k);
    set2.insert(k);
  }
  std::set<uint32_t> trueunion = unite(set1, set2);
  std::set<uint32_t> trueinter = intersect(set1, set2);
  std::set<uint32_t> truesubtract = subtract(set1, set2);
  std::set<uint32_t> truesymsubtract = symmetrically_subtract(set1, set2);
  ConciseSet<wahmode> union1;
  ConciseSet<wahmode> union2;
  size_t expunion1 = test1.logicalorCount(test2);
  union1 = test1.logicalor(test2);
  assert(union1.size() == expunion1);
  union2 = test1.logicalor(test2);
  assert(equals(trueunion, union1));
  assert(equals(trueunion, union2));
  ConciseSet<wahmode> intersect1;
  ConciseSet<wahmode> intersect2;
  size_t expinter1 = test1.logicalandCount(test2);
  intersect1 = test1.logicaland(test2);
  assert(expinter1 == intersect1.size());
  intersect2 = test1.logicaland(test2);
  assert(equals(trueinter, intersect1));
  assert(equals(trueinter, intersect2));
  ConciseSet<wahmode> symsubtract1;
  ConciseSet<wahmode> symsubtract2;
  symsubtract1 = test1.logicalxor(test2);
  symsubtract2 = test1.logicalxor(test2);
  assert(equals(truesymsubtract, symsubtract1));
  assert(equals(truesymsubtract, symsubtract2));
  ConciseSet<wahmode> subtract1;
  ConciseSet<wahmode> subtract2;
  subtract1 = test1.logicalandnot(test2);
  subtract2 = test1.logicalandnot(test2);
  assert(equals(truesubtract, subtract1));
  assert(equals(truesubtract, subtract2));
}
template <bool wahmode> void iteratortest() {
  std::cout << "[[[" << __PRETTY_FUNCTION__ << "]]]" << std::endl;

  uint32_t data[] = {3515,   5185,   7796,   33347,  45641,  51779,  53188,
                     60664,  68454,  68574,  74234,  78260,  82877,  100026,
                     111016, 116633, 117789, 119044, 119103, 146771, 159597,
                     163210, 181124, 182343, 187302, 187876, 191494};
  const int N = sizeof(data) / sizeof(uint32_t);
  ConciseSet<wahmode> test1;
  for (int k = 0; k < N; ++k) {
    test1.add(data[k]);
  }
  assert(test1.size() == N);
  int c = 0;
  for (auto i = test1.begin(); i != test1.end(); ++i) {
    assert(c < N);
    assert(*i == data[c]);
    c++;
  }
  assert(c == N);
}

template <bool wahmode> void variedtest() {

  std::cout << "[[[" << __PRETTY_FUNCTION__ << "]]]" << std::endl;

  ConciseSet<wahmode> test1;
  std::set<uint32_t> set1;

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

  ConciseSet<wahmode> test2;
  std::set<uint32_t> set2;
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
  std::set<uint32_t> trueunion = unite(set1, set2);
  std::set<uint32_t> trueinter = intersect(set1, set2);
  std::set<uint32_t> truesubtract = subtract(set1, set2);
  std::set<uint32_t> truesymsubtract = symmetrically_subtract(set1, set2);

  ConciseSet<wahmode> union1;
  ConciseSet<wahmode> union2;
  size_t expunion1 = test1.logicalorCount(test2);
  union1 = test1.logicalor(test2);
  assert(union1.size() == expunion1);
  union2 = test1.logicalor(test2);
  assert(equals(trueunion, union1));
  assert(equals(trueunion, union2));
  ConciseSet<wahmode> intersect1;
  ConciseSet<wahmode> intersect2;
  size_t expinter1 = test1.logicalandCount(test2);
  intersect1 = test1.logicaland(test2);
  assert(expinter1 == intersect1.size());
  intersect2 = test1.logicaland(test2);
  assert(equals(trueinter, intersect1));
  assert(equals(trueinter, intersect2));
  ConciseSet<wahmode> symsubtract1;
  ConciseSet<wahmode> symsubtract2;
  symsubtract1 = test1.logicalxor(test2);
  symsubtract2 = test1.logicalxor(test2);
  assert(equals(truesymsubtract, symsubtract1));
  assert(equals(truesymsubtract, symsubtract2));
  ConciseSet<wahmode> subtract1;
  ConciseSet<wahmode> subtract2;
  subtract1 = test1.logicalandnot(test2);
  subtract2 = test1.logicalandnot(test2);
  assert(equals(truesubtract, subtract1));
  assert(equals(truesubtract, subtract2));
}

template <bool wahmode> void realtest() {

  std::cout << "[[[" << __PRETTY_FUNCTION__ << "]]]" << std::endl;

  uint32_t data1[] = {
      1,    13,   62,   120,  132,  133,  134,  136,  143,  159,  170,  175,
      191,  222,  233,  255,  274,  317,  342,  346,  375,  388,  419,  453,
      455,  470,  485,  503,  506,  523,  536,  542,  548,  556,  570,  574,
      587,  600,  603,  622,  634,  674,  703,  714,  757,  764,  765,  768,
      796,  836,  841,  844,  851,  867,  881,  942,  946,  947,  960,  985,
      1035, 1045, 1106, 1126, 1128, 1135, 1165, 1191, 1201, 1239, 1248, 1267,
      1286, 1357, 1362, 1374, 1375, 1388, 1392, 1401, 1405, 1475, 1477, 1494,
      1509, 1517, 1518, 1535, 1544, 1548, 1553, 1564, 1573, 1577, 1584, 1589,
      1610, 1615, 1629, 1643, 1649, 1673, 1677, 1702, 1718, 1723, 1730, 1734,
      1749, 1758, 1774, 1846, 1847, 1878, 1880, 1912, 1913, 1915, 1919, 1946,
      1962, 1984, 2034, 2038, 2040, 2082, 2083, 2094, 2101, 2102, 2110, 2125,
      2129, 2134, 2136, 2151, 2155, 2165, 2176, 2204, 2209, 2229, 2237, 2258,
      2276, 2283, 2284, 2292, 2295, 2300, 2306, 2308, 2339, 2343, 2347, 2370,
      2386, 2420, 2430, 2450, 2451, 2454, 2459, 2462, 2463, 2489, 2496, 2511,
      2521, 2522, 2525, 2535, 2537, 2563, 2564, 2571, 2576, 2609, 2619, 2626,
      2638, 2647, 2654, 2672, 2702, 2703, 2719, 2743, 2744, 2757, 2798, 2816,
      2836, 2864, 2898, 2907, 2916, 2923, 2934, 2935, 2941, 3032, 3074, 3083,
      3113, 3126, 3130, 3137, 3160, 3169, 3192, 3196, 3198, 3215, 3223, 3258,
      3259, 3293, 3309, 3350, 3394, 3416, 3427, 3442, 3455, 3521, 3525, 3533,
      3536, 3553, 3561, 3593, 3615, 3630, 3659, 3677, 3698, 3707, 3718, 3722,
      3742, 3752, 3753, 3757, 3759, 3832, 3834, 3856, 3857, 3860, 3862, 3866,
      3886, 3891, 3896, 3897, 3945, 3962, 3964, 3977, 3986, 3995, 4006, 4011,
      4015, 4022, 4030, 4058, 4065, 4086, 4100, 4133, 4134, 4152, 4182, 4198,
      4207, 4214, 4246, 4275, 4280, 4301, 4303, 4308, 4311, 4312, 4339, 4344,
      4357, 4361, 4372, 4384, 4387, 4395, 4412, 4420, 4449, 4459, 4462, 4504,
      4509, 4523, 4531, 4536, 4545, 4565, 4616, 4627, 4677, 4679, 4699, 4702,
      4725, 4728, 4740, 4746, 4750, 4777, 4787, 4805, 4812, 4821, 4828, 4837,
      4844, 4860, 4873, 4876, 4878, 4908, 4920, 4926, 4928, 4939, 4958, 4963,
      4970, 4990, 4994, 4995, 5007, 5021, 5029, 5050, 5051, 5062, 5063, 5076,
      5095, 5132, 5168, 5191, 5195, 5218, 5243, 5258, 5304, 5326, 5341, 5347,
      5373, 5379, 5407, 5431, 5446, 5458, 5465, 5477, 5486, 5501, 5522, 5549,
      5578, 5603, 5604, 5626, 5640, 5643, 5663, 5664, 5679, 5686, 5687, 5692,
      5701, 5710, 5723, 5724, 5759, 5760, 5761, 5767, 5784, 5788, 5796, 5807,
      5828, 5839, 5846, 5851, 5881, 5909, 5910, 5911, 5923, 5954, 5989, 5993,
      6002, 6003, 6020, 6022, 6034, 6070, 6083, 6087, 6118, 6123, 6127, 6134,
      6140, 6174, 6180, 6197, 6218, 6227, 6237, 6250, 6260, 6275, 6280, 6304,
      6325, 6338, 6352, 6366, 6384, 6397, 6417, 6425, 6446, 6460, 6464, 6495,
      6504, 6526, 6532, 6543, 6564, 6583, 6643, 6650, 6651, 6701, 6704, 6730,
      6743, 6750, 6776, 6777, 6779, 6784, 6798, 6807, 6846, 6850, 6871, 6922,
      6924, 6952, 6955, 6956, 6968, 6974, 6998, 7003, 7029, 7038, 7090, 7106,
      7107, 7108, 7133, 7193, 7209, 7210, 7212, 7228, 7240, 7242, 7289, 7301,
      7325, 7351, 7391, 7393, 7404, 7429, 7453, 7490, 7491, 7495, 7545, 7580,
      7601, 7611, 7660, 7670, 7682, 7713, 7782, 7790, 7803, 7823, 7828, 7830,
      7843, 7846, 7876, 7885, 7913, 7922, 7932, 7942, 7947, 7964, 7983, 7996,
      7998, 8003, 8007, 8011, 8016, 8034, 8054, 8076, 8086, 8118, 8123, 8134,
      8143, 8149, 8158, 8160, 8208, 8212, 8230, 8245, 8252, 8253, 8257, 8260,
      8295, 8303, 8331, 8350, 8362, 8365, 8367, 8370, 8374, 8378, 8409, 8441,
      8510, 8541, 8571, 8587, 8592, 8621, 8664, 8681, 8692, 8695, 8699, 8719,
      8729, 8776, 8783, 8804, 8812, 8827, 8857, 8904, 8928, 8938, 8961, 8969,
      8974, 8995, 8998, 9002, 9004, 9017, 9028, 9029, 9048, 9068, 9079, 9098};
  const int N1 = sizeof(data1) / sizeof(uint32_t);

  uint32_t data2[] = {
      0,   1,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
      15,  16,  17,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
      30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,
      44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,
      58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
      72,  73,  74,  75,  76,  77,  78,  80,  81,  82,  83,  84,  85,  86,
      87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  100, 101,
      102, 103, 104, 105, 106, 107, 108, 110, 111, 112, 113, 114, 115, 116,
      117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 128, 130, 131, 132,
      133, 134, 135, 136, 137, 138, 139, 140, 141, 143, 144, 145, 146, 148,
      149, 150, 151, 152, 153, 154, 155, 157, 158, 159, 160, 161, 162, 164,
      165, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
      180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193,
      194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
      208, 209, 210, 211, 212, 213, 214, 215, 217, 219, 220, 221, 222, 223,
      224, 225, 226, 227, 228, 229, 231, 233, 234, 235, 236, 237, 238, 239,
      240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253,
      254, 255, 256, 257, 258, 259, 260, 261, 263, 264, 265, 266, 267, 268,
      270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283,
      284, 285, 286, 287, 288, 289, 290, 291, 292, 294, 295, 296, 297, 298,
      299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 313,
      315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328,
      329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342,
      343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 355, 356, 357,
      358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371,
      372, 373, 374, 375, 376, 377, 379, 380, 381, 382, 383, 385, 386, 387,
      388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 400, 401, 402,
      403, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417,
      418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431,
      432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445,
      446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459,
      460, 461, 462, 463, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474,
      475, 476, 477, 478, 479, 480, 481, 482, 483, 484, 485, 486, 487, 488,
      489, 490, 491, 492, 493, 494, 495, 496, 497, 498, 499, 500, 501, 502,
      503, 504, 505, 506, 508, 509, 510, 511, 512, 513, 514, 515, 516, 517,
      518, 519, 520, 521, 522, 523, 524, 525, 526, 527, 528, 529, 530, 531,
      532, 533, 534, 535, 536, 537, 538, 539, 540, 541, 542, 543, 544, 545,
      546, 548, 549, 550, 551, 552, 553, 554, 556, 557, 558, 559, 560, 561,
      562, 563, 564, 565, 566, 567, 568, 569, 570, 572, 573, 574, 575, 576,
      577, 578, 579, 580, 581, 582, 584, 585, 586, 587, 588, 589, 590, 591,
      592, 593, 594, 596, 597, 598, 599, 600, 601, 602, 603, 604, 605, 606,
      607, 608, 609, 610, 611, 613, 614, 615, 616, 617, 618, 619, 620, 621,
      622, 623, 625, 626, 628, 629, 630, 631, 632, 634, 635, 636};
  const int N2 = sizeof(data2) / sizeof(uint32_t);

  ConciseSet<wahmode> test1;
  std::set<uint32_t> set1;

  for (int k = 0; k < N1; ++k) {
    test1.add(data1[k]);
    set1.insert(data1[k]);
  }

  ConciseSet<wahmode> test2;
  std::set<uint32_t> set2;
  for (int k = 0; k < N2; ++k) {
    test2.add(data2[k]);
    set2.insert(data2[k]);
  }


  assert(test1.equals(test1));
  assert(test2.equals(test2));
  assert(!test2.equals(test1));
  assert(!test1.equals(test2));

  std::set<uint32_t> trueunion = unite(set1, set2);
  std::set<uint32_t> trueinter = intersect(set1, set2);
  std::set<uint32_t> truesubtract = subtract(set1, set2);
  std::set<uint32_t> truesymsubtract = symmetrically_subtract(set1, set2);

  ConciseSet<wahmode> union1;
  ConciseSet<wahmode> union2;

  size_t expunion1 = test1.logicalorCount(test2);
  union1 = test1.logicalor(test2);
  assert(union1.size() == expunion1);
  union2 = test1.logicalor(test2);
  assert(equals(trueunion, union1));
  assert(equals(trueunion, union2));
  ConciseSet<wahmode> intersect1;
  ConciseSet<wahmode> intersect2;
  size_t expinter1 = test1.logicalandCount(test2);
  intersect1 = test1.logicaland(test2);
  assert(expinter1 == intersect1.size());
  intersect2 = test1.logicaland(test2);
  assert(equals(trueinter, intersect1));
  assert(equals(trueinter, intersect2));
  ConciseSet<wahmode> symsubtract1;
  ConciseSet<wahmode> symsubtract2;
  symsubtract1 = test1.logicalxor(test2);
  symsubtract2 = test1.logicalxor(test2);
  assert(equals(truesymsubtract, symsubtract1));
  assert(equals(truesymsubtract, symsubtract2));
  ConciseSet<wahmode> subtract1;
  ConciseSet<wahmode> subtract2;
  subtract1 = test1.logicalandnot(test2);
  subtract2 = test1.logicalandnot(test2);
  assert(equals(truesubtract, subtract1));
  assert(equals(truesubtract, subtract2));
}

int main() {
  checkflush<false>();
  // checkflush<true>();// not actually safe (limitation in original code)
  iteratortest<true>();
  iteratortest<false>();
  heaportest<true>();
  heaportest<false>();
  basictest<true>();
  basictest<false>();
  longtest<true>();
  longtest<false>();
  toytest<true>();
  toytest<false>();
  variedtest<true>();
  variedtest<false>();
  realtest<true>();
  realtest<false>();

  std::cout << "code might be ok" << std::endl;
}
