package com.coder.hcj.nativeapp.lib;

import android.util.Log;

public class DemoClass {
    String data = "empty data";

    public DemoClass() {
        Log.i("TAG", "DemoClass被实例化了");
    }

    public DemoClass(String data) {
        Log.i("TAG", "DemoClass被实例化了");
        this.data = data;
    }

    public void callDemo() {
        Log.i("TAG", "DemoClass#callDemo 被调用 data=" + this.data);
    }

}
