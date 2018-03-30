// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_FLUTTERFISHBINARYMESSENGER_H_
#define FLUTTER_FLUTTERFISHBINARYMESSENGER_H_

#import <Foundation/Foundation.h>

#include "FlutterDartProject.h"
#include "FlutterMacros.h"
#import "FlutterBinaryMessenger.h"

//FleaMarket defaul messenger implement.

FLUTTER_EXPORT
@interface FlutterFishBinaryMessenger : NSObject<FlutterBinaryMessenger>

@property (nonatomic,weak) FlutterDartProject *dartProject;

- (FlutterDartProject *)dartProject;

- (void)setDartProject:(FlutterDartProject *)project;

- (void *)platformView;

- (void )setPlatformView:(void *)platformView;
@end

#endif  // FLUTTER_FLUTTERHEADLESSDARTRUNNER_H_
