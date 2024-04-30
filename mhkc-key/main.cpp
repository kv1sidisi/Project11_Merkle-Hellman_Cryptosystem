#include "key_generator.h"

int main()
{
 const size_t key_size = 8;

 std::tuple<std::vector<int32_t>, int32_t, int32_t> decryption_key;
 decryption_key = keys::GenerateDecryptionKey(key_size);

 std::vector<int32_t> encryption_key;
 encryption_key = keys::GenerateEncryptionKey(decryption_key,key_size);

 int64_t id = random::Random(1,10000000000000);
 std::ofstream decrypt("../keys/decryption_key" + std::to_string(id) + ".txt");
 if (!decrypt) {
  std::cerr << "Error opening output file\n";
  return 1;
 }

 std::ofstream encrypt("../keys/encryption_key" + std::to_string(id) + ".txt");
 if (!encrypt) {
  std::cerr << "Error opening output file\n";
  return 1;
 }

 filework::WriteDecriptionKey(decrypt,key_size,decryption_key);
 filework::WriteEncryptionKey(encrypt, key_size, encryption_key);
 decrypt.close();
 encrypt.close();

}
