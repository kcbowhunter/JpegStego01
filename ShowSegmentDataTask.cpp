//
// Created by ron on 13/01/18.
//

#include "ShowSegmentDataTask.h"

#include "Chunk.h"
#include "Jpeg.h"


ShowSegmentDataTask::ShowSegmentDataTask()
:
TaskBase(),
m_marker(0),
m_count(0)
{
}

ShowSegmentDataTask::~ShowSegmentDataTask()
{
}

bool ShowSegmentDataTask::Execute(Jpeg* jpeg, int argc, char* argv[])
{
    vector<Chunk*> chunks = jpeg->GetChunks();

    const unsigned char* rawdata = jpeg->RawData();

    int marker = 0;
    int count = 0;
    for(Chunk* ch: chunks)
    {
        marker = ch->Marker();
        if (marker == m_marker)
        {
            if (count++ == m_count)
            {
                ch->ShowData(rawdata);
                return true;
            }
        }
    }

    printf("Error: ShowSegmentDataTask, unable to find segment number %d of marker type %d 0X%X\n", m_count, m_marker, m_marker);

    return false;
}
