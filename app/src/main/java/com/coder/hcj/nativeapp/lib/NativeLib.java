package com.coder.hcj.nativeapp.lib;

import android.util.Log;

public class NativeLib {
    static {
        System.loadLibrary("native-lib");
    }

    public NativeLib() {
    }

    public String data = "not modify";

    public int number = 2;

    /**
     * @return
     */
    public native String getNativeData();


    /**
     * 测试native访问java的属性 访问了numbers属性
     */
    public native void accessField();

    /**
     * 测试native访问java string类型的属性
     */
    public native void accessFieldString();

    /**
     * 测试java调用native方法  native方法find java class 并实例化java class 且调用其方法
     */
    public native void accessClassAndCall();

    /**
     * 测试java调用native native再调用java的方法
     * @return
     */
    public native void accessMethod();

    /**
     * 测试native调用java的静态方法
     */
    public native void accessStaticMethod();

    /**
     * 求和 测试jint转int int转jint
     *
     * @param a
     * @param b
     * @return
     */
    public native int count(int a, int b);

    /**
     * 测试string jstring的类型互转
     * @param str
     * @return
     */
    public native String stringAndjstring(String str);

    /**
     * 排序 测试数组 冒泡排序
     * @param array
     * @return
     */
    public native int [] shortAsc(int [] array);
    /**
     * 提供给native调用java的方法
     * @return
     */
    public int nativeCall() {
        Log.i("TAG", "java代码被native代码调用了");
        return 520;
    }

    public static void nativeStaticCall(){
        Log.i("TAG", "java静态方法被native代码调用了");
    }

}
