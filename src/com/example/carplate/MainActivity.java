package com.example.carplate;

import java.io.File;
import java.io.UnsupportedEncodingException;
import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener
{
    final String      TAG        = "EasyPR";
    private ImageView imageView  = null;
    private TextView  m_text     = null;
    private String    path       = null;
    private String    imgDir     = null;
    private String    imgpath    = null;

    private int       currentImg = 0;

    File[]            picFiles       = null;

    static {
        if (!OpenCVLoader.initDebug()) {
        } else {
            System.loadLibrary("easypr");
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        m_text = (TextView) findViewById(R.id.myshow);
        imageView = (ImageView) findViewById(R.id.image_view);
        path = Environment.getExternalStorageDirectory().getAbsolutePath() + "/EasyPR/";
        imgDir = path + "PIC/";
        File dir = new File(imgDir);
        picFiles = dir.listFiles();
        if (picFiles != null && picFiles.length != 0) {
            imgpath = picFiles[currentImg].getAbsolutePath();
            Bitmap bit = BitmapFactory.decodeFile(imgpath);
            imageView.setImageBitmap(bit);
        }
        Button next = (Button) findViewById(R.id.next);
        next.setOnClickListener(this);
    }

    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS: {}
                break;
                default: {
                    super.onManagerConnected(status);
                }
                break;
            }
        }
    };

    public void click(View view) throws UnsupportedEncodingException {
        String svmpath = path + "/svm.xml";
        String annpath = path + "/ann.xml";
        String result = CarPlateDetection.ImageProc(imgpath, svmpath, annpath);
        if (result.isEmpty()) {
            result = "未识别到车牌";
        }
        System.out.println(result);
        m_text.setText(result);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.next) {
            currentImg = currentImg + 1;
            if (currentImg >= picFiles.length) {
                currentImg = 0;
            }
            imgpath = picFiles[currentImg].getAbsolutePath();
            Bitmap bit = BitmapFactory.decodeFile(imgpath);
            imageView.setImageBitmap(bit);
            m_text.setText("");
        }
    }
}
