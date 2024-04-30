
#include "encryptor.h"


int main()
{
 std::vector<int32_t> key;
 encryptor::GetEncryptionKey(key);

 std::string filename;
 std::cout << "Enter name of file to encrypt\n";
 std::cin >> filename;
 std::ifstream to_encrypt("../" + filename);
 if (!to_encrypt) {
  std::cerr << "Error opening input file\n";
  return 1;
 }

 std::cout << "Enter name of file where you want to write encrypted text\n";
 std::cin >> filename;
 std::ofstream output("../" + filename);
 if (!output) {
  std::cerr << "Error opening output file\n";
  return 1;
 }

 encryptor::Encrypt(to_encrypt,output,key);

 to_encrypt.close();
 output.close();
 return 0;
}
