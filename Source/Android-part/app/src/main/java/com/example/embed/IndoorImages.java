package com.example.embed;


import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.MediaController;
import android.widget.RadioButton;
import android.widget.VideoView;

public class IndoorImages extends Activity {
    /** Called when the activity is first created. */

    Button playButton ;
    VideoView videoView ;
    EditText rtspUrl ;
    RadioButton radioStream;
    RadioButton radioFile;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_indoor_images);

        rtspUrl = (EditText)this.findViewById(R.id.url);
        playButton = (Button)this.findViewById(R.id.start_play);

        playButton.setOnClickListener(new Button.OnClickListener(){
            public void onClick(View v) {

                    PlayStream(rtspUrl.getEditableText().toString());


            }
        });

        videoView = (VideoView)this.findViewById(R.id.rtsp_player);

    }

    //play  stream
    private void PlayStream(String Url){
        videoView.setVideoURI(Uri.parse(Url));
        videoView.requestFocus();
        videoView.start();
    }



}