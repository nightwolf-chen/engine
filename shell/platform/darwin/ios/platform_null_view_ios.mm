

#include "flutter/shell/platform/darwin/ios/platform_null_view_ios.h"
#include "flutter/shell/common/null_rasterizer.h"
#include "flutter/shell/common/shell.h"

#include <stdio.h>


namespace shell {
    
void PlatformNullViewIOS::HandlePlatformMessage(fxl::RefPtr<blink::PlatformMessage> message) {
    platform_message_router_.HandlePlatformMessage(std::move(message));
}

}  // namespace shell
