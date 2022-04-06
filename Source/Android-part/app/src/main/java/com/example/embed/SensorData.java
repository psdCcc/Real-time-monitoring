package com.example.embed;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class SensorData extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sensor_data);
        ActionBar actionBar = getSupportActionBar();
        actionBar.hide();

        TextView time = findViewById(R.id.time);
        SimpleDateFormat formatter = new SimpleDateFormat("YY-MM-dd HH:mm:ss");
        Date date = new Date(System.currentTimeMillis());
        time.setText(formatter.format(date));

        Button button3 = (Button) findViewById(R.id.button_refresh);
        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TextView time = findViewById(R.id.time);
                SimpleDateFormat formatter = new SimpleDateFormat("YY-MM-dd HH:mm:ss");
                Date date = new Date(System.currentTimeMillis());
                time.setText(formatter.format(date));

            }
        });
        Button buttons = (Button) findViewById(R.id.button_S);
        buttons.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });

    }
}
