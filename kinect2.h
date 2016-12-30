#ifndef KINECT_H
#define KINECT_H

#include "Kinect.h"

#define COLOR_W (1024)
#define COLOR_H (768)

#define DEPTH_W (512)
#define DEPTH_H (424)

class Kinect2;

extern Kinect2 *kinect;

class Kinect2
{

private:

public:
  IKinectSensor *sensor;
  IDepthFrameReader *depthFrameReader;
  IDepthFrame *depthFrame;

  UINT16 *depthData;

  int colorFrames;
  int depthFrames;

  bool ready;

  Kinect2();

  ~Kinect2();

  void initSDK();

  bool ableToInitDefaultSensor();
  bool ableToStartDepthStream();

  bool ableToUpdate();
  void freeDepthFrame();
};

#endif // KINECT_H
