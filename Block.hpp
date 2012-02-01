/*
 * Block.hpp
 *
 *  Created on: 31 Jan 2012
 *      Author: Max Foster
 */

#ifndef BLOCK_HPP
#define BLOCK_HPP

// A class for a single block of data in memory

class Heap;

class Block
{
public:
    enum DataType
    {
        DT_INTEGER,
        DT_REAL,
        DT_CHAR,
        DT_BOOLEAN,
        DT_POINTER,
        DATA_TYPE_COUNT
    };

    Block();
    Block(const Block & other);
    ~Block();

    bool inUse();
    DataType dataType();
    long integerData();
    double realData();
    char charData();
    bool booleanData();
    int pointerAddress();
    Heap & pointerHeap();
    bool pointerIsNull();

    void setUnused();
    void setToInteger(long data = 0u);
    void setToReal(double data = 0.0);
    void setToChar(char data = '\0');
    void setToBoolean(bool data = false);
    void setToPointer(int address, Heap & heap);
    void setToPointer(); // set to null pointer
    void setTo(DataType dataType); // Sets the block to the specified datatype with it's default value (i.e. 0)

    Block & operator =(const Block & rhs);
    bool operator ==(const Block & rhs);
    bool operator !=(const Block & rhs);

private:
    bool inUse_;
    DataType dataType_;

    union
    {
        long integerData_;
        double realData_;
        char charData_;
        bool booleanData_;

        struct // pointer struct
        {
            int address; // The array index of a block in one of the heaps
            Heap * heap; // The heap that the address is associated with
        } pointerData;
    };

    void nullifyPointer(); // Cleans the pointer data of a block, decrementing a heap reference count if necessary
};

#endif // BLOCK_HPP
