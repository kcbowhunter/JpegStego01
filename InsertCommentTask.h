//
// Created by ron on 11/01/18.
//

#ifndef JPEGSTEGO01_INSERTCOMMENTTASK_H
#define JPEGSTEGO01_INSERTCOMMENTTASK_H

#include "TaskBase.h"
#include <string>

using namespace std;

class Jpeg;

// Insert a comment task into the Jpeg after the nth chunk
// JpegStego filename InsertComment newfilename comment segnumber
class InsertCommentTask : public TaskBase {
public:
    InsertCommentTask();
    ~InsertCommentTask();

    virtual bool Execute(Jpeg* jpeg, int argc, char* argv[]) override;

    int m_afterChunk;
    string m_newFileName;
    string m_comment;
};


#endif //JPEGSTEGO01_INSERTCOMMENTTASK_H
