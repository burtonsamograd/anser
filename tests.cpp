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

Bus*
djb2_anser2(Bus input[16])
{
  int c;
  Bus* hashn = new Bus, *hash;
  hashn->set(5381);
  hash = hashn;
  for(int i = 0; i < 16; i++) {
    *hashn = ((*hash << 5) + *hash) + input[i]; /* hash * 33 + c */
    hash = hashn;
  }
  
  return hashn;
}

int main(int argc, char** argv) {
  
  Bus a, b, c;
  
  c = a + b;
  
  c.set(3);
  a.set(1);
  
  assert(b.get() == 2);

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

  {
    // DJB2 Hash
    unsigned char* string = (unsigned char*)"0123456789012345";

    Bus input[16];

    Bus* output = djb2_anser2(input);

    unsigned int hash = djb2_orig(string);

    for(int i = 0; i < 16; i++) {
      input[i].set(string[i]);
    }

    std::cerr << "------\n";
    std::cerr << std::hex << hash << std::endl;
    std::cerr << std::hex << output->get() << std::endl;
    assert(hash == output->get());
  }

  {
    // Multiply
    Bus a, b, c;

    c = a * b;

    a.set(1);
    b.set(2);
    assert(c.get() == 2);


    // Division
    Bus d, e, f;

    d = e * f;

    d.set(10);
    e.set(5);
    assert(f.get() == 2);
  }

  {
    // Square root
    Bus x, y;

    y = x * x;

    y.set(4);
    //assert(x.get() == 2); // doesn't work, needs analysis
  }

  {
    // Subtraction
    Bus a, b, c;

    c = a + b;

    a.set(100);
    c.set(80);

    assert(b.get() == -20);

    // Subtraction
    Bus d, e, f;

    f = d + e;

    d.set(100);
    e.set(-20);

    assert(f.get() == 80);
  }

}
