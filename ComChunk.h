//
// Created by ron on 11/01/18.
//

#ifndef JPEGSTEGO01_COMCHUNK_H
#define JPEGSTEGO01_COMCHUNK_H

#include "Chunk.h"

class ComChunk : public Chunk {
public:
    ComChunk();
    ~ComChunk();

    string m_comment;  // pure string comment

    virtual bool WriteToFile(FILE *file, const unsigned char *pRawData) override;

    virtual bool ShowData(const unsigned char *pRawData) override;
};


#endif //JPEGSTEGO01_COMCHUNK_H
