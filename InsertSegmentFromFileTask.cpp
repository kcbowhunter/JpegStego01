//
// Created by ron on 19/01/18.
//


#include "InsertSegmentFromFileTask.h"
#include "Utils.h"
#include "Chunk.h"
#include "Jpeg.h"

using namespace std;

// Insert a new segment into a jpeg file, using data from a use specified file.
// The user specified file does not include the marker or the unsigned short segment size
// JpegStego filename InsertSegmentFromFile newfilename marker SegmentDataFile segnumber
InsertSegmentFromFileTask::InsertSegmentFromFileTask()
    :
    TaskBase(),
    m_newFileName(),
    m_marker(0),
    m_segmentDataFile(),
    m_afterSegment()
{
}


InsertSegmentFromFileTask::~InsertSegmentFromFileTask()
{
}

bool InsertSegmentFromFileTask::Execute(Jpeg* jpeg, int argc, char* argv[])
{
    printf("InsertSegmentFromFileTask::Execute...\n");
    vector<unsigned char> data;

    bool dump = false;
    bool status = Utils::ReadBinaryFile(m_segmentDataFile, data, dump);

    if (status == false)
    {
        printf("Error: failed to read file %s\n", m_segmentDataFile.c_str());
        return false;
    }

    unsigned short marker = (unsigned short)m_marker;
    Chunk *chunk = new Chunk(marker);
    chunk->SetWriteNewData(true);
    chunk->SetNewData(data);

    list<int> afterChunk;
    list<Chunk*> newChunks;

    afterChunk.push_back(m_afterSegment);
    newChunks.push_back(chunk);

    status = jpeg->WriteToFile(m_newFileName, afterChunk, newChunks);


    return status;
}