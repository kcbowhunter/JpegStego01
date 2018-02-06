//
// Created by ron on 25/12/17.
//

#ifndef JPEGSTEGO01_JPEG_H
#define JPEGSTEGO01_JPEG_H

#include <vector>
#include <list>
#include <string>

class Chunk;

using namespace std;

class Jpeg {
public:
    Jpeg();
    ~Jpeg();

    bool GetStatus() { return m_status; }

    bool Process(const vector<unsigned char>& bytes, bool dump);
    bool Process2(const vector<unsigned char>& bytes);
    vector<Chunk*> GetChunks() { return m_chunks;}

    // Write the jpeg chunks to the file
    // Insert newChunks into the Jpeg file when writing the existing chunks to the newfile
    // Insert newChunks after the corresponding afterChunk
    bool WriteToFile(const string& filename, list<int>& afterChunk, list<Chunk*>& newChunks);

    const unsigned char* RawData() { return m_pData;}

private:
    bool m_status;
    vector<Chunk*> m_chunks;
    const unsigned char* m_pData;  // raw jpeg data

private:
    Chunk* CreateChunk(unsigned short marker);

};


#endif //JPEGSTEGO01_JPEG_H