//
// Created by ron on 30/12/17.
//

#ifndef JPEGSTEGO01_TASKBASE_H
#define JPEGSTEGO01_TASKBASE_H

class Jpeg;

// Base class for tasks
class TaskBase {
public:
    virtual bool Execute(Jpeg* jpeg, int argc, char* argv[]) = 0;

};


#endif //JPEGSTEGO01_TASKBASE_H
