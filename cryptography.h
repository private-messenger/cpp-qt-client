#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

class Cryptography {
public:
    // Cryptography();
    unsigned char* publickey = 0;
    unsigned char* privatekey = 0;
    virtual unsigned char* encode (unsigned char* data) = 0;
    virtual unsigned char* decode (unsigned char* data) = 0;
};

class AES256 : public Cryptography {
public:
    AES256 (unsigned char* key);
    unsigned char* encode (unsigned char* data);
    unsigned char* decode (unsigned char* data);
};

class RSA : public Cryptography {
public:
    RSA (unsigned char* publickey, unsigned char* privkey);
    unsigned char* encode (unsigned char* data);
    unsigned char* decode (unsigned char* data);
private:
    void generateKeys ();
};

#endif // CRYPTOGRAPHY_H
