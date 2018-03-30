// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SHELL_PLATFORM_IOS_PLATFORM_NULL_VIEW_IOS_H_
#define SHELL_PLATFORM_IOS_PLATFORM_NULL_VIEW_IOS_H_



#include <memory>

#include "flutter/fml/memory/weak_ptr.h"
#include "flutter/shell/common/platform_view.h"
#include "flutter/shell/common/null_platform_view.h"
#include "flutter/shell/platform/darwin/ios/framework/Headers/FlutterTexture.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/FlutterTextInputPlugin.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/accessibility_bridge.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/platform_message_router.h"
#include "flutter/shell/platform/darwin/ios/ios_surface.h"
#include "lib/fxl/functional/closure.h"
#include "lib/fxl/macros.h"

namespace shell {

class PlatformNullViewIOS : public NullPlatformView {
    
public:
    
    PlatformMessageRouter& platform_message_router() {
        return platform_message_router_;
    }
    
    NSObject<FlutterBinaryMessenger>* binary_messenger() const {
        return binary_messenger_;
    }
    
    void HandlePlatformMessage(fxl::RefPtr<blink::PlatformMessage> message) override;

private:
    NSObject<FlutterBinaryMessenger>* binary_messenger_;
    PlatformMessageRouter platform_message_router_;
};

}  // namespace shell

#endif  // SHELL_PLATFORM_IOS_PLATFORM_VIEW_IOS_H_
