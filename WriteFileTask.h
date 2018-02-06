//
// Created by ron on 01/01/18.
//

#ifndef JPEGSTEGO01_WRITEFILETASK_H
#define JPEGSTEGO01_WRITEFILETASK_H

#include "TaskBase.h"

#include <string>
using namespace std;

class WriteFileTask : public TaskBase {
public:
    WriteFileTask();
    ~WriteFileTask();

    virtual bool Execute(Jpeg* jpeg, int argc, char* argv[]) override;
    string m_filename;
};


#endif //JPEGSTEGO01_WRITEFILETASK_H
