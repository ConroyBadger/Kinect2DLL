#include "kinect2dll.h"

Kinect2DLL::Kinect2DLL()
{
}

extern "C" __declspec(dllexport) int getVersion()
{
  return 1;
}

extern "C" __declspec(dllexport) bool ableToInitialize()
{
  kinect = new Kinect2();//NULL);
  return kinect->ready;
}

extern "C" __declspec(dllexport) UINT16* getFrame()
{
  if (!kinect->ready) return NULL;

  if (kinect->ableToUpdate()) {
    return kinect->depthData;
  }

  return NULL;
}

// this needs to be called even if getFrame() returns NULL as
// kinect->ableToUpdate() can fail even if a depthFrame is acquired
// kinect->freeDepthFrame checks for NULL so it's safe
extern "C" __declspec(dllexport) void doneFrame()
{
  kinect->freeDepthFrame();
}

extern "C" __declspec(dllexport) void shutDown()
{
  delete kinect;
}



