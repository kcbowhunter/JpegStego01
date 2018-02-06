//
// Created by ron on 30/12/17.
//

#ifndef JPEGSTEGO01_EIOCHUNK_H
#define JPEGSTEGO01_EIOCHUNK_H

#include "Chunk.h"

class EoiChunk : public Chunk
{
public:
    EoiChunk();
    ~EoiChunk();

    virtual bool Process(const vector<unsigned char>& bytes, int& offset, bool dump) override;

    virtual bool WriteToFile(FILE *file, const unsigned char *pRawData) override;
};


#endif //JPEGSTEGO01_EIOCHUNK_H
