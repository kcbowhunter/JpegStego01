//
// Created by ron on 25/12/17.
//

#ifndef JPEGSTEGO01_CHUNK_H
#define JPEGSTEGO01_CHUNK_H

#include <vector>
#include <string>

using namespace std;

class Chunk {
public:
    Chunk();
    Chunk(unsigned short marker);

    virtual ~Chunk();

    virtual bool Process(const vector<unsigned char>& bytes, int& offset, bool dump);

    virtual bool WriteToFile(FILE *file, const unsigned char *pRawData);

    unsigned short Marker() { return m_marker;}
    unsigned short Size()   { return m_size;}

    bool Soi() { return m_marker == 0XFFD8;}
    bool Eoi() { return m_marker == 0XFFD9;}

    unsigned short Marker() const { return m_marker; }
    unsigned short Size()   const { return m_size; }

    void SetName(const string& s) { m_name = s;}
    const string& Name() const { return m_name; }

    const string& Description() const { return m_description;}

    int GetDataStart() const { return m_dataStart; }
    int GetDataEnd()   const { return m_dataEnd; }

    bool GetWriteNewData() { return m_writeNewData; }
    void SetWriteNewData(const bool b) { m_writeNewData = b; }

    virtual bool ShowData(const unsigned char *pRawData);

    void SetNewData(vector<unsigned char>& newData);

protected:
    bool ReadMarker(const vector<unsigned char>& bytes, int& offset);
    bool ReadSize  (const vector<unsigned char>& bytes, const int offset);
    void DumpMarkerAndSize();

    bool WriteUnsignedShortToFile(FILE* file, unsigned short us);

    void SetDataStart(int ds) { m_dataStart = ds; }
    void SetDataEnd(  int de) { m_dataEnd = de; }

private:
    // 0xff?? marker for the jpeg chunk
    unsigned short m_marker;

    // size of data including size bytes
    unsigned short m_size;

    // Chunk Name
    string m_name;

    // Chunk Description
    string m_description;

    int m_dataStart;  // start of data in original file
    int m_dataEnd;    // end of data in original file

    // Write new chunk data to the file
    bool m_writeNewData;

    // new data to write to the segment
    vector<unsigned char> m_newData;
};

#endif //JPEGSTEGO01_CHUNK_H
