package com.example.embed;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;

import android.view.View;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.Toast;

public class Settings extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        ActionBar actionBar = getSupportActionBar();
        actionBar.hide();
        final RadioButton rB1 = (RadioButton) findViewById(R.id.unitC);
        final RadioButton rB2 = (RadioButton) findViewById(R.id.unitF);
        Button button1 = (Button) findViewById(R.id.setting_confirm);
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(rB1.isChecked()){
                    SensorData.unit = "℃";
                    SensorData.num_temp = "26";
                }
                else if(rB2.isChecked()){
                    SensorData.unit = "℉";
                    SensorData.num_temp = "78.8";

                }

            }
        });



    }
}
