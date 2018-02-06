//
// Created by ron on 28/12/17.
//

#include <cstdio>
#include "SoiChunk.h"

SoiChunk::SoiChunk()
:
Chunk()
{
}

SoiChunk::~SoiChunk()
{
}


bool SoiChunk::Process(const vector<unsigned char>& bytes, int& offset, bool dump)
{
    ReadMarker(bytes, offset);

     if (Marker() == 0xFFD8)
     {
         SetName(string("SOI"));
         // start of image marker, no data
         if (dump)
             printf("Start of Image Marker : SOI\n");

         return true;
     }

     return false;
 }


bool SoiChunk::WriteToFile(FILE *file, const unsigned char *pRawData)
{
    unsigned short us = Marker();
    bool status = Chunk::WriteUnsignedShortToFile(file, us);
    return status;
}