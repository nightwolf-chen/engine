//
//  FlutterDartController.m
//  sources
//
//  Created by Jidong Chen on 2018/4/20.
//

#define FML_USED_ON_EMBEDDER

#include "flutter/shell/platform/darwin/ios/framework/Headers/FlutterDartController.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/FlutterDartController_Internal.h"


//#include "third_party/dart/runtime/include/dart_api.h"
//#include "flutter/common/task_runners.h"


@implementation FlutterDartVMController

+ (instancetype)sharedDartController
{
    static id instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [self new];
    });
    
    return instance;
}

- (BOOL)loadScript:(NSString *)scrpitSource url:(NSString *)url
{
    
//    blink::TaskRunners::GetUITaskRunner()->Post
    
//    Dart_Handle scriptHandle = Dart_NewStringFromCString(scrpitSource.UTF8String);
//    Dart_Handle urlHandle = Dart_NewStringFromCString(url.UTF8String);
//    Dart_Handle ret = Dart_LoadScript(urlHandle, Dart_Null(), scriptHandle, 0, 0);
//    return ret != NULL;
    
    
    return NO;
}

@end
