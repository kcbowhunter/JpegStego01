//
// Created by ron on 29/12/17.
//

#ifndef JPEGSTEGO01_SOSCHUNK_H
#define JPEGSTEGO01_SOSCHUNK_H

#include "Chunk.h"

// Start of Scan chunk
// Compressed data follows this chunk
class SosChunk : public Chunk {
public:

    SosChunk();
   ~SosChunk();

    virtual bool Process(const vector<unsigned char>& bytes, int& offset, bool dump) override;

    virtual bool WriteToFile(FILE *file, const unsigned char *pRawData) override;

    // End of compressed data (start of next marker - EOI)
    int m_compressedDataEnd;
};


#endif //JPEGSTEGO01_SOSCHUNK_H
