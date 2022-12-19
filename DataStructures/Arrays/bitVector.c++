#include <iostream>
#include <string>
#include <deque>
#include <limits.h>
#include <assert.h>

using namespace std;

class BitVector {
    public:
        void Set (size_t index);
        bool isSet (size_t index);
        void UnSet (size_t index);
        bool isUnSet (size_t index);
        size_t Mask (size_t index) const;
        
        explicit BitVector (size_t); // constructor 
        BitVector (const BitVector&); // copy constructor
        ~BitVector (); // destructor
        BitVector& operator = (const BitVector& a);  // assignment operator
        size_t Size () const;  // return size of bitvector
        
    private:
        // data
        unsigned char *byteArray;
        size_t size;
        
        // methods
        size_t ByteNumber (size_t index) const;
        void bv_assert (size_t index);
};

BitVector::BitVector (size_t sz) {
    size = sz;
    size_t n = (sz + CHAR_BIT - 1) / CHAR_BIT;
    byteArray = new unsigned char [n];
    if (byteArray == NULL) {
        std::cerr << "BitVector memory allocation failure, terminating" << endl;
        exit (EXIT_FAILURE);
    }
}

BitVector::~BitVector () {
    delete byteArray;   
}

size_t BitVector::ByteNumber (size_t index) const {
    return (index + CHAR_BIT - 1) / CHAR_BIT;
}

size_t BitVector::Mask (size_t index) const {
    return 0x1 << (index % CHAR_BIT);
}

void BitVector::bv_assert(size_t index) {
    assert(index <= size);   
}

void BitVector::Set (size_t index) {
    bv_assert(index);
    byteArray[ByteNumber(index)] |= Mask(index);
}

bool BitVector::isSet (size_t index) {
    bv_assert(index);
    return 0 != (byteArray[ByteNumber(index)] & Mask(index));
}

void BitVector::UnSet (size_t index) {
    bv_assert(index);
    byteArray[ByteNumber(index)] &= ~Mask(index);
}

bool BitVector::isUnSet (size_t index) {
    bv_assert(index);
    return 0 == (byteArray[ByteNumber(index)] & Mask(index));
}

size_t BitVector::Size (void) const {
    return size;   
}

void testSetUnset (BitVector &bv, size_t index) {
    bv.Set(index);
    if (bv.isSet(index) == false) {
        cout << index <<"th bit not set" << endl;
    } else {
        cout << index <<"th bit set" << endl;
    }
    bv.UnSet(index);
       if (bv.isSet(index) == false) {
        cout << index <<"th bit not set" << endl;
    } else {
        cout << index <<"th bit set" << endl;
    }  
}
int main()
{
    BitVector bv(40);
    size_t index = 25;
    testSetUnset(bv, index);
    index = 0;
    testSetUnset(bv, index);
    index = 40;
    testSetUnset(bv, index);
    index = 41;
    testSetUnset(bv, index);
}
