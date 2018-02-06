//
// Created by ron on 30/12/17.
//

#include "EoiChunk.h"

EoiChunk::EoiChunk()
:
Chunk()
{
}

EoiChunk::~EoiChunk()
{
}


bool EoiChunk::Process(const vector<unsigned char>& bytes, int& offset, bool dump)
{
    SetDataStart(offset); // start of data in original file
    ReadMarker(bytes, offset);

    if (Marker() == 0xFFD9)
    {
        SetName(string("EOI"));
        // start of image marker, no data
        if (dump)
            printf("End of Image Marker : EOI\n");

        return true;
    }

    return false;
}

bool EoiChunk::WriteToFile(FILE *file, const unsigned char *pRawData)
{
    unsigned short us = Marker();
    bool status = Chunk::WriteUnsignedShortToFile(file, us);
    return status;
}