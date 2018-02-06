//
// Created by ron on 11/01/18.
//

#include "ComChunk.h"

ComChunk::ComChunk()
    :
    Chunk(0xFFFE),
    m_comment()
{
}

ComChunk::~ComChunk(){}


bool ComChunk::WriteToFile(FILE *file, const unsigned char *pRawData)
{
    bool writeNewData = GetWriteNewData();

    bool status = false;
    if (writeNewData == false)
    {
        status = Chunk::WriteToFile(file, pRawData);
        return status;
    }

    WriteUnsignedShortToFile(file, Marker());  // Write the comment marker to the file

    unsigned short size = 2;  // the two size bytes are included in the chunk size

    // string size, add 1 for null terminating byte
    size_t dataSize = m_comment.size() + 1;

    size += (unsigned short)dataSize;
    WriteUnsignedShortToFile(file, size);

    const char* pString = m_comment.c_str();
    size_t sizew = 1;
    size_t nbytes = fwrite(pString, sizew, dataSize, file);

    if (nbytes != dataSize)
    {
        status = false;
        printf("Error writing new Comment chunk to jpeg\n");
    }
    else
        status = true;

    return status;
}

bool ComChunk::ShowData(const unsigned char *pRawData)
{
    int dataStart = GetDataStart();
    int size      = Size();

    // dataStart points to the 2 byte 0xfffe marker
    dataStart += 4;

    const char* pString = (const char*)pRawData + dataStart;
    printf("Comment Segment: %d bytes, '%s'\n", size, pString);


    return true;
}