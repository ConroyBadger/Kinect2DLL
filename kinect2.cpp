#include "kinect2.h"

Kinect2 *kinect;

Kinect2::Kinect2()
{
  colorFrames = 0;
  depthFrames = 0;

  depthFrame = NULL;

  if (ableToInitDefaultSensor()) {
    ready = ableToStartDepthStream();
  }
  else ready = false;
}

Kinect2::~Kinect2()
{
}

bool Kinect2::ableToInitDefaultSensor()
{
  HRESULT hr;

  hr = GetDefaultKinectSensor(&sensor);
  if (FAILED(hr)) return false;
  if (!sensor) return false;

  hr = sensor->Open();
  if (FAILED(hr)) return false;

  return true;
}

bool Kinect2::ableToStartDepthStream()
{
// get the depth source
  IDepthFrameSource* depthFrameSource = NULL;
  HRESULT hr = sensor->get_DepthFrameSource(&depthFrameSource);

// open the reader
  if (SUCCEEDED(hr)) {
    hr = depthFrameSource->OpenReader(&depthFrameReader);
    if (!SUCCEEDED(hr)) return false;
    if (!depthFrameReader) return false;
    return true;
  }
  return false;
}

void Kinect2::initSDK()
{
}

bool Kinect2::ableToUpdate()
{
  depthFrame = NULL;
  UINT nBufferSize = 0;

  HRESULT hr = depthFrameReader->AcquireLatestFrame(&depthFrame);

  if (SUCCEEDED(hr)) {
    INT64 nTime = 0;
    IFrameDescription* pFrameDescription = 0;

    depthData = NULL;

    hr = depthFrame->get_RelativeTime(&nTime);

    if (SUCCEEDED(hr)) {
      hr = depthFrame->get_FrameDescription(&pFrameDescription);
    }

    if (SUCCEEDED(hr)) {
      hr = depthFrame->AccessUnderlyingBuffer(&nBufferSize, &depthData);
    }

    if (pFrameDescription) {
      pFrameDescription->Release();
      pFrameDescription = NULL;
    }
  }

// buffer size isn't the size of the data in bytes but the number of elements
  int expectedSize = DEPTH_W * DEPTH_H;
  if (expectedSize != nBufferSize) return false;

  return (SUCCEEDED(hr));
}

void Kinect2::freeDepthFrame()
{
  if (depthFrame) {
    depthFrame->Release();
    depthFrame = NULL;
  }
}
