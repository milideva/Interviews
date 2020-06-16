/* Design a simple hash table for storing Mac addresses.
 */


unsigned short hash_func (uchar mac[], unsigned short size) {
    unsigned short index, hash1, hash2, hash3, hash4, hash5;
    if (!mac) return 0;

    hash1 = hash2 = hash3 = hash4 = hash5 = 0;

    hash1 = mac[0]^ mac[1];
    hash2 = mac[1]^ mac[2];
    hash3 = mac[2]^ mac[3];
    hash4 = mac[3]^ mac[4];
    hash5 = mac[4]^ mac[5];

    index = hash1 | (hash2 << 8);

    index ^= (hash3 | (hash4 << 8));

    index ^= hash5;

    index = index % size;

    return index;
}

/* How to handle collisions :
   Save some part of key in hash table, use remaining part of key for index.
   For hash collision, compare key. If collision, try another hash function.

   Cuckoo hash :

   The basic idea is to use two hash functions instead of only one. This
   provides two possible locations in the hash table for each key. In one of
   the commonly used variants of the algorithm, the hash table is split into
   two smaller tables of equal size, and each hash function provides an index
   into one of these two tables.

   When a new key is inserted, a greedy algorithm is used: The new key is
   inserted in one of its two possible locations, "kicking out", that is,
   displacing, any key that might already reside in this location. This
   displaced key is then inserted in its alternative location, again kicking
   out any key that might reside there, until a vacant position is found, or
   the procedure would enter an infinite loop. In the latter case, the hash
   table is rebuilt in-place using new hash functions.

   Increase bucket size or # hash functions to increase capacity
   Using just three hash functions increases the load to 91%


   Two-way skewed associative cache

   Other schemes have been suggested, such as the skewed cache, where the
   index for way 0 is direct, as above, but the index for way 1 is formed with
   a hash function. A good hash function has the property that addresses which
   conflict with the direct mapping tend not to conflict when mapped with the
   hash function, and so it is less likely that a program will suffer from an
   unexpectedly large number of conflict misses due to a pathological access
   pattern.

   Other algorithms that use multiple hash functions include the Bloom filter.

   D-left Cuckoo

   http://mybiasedcoin.blogspot.com/2014/10/cuckoo-filters.html

   Comparison of simple hash functions :

   http://burtleburtle.net/bob/hash/doobs.html

   Additive, Rotating, One-at-a-Time, Bernstein, CRC, Zobrist etc

*/
