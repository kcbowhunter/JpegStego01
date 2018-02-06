//
// Created by ron on 19/01/18.
//

#ifndef JPEGSTEGO01_INSERTSEGMENTFROMFILETASK_H
#define JPEGSTEGO01_INSERTSEGMENTFROMFILETASK_H


#include "TaskBase.h"
#include <string>

using namespace std;

// Insert a new segment into a jpeg file, using data from a use specified file.
// The user specified file does not include the marker or the unsigned short segment size
// JpegStego filename InsertSegmentFromFile newfilename marker SegmentDataFile segnumber

class InsertSegmentFromFileTask : public TaskBase {
public:
    InsertSegmentFromFileTask();
    ~InsertSegmentFromFileTask();

    virtual bool Execute(Jpeg* jpeg, int argc, char* argv[]) override;

    string m_newFileName;       // new jpeg file name
    int    m_marker;            // marker for new segment
    string m_segmentDataFile;   // segment data file
    int    m_afterSegment;      // insert the new segment after this segment


};


#endif //JPEGSTEGO01_INSERTSEGMENTFROMFILETASK_H
