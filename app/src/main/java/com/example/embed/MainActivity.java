package com.example.embed;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.lang.reflect.Method;

public class MainActivity extends AppCompatActivity {

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main,menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        switch (item.getItemId()){
            case R.id.set:
                Toast.makeText(this,"1111",Toast.LENGTH_SHORT);
                break;
            case R.id.about:
                Toast.makeText(this,"1221",Toast.LENGTH_SHORT);
                break;
            default:
        }
        return true;
    }
    @Override
    public boolean onMenuOpened(int featureId, Menu menu)
    {
        if (menu != null) {
            if (menu.getClass().getSimpleName().equalsIgnoreCase("MenuBuilder")) {
                try {
                    Method method = menu.getClass().getDeclaredMethod("setOptionalIconsVisible", Boolean.TYPE);
                    method.setAccessible(true);
                    method.invoke(menu, true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        return super.onMenuOpened(featureId, menu);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ActionBar actionBar = getSupportActionBar();
        actionBar.hide();

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
                Intent intent = new Intent(MainActivity.this,trendOfData.class);
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
}
