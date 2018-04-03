package io.flutter.app;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import io.flutter.view.FlutterNativeView;
import io.flutter.view.FlutterView;
import io.flutter.view.FlutterMain;

public class FlutterHeadlessRunner{
    private FlutterView mFlutterView;
    private FlutterNativeView mNativeView;
    private Context mContext;

    public FlutterHeadlessRunner(Context context){
        //load from default dart resource bundle.
        mNativeView = new FlutterNativeView(context);
        mFlutterView =  new FlutterView(context, null, mNativeView);
        mContext = context;
    }
    
    public FlutterView getFlutterView(){
        return mFlutterView;
    }
    
    public FlutterNativeView getFlutterNativeView(){
        return mNativeView;
    }

    public void runWithEntry(String entryName){
        String appBundlePath = FlutterMain.findAppBundlePath(mContext);
        if (appBundlePath != null) {
            boolean reuseIsolate = true;
            mFlutterView.runFromBundle(appBundlePath, null, entryName, reuseIsolate);
        }
    }

};
