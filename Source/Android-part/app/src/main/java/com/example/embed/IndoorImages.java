package com.example.embed;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.MediaController;
import android.widget.VideoView;

public class IndoorImages extends AppCompatActivity {

    VideoView videoView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_indoor_images);
        ActionBar actionBar = getSupportActionBar();
        actionBar.hide();
        videoView =(VideoView)this.findViewById(R.id.stream_player);
        videoView.setVideoURI(Uri.parse("http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4"));
        android.widget.MediaController mediaController = new MediaController(this);
        videoView.setMediaController(mediaController);
        videoView.start();
        Button buttoni = (Button) findViewById(R.id.button_I);
        buttoni.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });


    }
}
