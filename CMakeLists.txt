cmake_minimum_required(VERSION 3.9)
project(JpegStego01)

set(CMAKE_CXX_STANDARD 14)

add_executable(JpegStego01 main.cpp Utils.cpp Utils.h Jpeg.cpp Jpeg.h Chunk.cpp Chunk.h SoiChunk.cpp SoiChunk.h SosChunk.cpp SosChunk.h EoiChunk.cpp EoiChunk.h TaskBase.cpp TaskBase.h DumpSegmentsTask.cpp DumpSegmentsTask.h WriteFileTask.cpp WriteFileTask.h StringUtils.cpp StringUtils.h ComChunk.cpp ComChunk.h InsertCommentTask.cpp InsertCommentTask.h ShowSegmentDataTask.cpp ShowSegmentDataTask.h InsertSegmentFromFileTask.cpp InsertSegmentFromFileTask.h)