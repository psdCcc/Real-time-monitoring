package com.example.embed;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.format.DateFormat;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.reflect.Method;

public class MainActivity extends AppCompatActivity {
    TextView real_time;
    static int zoneIncre=1;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ActionBar actionBar = getSupportActionBar();
        actionBar.hide();

        real_time = findViewById(R.id.real_time);
        Startthread();

        Button button1 = (Button) findViewById(R.id.button_1);
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this,"see the sensors' data now",
                               Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(MainActivity.this,SensorData.class);
                startActivity(intent);
            }
        });
        Button button2 = (Button) findViewById(R.id.button_2);
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this,"see the image now",
                        Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(MainActivity.this,IndoorImages.class);
                startActivity(intent);

            }
        });
        Button button3 = (Button) findViewById(R.id.button_3);
        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this,"see the image now",
                        Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(MainActivity.this,LocalData.class);
                startActivity(intent);
            }
        });
        Button titleSet =(Button) findViewById(R.id.title_set);
        titleSet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this,"see the settings now",
                        Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(MainActivity.this,Settings.class);
                startActivity(intent);
            }
        });

    }
    private void Startthread(){
        new Thread(){
            @Override
            public void run() {
                do {
                    try {
                        Thread.sleep(1000);
                        Message message=new Message();
                        message.what=1;
                        handler.sendMessage(message);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }while (true);
            }
        }.start();
    }

    // deal the task in the thread
    private Handler handler=new Handler(){
        @Override
        public void handleMessage(@NonNull Message msg) {
            switch (msg.what){
                case 1:
                    long time = System.currentTimeMillis() + 3600000*(zoneIncre);
                    CharSequence format = DateFormat.format("HH:mm:ss yyyy-MM-dd", time);
                    real_time.setText(format);
                    break;
            }
        }
    };
}
