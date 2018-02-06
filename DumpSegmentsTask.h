//
// Created by ron on 30/12/17.
//

#ifndef JPEGSTEGO01_DUMPSEGMENTSTASK_H
#define JPEGSTEGO01_DUMPSEGMENTSTASK_H

#include "TaskBase.h"

// Dump the segment marker, name and length for each segment in the jpeg file
class DumpSegmentsTask : public TaskBase
{
public:
    virtual bool Execute(Jpeg* jpeg, int argc, char* argv[]) override;

};


#endif //JPEGSTEGO01_DUMPSEGMENTSTASK_H
