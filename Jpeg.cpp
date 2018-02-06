//
// Created by ron on 25/12/17.
//

#include "Jpeg.h"
#include "Chunk.h"
#include "SoiChunk.h"
#include "SosChunk.h"
#include "EoiChunk.h"
#include "ComChunk.h"
#include "Utils.h"


Jpeg::Jpeg()
    :
    m_status(true),
    m_pData(nullptr)
{

}

Jpeg::~Jpeg()
{
    for(auto pChunk: m_chunks)
    {
        delete pChunk;
    }
    m_chunks.clear();
}


bool Jpeg::Process(const vector<unsigned char>& bytes, bool dump)
{
    int offset = 0;
    bool status = false;
    m_pData = &bytes[0];

    Chunk *chunk = nullptr;
    while (1)
    {
        unsigned char b0 = bytes[offset+0];
        unsigned char b1 = bytes[offset+1];

        unsigned short marker = (b0 << 8) + b1;

        chunk = CreateChunk(marker);

        m_chunks.push_back(chunk);

        status = chunk->Process(bytes, offset, dump);
        if (!status)
            return false;

        if (chunk->Eoi())
            break;
    }

    return true;
}


Chunk* Jpeg::CreateChunk(unsigned short marker)
{
    Chunk *chunk = nullptr;

    if (marker == 0xFFD8)
        chunk = new SoiChunk();
    else if (marker == 0XFFD9)
        chunk = new EoiChunk();
    else if (marker == 0XFFDA)
        chunk = new SosChunk();
    else if (marker == 0XFFFE)
        chunk = new ComChunk();
    else
        chunk = new Chunk();

    return chunk;
}

bool Jpeg::Process2(const vector<unsigned char>& bytes)
{
    bool dump = false;
    Chunk *chunk = new Chunk();
    m_chunks.push_back(chunk);

    int offset = 0;

    bool status = chunk->Process(bytes, offset, dump);
    if (!status)
        return false;

    chunk = new Chunk();
    m_chunks.push_back(chunk);

    status = chunk->Process(bytes, offset, dump);
    if (!status)
        return false;

    chunk = new Chunk();
    m_chunks.push_back(chunk);

    status = chunk->Process(bytes, offset, dump);
    if (!status)
        return false;

    return true;
}

// Write the jpeg chunks to the file
// Insert newChunks into the Jpeg file when writing the existing chunks to the newfile
// Insert newChunks after the corresponding afterChunk
bool Jpeg::WriteToFile(const string& filename, list<int>& afterChunk, list<Chunk*>& newChunks)
{
    if (filename.empty())
    {
        printf("Error in Jpeg::Write - filename is empty\n");
        return false;
    }

    FILE *file = fopen(filename.c_str(), "w");
    if (file == nullptr)
    {
        printf("Error opening file %s\n", filename.c_str());
        return false;
    }

    int count = 0;
    bool status = true;
    for(auto pChunk: m_chunks)
    {
        status = pChunk->WriteToFile(file, m_pData);
        if (!status)
        {
            printf("Error writing to file %s\n", filename.c_str());
            break;
        }

        // insert new Chunks
        if (newChunks.empty() == false)
        {
            // Get the chunks to be inserted at this point in the jpeg
            list<Chunk*> chunks = Utils::GetChunks(afterChunk, newChunks, count);
            if (chunks.empty() == false)
            {
                for(Chunk* ch : chunks)
                {
                    ch->WriteToFile(file, nullptr);
                }
            }
        }
        ++count;
    }

    fclose(file);

    return status;
}