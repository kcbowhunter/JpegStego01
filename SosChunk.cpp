//
// Created by ron on 29/12/17.
//

#include "SosChunk.h"

SosChunk::SosChunk()
        :
        Chunk(),
        m_compressedDataEnd(0)
{
}

SosChunk::~SosChunk()
{
}


 bool SosChunk::Process(const vector<unsigned char>& bytes, int& offset, bool dump)
 {
     Chunk::SetDataStart(offset);
     ReadMarker(bytes, offset);

     unsigned short marker = Marker();
     if (marker != 0XFFDA)
     {
         printf("Error in SosChunk: Marker is h 0X%X but expecting 0XFFDA", marker);
         return false;
     }

     ReadSize(bytes, offset);

     if (dump)
     {
         DumpMarkerAndSize();
     }

     int size = Size();

     // increment offset to the start of the compressed data
     offset += size;
     SetDataEnd(offset);

     // walk through the compressed data looking for the EIO marker, 0XFFD9

     unsigned char b0 = 0, b1 = 0;
     int datasize = (int)bytes.size();
     for (int i=offset; i<datasize-1; ++i)
     {
         b0 = bytes[i];

         if (b0 == 0xFF)
         {
             b1 = bytes[i+1];
             if (b1 == 0XD9)
             {
                 offset = i;
                 m_compressedDataEnd = offset;
                 return true;
             }
         }
     }

     return false;
 }

bool SosChunk::WriteToFile(FILE *file, const unsigned char *pRawData)
{
    // Write the header
    bool status = Chunk::WriteToFile(file, pRawData);

    // Write the uncompressed data
    int dataEnd = GetDataEnd();
    const unsigned char* pStart = pRawData + dataEnd;
    size_t size = 1;
    size_t count = m_compressedDataEnd - dataEnd;
    size_t nbytes = fwrite(pStart, size, count, file);

    return status;
}