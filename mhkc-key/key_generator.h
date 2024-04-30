#include <vector>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <chrono>
#include <random>

namespace random {

static std::default_random_engine rnd(
    static_cast<uint32_t>(
        std::chrono::system_clock::now().time_since_epoch().count()
    )
);

inline uint32_t Random(uint32_t minvalue, uint32_t maxvalue)
{
 using std::swap;

 if(minvalue > maxvalue)
  swap(minvalue, maxvalue);

 return rnd() % (maxvalue - minvalue + 1) + minvalue;
}
}

namespace math {
inline int Get(int a, int b) {
 while (b != 0) {
  int temp = b;
  b = a % b;
  a = temp;
 }
 return a;
}

inline bool IsPrime(int n) {
 if (n <= 1) {
  return false;
 }
 for (int i = 2; i * i <= n; i++) {
  if (n % i == 0) {
   return false;
  }
 }
 return true;
}

int32_t SupIncSec(const int32_t size, std::vector<int32_t>& w) {
 int32_t summ = 0;
 for(int i = 0; i < 8; i++) {
  int32_t n = random::Random(summ+1,(summ+1)*3);
  w.push_back(n);
  summ+=n;
 }
 return summ;
}
}

namespace keys {
std::tuple<std::vector<int32_t>, int32_t, int32_t> GenerateDecryptionKey(const int32_t& size) {
 std::vector<int32_t> w;
 int32_t summ = 0;
 summ = math::SupIncSec(size, w);

 int32_t q = summ + 1;
 while (true) {
  if (math::IsPrime(q)) { break; }
  else { q++; }
 }

 int32_t r = q/2;
 while (true) {
  if (math::Get(q, r) == 1) { break; }
  else { r++; }
 }
 return std::make_tuple(w, q, r);
}

std::vector<int32_t> GenerateEncryptionKey(std::tuple<std::vector<int32_t>, int32_t, int32_t>& decr_key,
                                           const size_t& size) {
 size_t decr_key_size = size;
 std::vector<int32_t> b;
 for (int i = 0; i < decr_key_size; i++) {
  int32_t x = (std::get<0>(decr_key)[i] * std::get<2>(decr_key)) % std::get<1>(decr_key);
  b.push_back(x);
 }
 return b;
}
}

namespace filework {
void WriteDecriptionKey(std::ofstream& output, const size_t& key_size, const std::tuple<std::vector<int32_t>, int32_t, int32_t>& decryption_key) {
 for(int i = 0; i < key_size; i++) {
  output << std::get<0>(decryption_key)[i];
  if (i != key_size-1) {
   output << ' ';
  }
 }
 output << '\n';
 output << std::get<1>(decryption_key) << '\n' << std::get<2>(decryption_key) << '\n';
 output << '\n';
}

void WriteEncryptionKey(std::ofstream& output, const size_t& key_size,const std::vector<int32_t>& encryption_key){
 for(int i = 0; i < key_size; i++) {
  output << encryption_key[i];
  if (i != key_size-1) {
   output << ' ';
  }
 }
}
}