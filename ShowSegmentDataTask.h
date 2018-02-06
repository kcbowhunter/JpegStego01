//
// Created by ron on 13/01/18.
//

#ifndef JPEGSTEGO01_SHOWSEGMENTDATATASK_H
#define JPEGSTEGO01_SHOWSEGMENTDATATASK_H


#include "TaskBase.h"

class ShowSegmentDataTask : public TaskBase {
public:
    ShowSegmentDataTask();
    ~ShowSegmentDataTask();

    virtual bool Execute(Jpeg* jpeg, int argc, char* argv[]) override;

    // show the data for this marker
    int m_marker;

    // marker count, display the data for the nth segment (chunk)
    int m_count;

};


#endif //JPEGSTEGO01_SHOWSEGMENTDATATASK_H
