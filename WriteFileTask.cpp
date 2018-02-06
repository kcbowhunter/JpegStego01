//
// Created by ron on 01/01/18.
//

#include "WriteFileTask.h"
#include "Jpeg.h"
#include "Chunk.h"


WriteFileTask::WriteFileTask()
    :
    m_filename()
{
}

WriteFileTask::~WriteFileTask()
{
}


// JpegStego01 --WriteFile -filename=abc.jpg
bool WriteFileTask::Execute(Jpeg* jpeg, int argc, char* argv[])
{
    list<int> afterChunks;
    list<Chunk*> newChunks;
    bool status = jpeg->WriteToFile(m_filename, afterChunks, newChunks);
    return status;
}