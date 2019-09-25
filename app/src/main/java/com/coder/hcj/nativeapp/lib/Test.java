package com.coder.hcj.nativeapp.lib;

public class Test {
    static {
        System.loadLibrary("testSecond");
    }

    public native static String getStringData();
}
