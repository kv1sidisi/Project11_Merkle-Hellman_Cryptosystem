#include "decryptor.h"

int main()
{
 Key key;
 decryptor::GetDecryptionKey(key);

 std::string filename;
 std::cout << "Enter name of file to decrypt\n";
 std::cin >> filename;
 std::ifstream encrypted("../" + filename);
 if (!encrypted.is_open()) {
  std::cerr << "Error opening file." << std::endl;
  std::exit(1);
 }

 std::cout << "Enter name of file where you want to write decrypted text\n";
 std::cin >> filename;
 std::ofstream decrypted("../" + filename);
 if (!decrypted.is_open()) {
  std::cerr << "Error opening file." << std::endl;
  std::exit(1);
 }

 decryptor::Decrypt(encrypted,decrypted,key);

 encrypted.close();
 decrypted.close();
}
