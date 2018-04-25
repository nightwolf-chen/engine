//
//  FlutterDartController.h
//  sources
//
//  Created by Jidong Chen on 2018/4/20.
//

#import <Foundation/Foundation.h>

/*
 * Provide some dart api interface.
 */

@interface FlutterDartVMController : NSObject

- (BOOL)loadScript:(NSString *)scrpitSource url:(NSString *)url;

+ (instancetype)sharedDartController;

@end
