// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_FLUTTERFISHHEADLESSDARTRUNNER_H_
#define FLUTTER_FLUTTERFISHHEADLESSDARTRUNNER_H_

#import <Foundation/Foundation.h>

#include "FlutterDartProject.h"
#include "FlutterMacros.h"

/**
 The FlutterHeadlessDartRunner runs Flutter Dart code with a null rasterizer,
 and no native drawing surface. It is appropriate for use in running Dart
 code e.g. in the background from a plugin.
*/
FLUTTER_EXPORT
@interface FlutterFishHeadlessDartRunner : NSObject

/**
 Runs a Dart function on an Isolate that is not the main application's Isolate.
 The first call will create a new Isolate. Subsequent calls will reuse that
 Isolate. The Isolate is destroyed when the FlutterHeadlessDartRunner is
 destroyed.

 - Parameter entrypoint: The name of a top-level function from the same Dart
   library that contains the app's main() function.
*/
- (void)runWithEntrypoint:(NSString*)entrypoint;

//DartProject for runner.
- (FlutterDartProject *)dartProject;

//Platformview for runner. For headless runner is null view which means it draws nothing on screen.
- (void *)platformView;

@end

#endif  // FLUTTER_FLUTTERHEADLESSDARTRUNNER_H_
