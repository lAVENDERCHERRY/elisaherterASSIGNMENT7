//work cited: chatgpt, stackoverflow
#include <stdio.h>
#include <stdlib.h>

unsigned int getOffset(unsigned int address){ // extract the offset from the address
    return address & 0xF; // masks the last 4 bits
}

unsigned int getSet(unsigned int address) { //extract the set from the address
    return (address >> 4) & 0xFF; // shift right 4 bits and mask the last 8 bits
}

unsigned int getTag(unsigned int address) { //extract the set from the address
    return address >> 12; // shift right 12 bits
}

int main(int argc, char *argv[]) {
if (argc == 2) { //// Checks command-line argument

    unsigned int a = strtoul(argv[1], NULL, 16); // Convert argument to unsigned int
    unsigned int o = getOffset(a); //get offset
    unsigned int s = getSet(a); //get set
    unsigned int t = getTag(a); //get tag
    printf("offset: %x - tag: %x - set: %x\n", o, t, s); //printed results

} else {
// TODO - your test cases go here!
        unsigned int testAddress1 = 0x12345678; //defines address 1
        unsigned int testAddress2 = 0x87654321; //define address 2

        unsigned int o1 = getOffset(testAddress1); //gets offset for 1
        unsigned int s1 = getSet(testAddress1); // gets set for 1
        unsigned int t1 = getTag(testAddress1); //gets tag for 1
        printf("0x12345678: offset: %x - tag: %x - set: %x\n", o1, t1, s1); //results for 1

        unsigned int o2 = getOffset(testAddress2); //offset for address 2
        unsigned int s2 = getSet(testAddress2); //set for address 2
        unsigned int t2 = getTag(testAddress2); //tag for address 2
        printf("0x87654321: offset: %x - tag: %x - set: %x\n", o2, t2, s2); //results of address 2
}
        return 0;
}