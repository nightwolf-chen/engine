// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/flow/compositor_context.h"

#include "flutter/flow/layers/layer_tree.h"
#include "third_party/skia/include/core/SkCanvas.h"

namespace flow {

CompositorContext::CompositorContext() = default;

CompositorContext::~CompositorContext() = default;

void CompositorContext::BeginFrame(ScopedFrame& frame,
                                   bool enable_instrumentation) {
  if (enable_instrumentation) {
    frame_count_.Increment();
    frame_time_.Start();
  }
}

void CompositorContext::EndFrame(ScopedFrame& frame,
                                 bool enable_instrumentation) {
  raster_cache_.SweepAfterFrame();
  if (enable_instrumentation) {
    frame_time_.Stop();
  }
}

std::unique_ptr<CompositorContext::ScopedFrame> CompositorContext::AcquireFrame(
    GrContext* gr_context,
    SkCanvas* canvas,
    bool instrumentation_enabled) {
  return std::make_unique<ScopedFrame>(*this, gr_context, canvas,
                                       instrumentation_enabled);
}

CompositorContext::ScopedFrame::ScopedFrame(CompositorContext& context,
                                            GrContext* gr_context,
                                            SkCanvas* canvas,
                                            bool instrumentation_enabled)
    : context_(context),
      gr_context_(gr_context),
      canvas_(canvas),
      instrumentation_enabled_(instrumentation_enabled) {
  context_.BeginFrame(*this, instrumentation_enabled_);
}

CompositorContext::ScopedFrame::~ScopedFrame() {
  context_.EndFrame(*this, instrumentation_enabled_);
}

bool CompositorContext::ScopedFrame::Raster(flow::LayerTree& layer_tree,
                                            bool ignore_raster_cache) {
  layer_tree.Preroll(*this, ignore_raster_cache);
  layer_tree.Paint(*this);
  return true;
}

void CompositorContext::OnGrContextCreated() {
  texture_registry_.OnGrContextCreated();
}

void CompositorContext::OnGrContextDestroyed() {
  texture_registry_.OnGrContextDestroyed();
  raster_cache_.Clear();
}

}  // namespace flow
