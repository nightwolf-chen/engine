// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import "flutter/shell/platform/darwin/ios/framework/Headers/FlutterFishBinaryMessenger.h"

#include <memory>

#include "flutter/fml/platform/darwin/scoped_nsobject.h"
#include "flutter/shell/platform/darwin/ios/platform_null_view_ios.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/FlutterDartProject_Internal.h"
#include "flutter/common/threads.h"
#include "flutter/flow/texture.h"
#include "flutter/fml/platform/darwin/platform_version.h"
#include "flutter/fml/platform/darwin/scoped_block.h"
#include "flutter/fml/platform/darwin/scoped_nsobject.h"
#include "flutter/lib/ui/painting/resource_context.h"
#include "flutter/shell/platform/darwin/common/buffer_conversions.h"
#include "flutter/shell/platform/darwin/common/platform_mac.h"
#include "flutter/shell/platform/darwin/ios/framework/Headers/FlutterCodecs.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/FlutterDartProject_Internal.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/FlutterPlatformPlugin.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/FlutterTextInputDelegate.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/FlutterTextInputPlugin.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/flutter_main_ios.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/flutter_touch_mapper.h"
#include "flutter/shell/platform/darwin/ios/ios_external_texture_gl.h"
#include "flutter/shell/platform/darwin/ios/platform_view_ios.h"
#include "lib/fxl/functional/make_copyable.h"
#include "lib/fxl/time/time_delta.h"

#import <UIKit/UIKit.h>

#include <sys/cdefs.h>

//class PlatformView;

namespace {
    
    typedef void (^PlatformMessageResponseCallback)(NSData*);
    
    class PlatformMessageResponseDarwin : public blink::PlatformMessageResponse {
        FRIEND_MAKE_REF_COUNTED(PlatformMessageResponseDarwin);
        
    public:
        void Complete(std::vector<uint8_t> data) override {
            fxl::RefPtr<PlatformMessageResponseDarwin> self(this);
            blink::Threads::Platform()->PostTask(
                                                 fxl::MakeCopyable([ self, data = std::move(data) ]() mutable {
                self->callback_.get()(shell::GetNSDataFromVector(data));
            }));
        }
        
        void CompleteEmpty() override {
            fxl::RefPtr<PlatformMessageResponseDarwin> self(this);
            blink::Threads::Platform()->PostTask(
                                                 fxl::MakeCopyable([self]() mutable { self->callback_.get()(nil); }));
        }
        
    private:
        explicit PlatformMessageResponseDarwin(PlatformMessageResponseCallback callback)
        : callback_(callback, fml::OwnershipPolicy::Retain) {}
        
        fml::ScopedBlock<PlatformMessageResponseCallback> callback_;
    };
    
}  // namespace

@interface FlutterFishBinaryMessenger (){
    shell::PlatformNullViewIOS *_platformView;
    FlutterDartProject *_dartProject;
}
@end

@implementation FlutterFishBinaryMessenger
#pragma mark - FlutterBinaryMessenger

- (void)sendOnChannel:(NSString*)channel message:(NSData*)message {
    [self sendOnChannel:channel message:message binaryReply:nil];
}

- (void)sendOnChannel:(NSString*)channel
              message:(NSData*)message
          binaryReply:(FlutterBinaryReply)callback {
    
    if (_platformView == NULL) {
        NSLog(@"Platform view is NULL do nothing and return!");
        return;
    }
    
    NSAssert(channel, @"The channel must not be null");
    fxl::RefPtr<PlatformMessageResponseDarwin> response =
    (callback == nil) ? nullptr
    : fxl::MakeRefCounted<PlatformMessageResponseDarwin>(^(NSData* reply) {
        callback(reply);
    });
    fxl::RefPtr<blink::PlatformMessage> platformMessage =
    (message == nil) ? fxl::MakeRefCounted<blink::PlatformMessage>(channel.UTF8String, response)
    : fxl::MakeRefCounted<blink::PlatformMessage>(
                                                  channel.UTF8String, shell::GetVectorFromNSData(message), response);
    _platformView->DispatchPlatformMessage(platformMessage);
    
    NSLog(@"send on channel %@ msg:%@",channel,message);
    
}

- (void)setMessageHandlerOnChannel:(NSString*)channel
              binaryMessageHandler:(FlutterBinaryMessageHandler)handler {
    NSAssert(channel, @"The channel must not be null");
    if (_platformView == NULL) {
        NSLog(@"Platform view is NULL do nothing and return!");
        return;
    }
    _platformView->platform_message_router().SetMessageHandler(channel.UTF8String, handler);
    NSLog(@"send message handler %@",channel);
}

- (void)setPlatformView:(void *)platformView
{
    _platformView = (shell::PlatformNullViewIOS *)platformView;
}

- (void *)platformView
{
    return (void *)_platformView;
}

- (void)setDartProject:(FlutterDartProject *)project
{
    _dartProject = project;
}

- (FlutterDartProject *)dartProject
{
    return _dartProject;
}


@end
