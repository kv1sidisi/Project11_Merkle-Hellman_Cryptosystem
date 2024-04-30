#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H
#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
const size_t key_size = 8;


namespace encryptor {
void GetEncryptionKey(std::vector<int32_t>& key) {
 std::string filename;
 std::cout << "Enter name of file with encryption key:";
 std::cin >> filename;
 std::ifstream key_file("../" + filename);
 if (!key_file) {
  std::cerr << "Error opening input file\n";
  std::exit(1);
 }

 int32_t num;
 while (key_file >> num) {
  key.push_back(num);
 }
 key_file.close();
}

void Encrypt(std::ifstream& to_encrypt,
             std::ofstream& output,
             const std::vector<int32_t>& encryption_key) {
 char buffer;
 while (to_encrypt.get(buffer)) {
  int32_t result = 0;
  for (int i = 7; i >= 0; --i) {
   int bit = (buffer >> i) & 1;
   result += bit * encryption_key[7 - i];
  }
  output << result << ' ';
 }

 output.close();
 to_encrypt.close();
}

}

#endif //ENCRYPTOR_H
