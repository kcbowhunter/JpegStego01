//
// Created by ron on 25/12/17.
//

#include <cstdio>
#include "Chunk.h"
#include "Utils.h"


Chunk::Chunk()
        :
        m_marker(0),
        m_size(0),
        m_name(),
        m_description(),
        m_dataStart(0),
        m_dataEnd(0),
        m_writeNewData(false),
        m_newData()
{
}

Chunk::Chunk(unsigned short marker)
        :
        m_marker(marker),
        m_size(0),
        m_name(),
        m_description(),
        m_dataStart(0),
        m_dataEnd(0),
        m_writeNewData(false),
        m_newData()
{
}


Chunk::~Chunk()
{
}

bool Chunk::Process(const vector<unsigned char>& bytes, int& offset, bool dump)
{
    m_dataStart = offset; // start of data in original file
    ReadMarker(bytes, offset);

    ReadSize(bytes, offset);

    if (dump)
    {
        DumpMarkerAndSize();

        int i=0, k=0;
        for(int count=2; count < m_size; ++count)
        {
            i = offset+count;
            printf("%3d) %c 0x%x\n", k++, bytes[i], bytes[i]);

            if (count > 10)
                break;
        }
    }

    offset += m_size;

    // end of data in original file, (not including this byte)
    m_dataEnd = offset;

    return true;
}


bool Chunk::ReadMarker(const vector<unsigned char>& bytes, int& offset)
{
    unsigned char b0 = bytes[offset+0];
    unsigned char b1 = bytes[offset+1];

    m_marker = (b0 << 8) + b1;

    m_name        = Utils::GetMarkerName(m_marker);
    m_description = Utils::GetMarkerDesc(m_marker);

    offset += 2;

    return true;
}

bool Chunk::ReadSize(const vector<unsigned char>& bytes, const int offset)
{
    unsigned char b0 = bytes[offset+0];
    unsigned char b1 = bytes[offset+1];

    m_size = (b0 << 8) + b1;

    return true;
}

void Chunk::DumpMarkerAndSize()
{
    printf("marker 0x%x\n", m_marker);
    printf("size   0x%x %d\n", m_size, m_size);
}

bool Chunk::WriteToFile(FILE *file, const unsigned char *pRawData)
{
    bool status = true;
    WriteUnsignedShortToFile(file, m_marker);
    WriteUnsignedShortToFile(file, m_size);

    if (m_dataStart > 0)
    {
        const unsigned char* pStart = pRawData + m_dataStart + 4;
        size_t count = m_dataEnd - m_dataStart - 4;

        size_t size = 1;
        size_t nbytes = fwrite(pStart, size, count, file);
        if (nbytes != count)
        {
            printf("Error in Chunk::WriteToFile Writing Chunk, size mismatch %lu %lu\n", count, nbytes);
            return false;
        }
    }
    else if (m_newData.size() > 0)
    {
        const unsigned char* pStart = &m_newData[0];
        size_t size = 1;
        size_t count = m_newData.size();
        size_t nbytes = fwrite(pStart, size, count, file);
        if (nbytes != count)
        {
            printf("Error in Chunk::WriteToFile Writing Chunk, size mismatch %lu %lu\n", count, nbytes);
            return false;
        }
    }
    else
    {
        printf("Error in Chunk::WriteToFile -> marker 0x%x : missing data\n", m_marker);
        status = false;
    }

    return status;
}

// Write the Marker to the file
// Convert marker to big endian to conform to Jpeg
bool Chunk::WriteUnsignedShortToFile(FILE* file, unsigned short us)
{
    // high byte
    unsigned char b0 = (unsigned char)(us & 0X00FF);
    // low byte
    unsigned short test = (us & 0xFF00);
    unsigned char b1 = (unsigned char)(test >> 8);
    size_t size = 1;
    size_t count = 1;

    size_t nbytes = 0;
    nbytes = fwrite(&b1, size, count, file);
    nbytes = fwrite(&b0, size, count, file);

    // can't do this because Intel x86 chips are little endian
//    size_t nbytes = fwrite(&us, 1, 2, file);

    return true;
}


bool Chunk::ShowData(const unsigned char *pRawData)
{
    printf("Marker %8d 0x%x\n", m_marker, m_marker);

    printf("Size   %8d 0x%x\n", m_size, m_size);

    printf("Offset %8d 0x%x\n", m_dataStart, m_dataStart);

    int len = m_size - 2;  // includes the 2 byte size

    int cols = 10;

    int rows = len / cols;

    int last = len % (rows*cols);

    unsigned char byte = 0;
    int count = 0;
    int off   = m_dataStart + 4;
    for (int r = 0; r<rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            byte = pRawData[off + count++];
            printf("%02x ", byte);
        }
        printf("\n");
    }

    if (last > 0)
    {
        for (int c = count; c<len; ++c)
        {
            byte = pRawData[off + count++];
            printf("%02x ", byte);
        }
        printf("\n");
    }

    return true;
}

void Chunk::SetNewData(vector<unsigned char>& newData)
{
    m_newData = newData;

    // the size written for a jpeg chunk includes the actual data
    // plus the 2 bites for the unsigned short size
    m_size = (unsigned short)m_newData.size() + 2;
}