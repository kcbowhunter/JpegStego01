//
// Created by ron on 25/12/17.
//

#include <strings.h>
#include "Utils.h"
#include "TaskBase.h"
#include "DumpSegmentsTask.h"
#include "WriteFileTask.h"
#include "InsertCommentTask.h"
#include "ShowSegmentDataTask.h"
#include "InsertSegmentFromFileTask.h"

map<int, string> Utils::m_markerNameMap;
map<int, string> Utils::m_markerDescMap;

bool Utils::ReadBinaryFile(const string &filename, vector<unsigned char> &bytes, bool dump)
{
    bool status = true;

    if (filename.empty())
    {
        printf("Filename cannot be empty\n");
        return false;
    }

    FILE* file = fopen(filename.c_str(), "r");

    if (file == NULL)
    {
        printf("Unable to open file %s\n", filename.c_str());
        return false;
    }

    int seekvalue = fseek(file, 0L, SEEK_END);
    if (seekvalue == -1)
    {
        printf("fseek failed - errno = %d\n", errno);
        fclose(file);
        return false;
    }

    unsigned int size = (unsigned int) ftell(file);

    bytes.resize(size);

    if (dump)
        printf("filesize is %u bytes\n", size);

    size_t count = size;

    rewind(file);

    unsigned char* ptr = &bytes[0];
    unsigned int nread = fread(ptr, 1, count, file);

    if (nread != count)
    {
        printf("fread failed to read %u bytes\n", nread);
        return false;
    }

    fclose(file);

    return status;
}

// Create the task to execute based on the command line
TaskBase *Utils::GetTask(int argc, char **argv, bool& error)
{
    TaskBase *taskbase = nullptr;
    error = false;

    // If no task is requested, dump the jpeg segments
    if (argc == 2)
    {
        taskbase = new DumpSegmentsTask();
    }
    else
    {
        string arg2 = string(argv[2]);
        if (arg2 == "ShowSegments")
        {
            taskbase = new DumpSegmentsTask();
        }
        else if (arg2 == "WriteFile")
        {
            //     0         1       2         3
            // JpegStego filename WriteFile newfilename
            WriteFileTask *wft = new WriteFileTask();
            taskbase = wft;
            if (argc == 4)
            {
                string filename(argv[3]);
                wft->m_filename = filename;
            }
            else
            {
                printf("Error: WriteFile but no filename specified\n");
                error = true;
            }
        }
        else if (arg2 == "InsertComment")
        {
            if (argc != 6)
            {
                printf("Usage: JpegStego filename InsertComment newfilename comment segnumber\n");
                error = true;
                return nullptr;
            }
            //      0        1         2           3          4        5
            // JpegStego filename InsertComment newfilename comment segnumber
            InsertCommentTask *ict = new InsertCommentTask();
            string filename(argv[3]);
            ict->m_newFileName = filename;

            string comment(argv[4]);
            ict->m_comment = comment;

            int after(atoi(argv[5]));
            ict->m_afterChunk = after;

            taskbase = ict;

            printf("Taskbase = %p\n", taskbase);
        }
        else if (arg2 == "ShowSegmentData")
        {
            // JpegStego filename ShowSegmentData 0xffxx n
            if (argc != 5)
            {
                printf("Usage: JpegStego filename ShowSegmentdata 0xffxx n\n");
                error = true;
                return nullptr;
            }

            auto *ssd = new ShowSegmentDataTask();
            taskbase = ssd;

            ssd->m_marker = strtol(argv[3], nullptr, 16);
            ssd->m_count  = atoi(argv[4]);

        }
        else if (arg2 == "InsertSegmentFromFile")
        {
        //    0        1         2                          3        4         5             6
        //JpegStego filename InsertSegmentFromFileTask newfilename 0xmarker SegmentDataFile segnumber
            if (argc != 7)
            {
                printf("Usage: JpegStego filename InsertSegmentFromFile newfilename marker SegmentDataFile segnumber\n");
                error = true;
                return nullptr;
            }

            auto *isfft = new InsertSegmentFromFileTask();
            isfft->m_newFileName = string(argv[3]);
            isfft->m_marker      = strtol(argv[4], nullptr, 16);
            isfft->m_segmentDataFile = string(argv[5]);
            isfft->m_afterSegment    = atoi(argv[6]);

            return isfft;
        }
        else
        {
            printf("Error: Unknown action %s\n", arg2.c_str());
            error = true;
        }
    }

    return taskbase;
}

void Utils::SetupStaticData()
{
    SetupMarkerNameMap();
    SetupMarkerDescMap();
}


void Utils::SetupMarkerNameMap()
{
    int base = 0xffe0;
    const int SIZE=32;
    char buffer[SIZE];
    for (int i=0; i<16; ++i)
    {
        snprintf(buffer, SIZE, "APP%X", i);
        m_markerNameMap[base+i] = string(buffer);

    }
//    m_markerNameMap[0XFFE0] = string("APP0");
//    m_markerNameMap[0XFFE1] = string("APP1");
//    m_markerNameMap[0XFFE2] = string("APP2");
    m_markerNameMap[0XFFDB] = string("DQT");
    m_markerNameMap[0XFFC2] = string("SOF2");
    m_markerNameMap[0XFFC4] = string("DHT");
    m_markerNameMap[0XFFDD] = string("DRI");
    m_markerNameMap[0XFFC0] = string("SOF");
    m_markerNameMap[0XFFDA] = string("SOS");
    m_markerNameMap[0XFFD8] = string("SOI");
    m_markerNameMap[0XFFD9] = string("EIO");
    m_markerNameMap[0XFFFE] = string("COM");
}

void Utils::SetupMarkerDescMap()
{
    int base = 0xffe0;
    const int SIZE=64;
    char buffer[SIZE];
    for (int i=0; i<16; ++i)
    {
        snprintf(buffer, SIZE, "Application Data %X", i);
        m_markerDescMap[base+i] = string(buffer);
    }

//    m_markerDescMap[0XFFE0] = string("Application Data 0");
//    m_markerDescMap[0XFFE1] = string("Application Data 1");
//    m_markerDescMap[0XFFE2] = string("Application Data 2");
    m_markerDescMap[0XFFDB] = string("Define Quantization Table");
    m_markerDescMap[0XFFC2] = string("Start of Frame Progressive DCT");
    m_markerDescMap[0XFFC4] = string("Define Huffman Table");
    m_markerDescMap[0XFFDD] = string("Define Restart Interoperability");
    m_markerDescMap[0XFFC0] = string("Start of Frame");
    m_markerDescMap[0XFFDA] = string("Start of Scan");
    m_markerDescMap[0XFFD8] = string("Start of Image");
    m_markerDescMap[0XFFD9] = string("End of Image");
    m_markerDescMap[0XFFFE] = string("Comment");
}


// Return the marker name given the marker value
string Utils::GetMarkerName(const int marker)
{
    string name;
    auto iter = m_markerNameMap.find(marker);
    if (iter == m_markerNameMap.end())
        return name;

    name = (*iter).second;

    return name;
}

// Return the marker name given the marker value
string Utils::GetMarkerDesc(const int marker)
{
    string desc;
    auto iter = m_markerDescMap.find(marker);
    if (iter == m_markerDescMap.end())
        return desc;

    desc = (*iter).second;

    return desc;
}

// Get the chunks to be inserted at this point in the jpeg
// Return a list of chunks that correspond to count (insert after the nth chunk in the original jpeg)
list<Chunk*> Utils::GetChunks(list<int>& afterChunk, list<Chunk*>& newChunks, int count)
{
    list<Chunk*> chunks;

    if (afterChunk.size() != newChunks.size())
    {
        printf("Internal Error: Utils::GetChunks, different sizes\n");
        return chunks;
    }

    auto intIter = afterChunk.begin();
    for(Chunk* chunk : newChunks)
    {
        int after = *intIter;
        if (after == count)
        {
            chunks.push_back(chunk);
        }
        ++intIter;
    }

    return chunks;
}


// Return true if the filename ends in .jpg or .jpeg
bool Utils::ValidJpegFileName(const string& filename)
{
    if (filename.empty())
    {
        printf("Empty filename is not valid for a jpeg file\n");
        return false;
    }

    size_t len = filename.length();
    if (len <= 4)
    {
        printf("%s is not a valid jpg filename\n", filename.c_str());
        return false;
    }

    size_t pos = filename.find('.');
    if (pos == string::npos)
    {
        printf("%s is not a valid jpeg file name, missing .jpg\n", filename.c_str());
        return false;
    }

    string ext = filename.substr(pos+1);

    if (strcasecmp("jpg", ext.c_str()) == 0)
    {
        return true;
    }

    if (strcasecmp("jpeg", ext.c_str()) == 0)
    {
        return true;
    }

    printf("Error: %s is not a valid jpg file name\n", filename.c_str());

    return false;
}
