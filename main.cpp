#include <cstdio>
#include <vector>
#include "Utils.h"
#include "Jpeg.h"
#include "TaskBase.h"

// https://en.wikipedia.org/wiki/JPEG

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1)
    {
        printf("Usage: JpegStego filename action [options]\n");
        printf("\n");
        printf("       JpegStego filename ShowSegments\n");
        printf("       JpegStego filename WriteFile newfilename\n");
        printf("       JpegStego filename ShowSegmentData 0xFFxx n\n");
        printf("       JpegStego filename InsertComment newfilename comment segnumber\n");
        printf("       JpegStego filename InsertSegmentFromFile newfilename 0xmarker SegmentDataFile segnumber\n");
        printf(" ");
        return 1;
    }

    Utils::SetupStaticData();

    printf("JpegStego %s begin...\n", argv[1]);

    bool dump = false;

    vector<unsigned char> bytes;

    string filename(argv[1]);

    if (!Utils::ValidJpegFileName(filename))
    {
        return 1;  // invalid jpeg file name
    }

    if (dump)
        printf("Filename is %s\n", filename.c_str());

    bool status = Utils::ReadBinaryFile(filename, bytes, dump);

    if (!status) {
        printf("Error reading jpeg file %s\n", filename.c_str());
        return 1;
    }

    Jpeg *jpeg = new Jpeg();

    status = jpeg->Process(bytes, dump);

    // Execute the task requested by the user
    bool error = false;
    TaskBase *taskbase = Utils::GetTask(argc, argv, error);

    if (error) {
        printf("Error processing argument list\n");
    }
    else if (taskbase == nullptr)
    {
        printf("Error creating internal task object\n");
    }
    else
    {
        taskbase->Execute(jpeg, argc, argv);
    }

    delete jpeg;
    delete taskbase;

    printf("... JpegStego end\n");
    return 0;
}