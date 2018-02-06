//
// Created by ron on 25/12/17.
//

#ifndef JPEGSTEGO01_UTILS_H
#define JPEGSTEGO01_UTILS_H

#include <string>
#include <vector>
#include <map>
#include <list>

class Chunk;

using namespace std;

class TaskBase;

class Utils {
public:
    static bool ReadBinaryFile(const string &filename, vector<unsigned char> &bytes, bool dump);

    static TaskBase* GetTask(int argc, char* argv[], bool& error);

    // map of marker value vs marker name, ie 0XFFE1 -> APP0
    static map<int, string> m_markerNameMap;

    // map of marker valud vs marker description
    static map<int, string> m_markerDescMap;

    static void SetupStaticData();

    static void SetupMarkerNameMap();
    static string GetMarkerName(const int marker);

    static void SetupMarkerDescMap();
    static string GetMarkerDesc(const int marker);

    // Get the chunks to be inserted at this point in the jpeg
    static list<Chunk*> GetChunks(list<int>& afterChunk, list<Chunk*>& newChunks, int count);

    // Return true if the filename ends in .jpg or .jpeg
    static bool ValidJpegFileName(const string& filename);
};


#endif //JPEGSTEGO01_UTILS_H
