//
// Created by ron on 30/12/17.
//

#include "DumpSegmentsTask.h"
#include "Jpeg.h"
#include "Chunk.h"

bool DumpSegmentsTask::Execute(Jpeg* jpeg, int argc, char* argv[])
{
    vector<Chunk*> chunks = jpeg->GetChunks();

    int count = 0;
    int marker = 0, size = 0, dataStart = 0;
    string name, desc;
    printf("Segment    Marker    Size  Offset  Name   Description\n");
    for(Chunk* ch : chunks)
    {
        marker = ch->Marker();
        size   = ch->Size();
        dataStart = ch->GetDataStart();
        name   = ch->Name();
        desc   = ch->Description();
        const char* n = name.empty() ? "?" : name.c_str();
        const char* d = desc.empty() ? "?" : desc.c_str();
        printf("  %2d)      0X%X  %6d  0X%04X %5s   %s\n", ++count, marker, size, dataStart, n, d);
    }

    return true;
}