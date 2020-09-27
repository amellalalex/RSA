#include <stdio.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <string.h>
#include <stdbool.h>

bool DEBUG = true;

int main() {
  //settings
  int bits = 4096;

  //set up BN
  if(DEBUG) printf("[*] Generating public exponent...\n");
  BIGNUM * e = BN_new();
  int err = BN_dec2bn(&e, "65537");
  if(err == 0) printf("[!] ERROR creating BIGNUM e for public exponent.\n\n");

  //generate RSA keypair
  if(DEBUG) printf("[*] Generating RSA public/private keypair...\n");
  RSA * rsa = RSA_new();
  err = RSA_generate_key_ex(rsa, bits, e, NULL);
  if(err == 0) printf("[!] ERROR Creating RSA keypair.\n\n");

  //print keys
  if(DEBUG) printf("[*] Creating placeholders for n e and d values.\n");
  const BIGNUM * n = BN_new();
  const BIGNUM * newe = BN_new();
  const BIGNUM * d = BN_new();

  if(DEBUG) printf("[*] Fetching RSA values.\n");
  RSA_get0_key(rsa, &n, &newe, &d);

  char * nchar = BN_bn2dec(n);
  char * echar = BN_bn2dec(newe);
  char * dchar = BN_bn2dec(d);

  printf("[*] RSA values are n = %s \n\n e = %s \n\n d = %s\n\n", nchar, echar, dchar);

  return 0;
}
