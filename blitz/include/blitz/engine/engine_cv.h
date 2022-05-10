// MIT License
//
// Copyright (c) 2021 Emmanuel Godwin
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef BLITZ_ENGINE_INCLUDE_ENGINE_ENGINECV_ENGINE_CV_H
#define BLITZ_ENGINE_INCLUDE_ENGINE_ENGINECV_ENGINE_CV_H

#include <fstream>

#include "engine/engine.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace engine {
namespace Cv {
int display_image(std::string);

void onTrackBarSlide(int, void*);
int playVideo(std::string);

int show_mat(cv::Mat, std::string = "Test");
class NamedWindow {
 public:
  NamedWindow() = delete;
  NamedWindow(std::string, cv::WindowFlags);
  void operator()();
  ~NamedWindow();

 private:
  std::string _name;
  cv::WindowFlags _size;
};

}  // namespace Cv

}  // namespace engine
#endif