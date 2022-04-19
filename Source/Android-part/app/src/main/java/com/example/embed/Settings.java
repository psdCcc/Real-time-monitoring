package com.example.embed;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;

import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.Toast;


import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
public class Settings extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        ActionBar actionBar = getSupportActionBar();
        actionBar.hide();



        Button confirm = (Button) findViewById(R.id.setting_confirm);
        confirm.setOnClickListener(new View.OnClickListener() {


            @Override
            public void onClick(View v) {
                    EditText timeZone = (EditText) findViewById(R.id.zone);
                    String zoneStr = timeZone.getText().toString();
                    if(Integer.parseInt(zoneStr)<15 & Integer.parseInt(zoneStr)>-13){
                        final int scale = Integer.parseInt(zoneStr);
                        MainActivity.zoneIncre = scale;
                    }else{
                        Toast.makeText(Settings.this,"invalid input!",
                                Toast.LENGTH_SHORT).show();
                    }

                }

        });

    }
}


