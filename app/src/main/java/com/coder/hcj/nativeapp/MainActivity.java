package com.coder.hcj.nativeapp;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import com.coder.hcj.nativeapp.lib.NativeLib;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private NativeLib lib;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        lib = new NativeLib();

        findViewById(R.id.button1).setOnClickListener(this);
        findViewById(R.id.button2).setOnClickListener(this);
        findViewById(R.id.button3).setOnClickListener(this);
        findViewById(R.id.button4).setOnClickListener(this);
        findViewById(R.id.button5).setOnClickListener(this);
        findViewById(R.id.button6).setOnClickListener(this);
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.button1://调用jni获取数据
                String data = lib.getNativeData();
                Log.i("TAG", data);
                break;
            case R.id.button2://访问java的int filed
                Log.i("TAG", "修改前=" + lib.number);
                lib.accessField();
                Log.i("TAG", "修改后=" + lib.number);
                break;
            case R.id.button3://访问java的String filed
                Log.i("TAG", "修改前=" + lib.data);
                lib.accessFieldString();
                Log.i("TAG", "修改后=" + lib.data);
                break;
            case R.id.button4://访问java的method
                lib.accessMethod();
                break;
            case R.id.button5://c++实例化java的对象，并调用其方法
                lib.accessClassAndCall();
                break;
            case R.id.button6://jni数组的使用 排序
                int arr[] = new int[]{1, 9, 5, 98, 6, 3, 2, 55};
                for (int i : arr) {
                    Log.i("TAG", "排序前:" + i);
                }
                int[] ints = lib.shortAsc(arr);
                for (int i : arr) {
                    Log.i("TAG", "------------:" + i);
                }
                for (int i : ints) {
                    Log.i("TAG", "排序后:" + i);
                }
                break;

        }
    }
}
