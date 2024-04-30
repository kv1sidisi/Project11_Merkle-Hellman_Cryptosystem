#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

const size_t key_size = 8;

struct Key {
 std::vector<std::pair<int32_t, int>> w; //number, used or unused
 int32_t q;
 int32_t r;
};

namespace support {
int extendedEuclidean(int a, int b, int& x, int& y) {
 if (b == 0) {
  x = 1;
  y = 0;
  return a;
 }

 int x1, y1;
 int gcd = extendedEuclidean(b, a % b, x1, y1);

 x = y1;
 y = x1 - (a / b) * y1;

 return gcd;
}

int FindMultiplicativeInverse(int a, int q) {
 int x, y;
 int gcd = extendedEuclidean(a, q, x, y);
 x = (x % q + q) % q;
 return x;
}

int32_t FindMaxLessThan(int32_t a, Key& key) {
 int max_ind = -1;
 int max = -1;
 for (int i = 0; i < 8; i++) {
  if (key.w[i].first <= a && max < key.w[i].first) {
   max_ind = i;
   max = key.w[i].first;
  }
 }
 key.w[max_ind].second = true;
 return max;
}

char CreateSymbol(const Key& key) {
 char symbol = 0;
 for (int i = 0; i < 8; ++i) { symbol |= key.w[i].second << (7 - i); }
 return symbol;
}
}

namespace decryptor {
void GetDecryptionKey(Key& key) {
 std::string filename;
 std::cout << "Enter name of file with decryption key:";
 std::cin >> filename;
 std::ifstream key_file("../" + filename);
 if (!key_file) {
  std::cerr << "Error opening input file\n";
  std::exit(1);
 }

 int32_t num;
 for (int i = 0; i < 8; i++) {
  key_file >> num;
  key.w.emplace_back(num, false);
 }
 key_file >> num;
 key.q = num;
 key_file >> num;
 key.r = num;

 key_file.close();
}

void Decrypt(std::ifstream& encrypted, std::ofstream& decrypted, Key& key) {
 int32_t number;
 while (encrypted >> number) {
  number = number * support::FindMultiplicativeInverse(key.r, key.q) % key.q;
  while (number != 0) {
   number -= support::FindMaxLessThan(number,key);
  }
  char symbol = support::CreateSymbol(key);
  decrypted << symbol;
  for (int i = 0; i < 8; i++) { key.w[i].second = 0; }
 }
}
}

#endif //DECRYPTOR_H
