//
// Created by ron on 28/12/17.
//

#ifndef JPEGSTEGO01_SOICHUNK_H
#define JPEGSTEGO01_SOICHUNK_H

#include "Chunk.h"

class SoiChunk : public Chunk
{
public:
    SoiChunk();
   ~SoiChunk();

    virtual bool Process(const vector<unsigned char>& bytes, int& offset, bool dump) override;

    virtual bool WriteToFile(FILE *file, const unsigned char *pRawData) override;

};


#endif //JPEGSTEGO01_SOICHUNK_H
