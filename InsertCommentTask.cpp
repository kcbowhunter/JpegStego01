//
// Created by ron on 11/01/18.
//

#include "InsertCommentTask.h"
#include "ComChunk.h"
#include "Jpeg.h"

#include <list>

InsertCommentTask::InsertCommentTask()
        :
        TaskBase(),
        m_afterChunk(0),
        m_newFileName(),
        m_comment()
    {}

InsertCommentTask::~InsertCommentTask() {}

bool InsertCommentTask::Execute(Jpeg* jpeg, int argc, char* argv[])
{
    ComChunk *com = new ComChunk();
    com->SetWriteNewData(true);  // write a new chunk to the jpeg

    com->m_comment = m_comment;

    list<int> afterChunk;
    if (m_afterChunk > 0)
        afterChunk.push_back(m_afterChunk);
    else
        afterChunk.push_back(1);

    list<Chunk*> newChunks;
    newChunks.push_back(com);

    bool status = jpeg->WriteToFile(m_newFileName, afterChunk, newChunks);

    return status;
}

