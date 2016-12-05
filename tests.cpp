#include "anser.h"


unsigned long
djb2_orig(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;
  
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  
  return hash;
}

Bus*
djb2_anser(unsigned char *str)
{
  Bus* hash = new Bus();

  hash->set(5381);

  int c;
  while ((c = (*str++))) {
    *hash = ((*hash << 5) + *hash) + c; /* hash * 33 + c */
  }
  
  return hash;
}

int main(int argc, char** argv) {

  unsigned char* string = (unsigned char*)"This is a test.";
  unsigned int hash = djb2_orig(string);
  Bus* hash2 = djb2_anser(string);
  std::cerr << std::hex << hash << std::endl;
  std::cerr << std::hex << hash2->get() << std::endl;
  assert(hash == hash2->get());

  
  int ntests = 3;
  
  for(int i=0; i < ntests; i++) {
    uint32_t x = random();
    uint32_t y = random();
    uint32_t z;
    Bus a, b;

    Bus sum = a + b;
    a.set(x);  b.set(y);
    z = sum.get();
    std::cerr << a.toString() << std::endl << b.toString() << std::endl << sum.toString() << std::endl << x << " " << y << " " << z << " " << (x + y == z) <<  " " << (z - (x + y)) << std::endl;
    assert(z == x + y);
  }

  for(int i=0; i < ntests; i++) {
    uint32_t x = random();
    uint32_t n = random() % 32;
    uint32_t z;
    
    Bus a, b;
    a = b >> n;
    b.set(x);
    z = a.get();
    std::cerr << a.toString() << std::endl << b.toString() << std::endl << x << " " << n << " " << ((x >> n) == z) << std::endl;
    assert(z == (x >> n));
  }
  
  for(int i=0; i < ntests; i++) {
    uint32_t x = random();
    uint32_t y = random();
    uint32_t z;

    Bus a, b;
    std::cerr << "------\n";
    Bus exp = a ^ b;
    a.set(x);
    b.set(y);
    std::cerr << a.toString() << " " << b.toString() << " " << exp.toString() << std::endl;
    z = exp.get();
    std::cerr << a.toString() << std::endl << b.toString() << std::endl << exp.toString() << std::endl << x << " " << y << " " << z << std::endl;
    std::cerr << (x^y) << " " << ((x ^ y) == z) << std::endl;
    assert(z == (x ^ y));
  }
}
