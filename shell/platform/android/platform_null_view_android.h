//
//  platform_null_view_android.hpp
//  sources
//
//  Created by Jidong Chen on 2018/4/2.
//

#ifndef SHELL_PLATFORM_ANDROID_NULL_PLATFORM_VIEW_ANDROID_H_
#define SHELL_PLATFORM_ANDROID_NULL_PLATFORM_VIEW_ANDROID_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "flutter/fml/platform/android/jni_weak_ref.h"
#include "flutter/fml/platform/android/scoped_java_ref.h"
#include "flutter/lib/ui/window/platform_message.h"
#include "flutter/shell/common/platform_view.h"
#include "flutter/shell/common/null_platform_view.h"
#include "flutter/shell/platform/android/android_native_window.h"
#include "flutter/shell/platform/android/android_surface.h"
#include "lib/fxl/memory/weak_ptr.h"



namespace shell {
    
    class PlatformNullViewAndroid : public  NullPlatformView{
    public:
        static bool Register(JNIEnv* env);
        
        PlatformNullViewAndroid();
        
        ~PlatformNullViewAndroid() override;
        
        virtual void Attach() override;
        
        void Detach();
        
        void SurfaceCreated(JNIEnv* env, jobject jsurface, jint backgroundColor);
        
        void SurfaceChanged(jint width, jint height);
        
        void SurfaceDestroyed();
        
        void RunBundleAndSnapshot(JNIEnv* env, std::string bundle_path,
                                  std::string snapshot_override,
                                  std::string entrypoint,
                                  bool reuse_isolate,
                                  jobject assetManager);
        
        void RunBundleAndSource(std::string bundle_path,
                                std::string main,
                                std::string packages);
        
        void SetViewportMetrics(jfloat device_pixel_ratio,
                                jint physical_width,
                                jint physical_height,
                                jint physical_padding_top,
                                jint physical_padding_right,
                                jint physical_padding_bottom,
                                jint physical_padding_left,
                                jint physical_view_inset_top,
                                jint physical_view_inset_right,
                                jint physical_view_inset_bottom,
                                jint physical_view_inset_left);
        
        void DispatchPlatformMessage(JNIEnv* env,
                                     std::string name,
                                     jobject message_data,
                                     jint message_position,
                                     jint response_id);
        
        void DispatchEmptyPlatformMessage(JNIEnv* env,
                                          std::string name,
                                          jint response_id);
        
        void DispatchPointerDataPacket(JNIEnv* env, jobject buffer, jint position);
        
        void InvokePlatformMessageResponseCallback(JNIEnv* env,
                                                   jint response_id,
                                                   jobject java_response_data,
                                                   jint java_response_position);
        
        void InvokePlatformMessageEmptyResponseCallback(JNIEnv* env,
                                                        jint response_id);
        
        void DispatchSemanticsAction(JNIEnv* env,
                                     jint id,
                                     jint action,
                                     jobject args,
                                     jint args_position);
        
        void SetSemanticsEnabled(jboolean enabled);
        
        fml::jni::ScopedJavaLocalRef<jobject> GetBitmap(JNIEnv* env);
        
        VsyncWaiter* GetVsyncWaiter() override;
        
        bool ResourceContextMakeCurrent() override;
        
        void UpdateSemantics(blink::SemanticsNodeUpdates update) override;
        
        void HandlePlatformMessage(
                                   fxl::RefPtr<blink::PlatformMessage> message) override;
        
        void HandlePlatformMessageResponse(int response_id,
                                           std::vector<uint8_t> data);
        
        void HandlePlatformMessageEmptyResponse(int response_id);
        
        void RunFromSource(const std::string& assets_directory,
                           const std::string& main,
                           const std::string& packages) override;
        
        void SetAssetBundlePathOnUI(std::string bundle_path);
        
        void SetAssetBundlePath(const std::string& assets_directory) override;
        
        void RegisterExternalTexture(
                                     int64_t texture_id,
                                     const fml::jni::JavaObjectWeakGlobalRef& surface_texture);
        
        void MarkTextureFrameAvailable(int64_t texture_id) override;
        
        void set_flutter_view(const fml::jni::JavaObjectWeakGlobalRef& flutter_view) {
            flutter_view_ = flutter_view;
        }
        
    private:
        std::unique_ptr<AndroidSurface> android_surface_;
        fml::jni::JavaObjectWeakGlobalRef flutter_view_;
        // We use id 0 to mean that no response is expected.
        int next_response_id_ = 1;
        std::unordered_map<int, fxl::RefPtr<blink::PlatformMessageResponse>>
        pending_responses_;
        
        void UpdateThreadPriorities();
        
        void ReleaseSurface();
        
        void GetBitmapGpuTask(jobject* pixels_out, SkISize* size_out);
        
        FXL_DISALLOW_COPY_AND_ASSIGN(PlatformNullViewAndroid);
    };
    
}  // namespace shell

#endif /* platform_null_view_android_hpp */
