package com.example.gameview;

import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.ArrayList;
import java.util.Locale;

public class MainActivity extends AppCompatActivity implements SharedPreferences.OnSharedPreferenceChangeListener {

    TextView username_text;
    FloatingActionButton add_button;
    Button games_button;
    String username;

    String appColorS;

    int appColor;
    static int count=0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        add_button = findViewById(R.id.add_button);
        games_button = findViewById(R.id.games_button);
        username_text = findViewById(R.id.app_title_text);
        add_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, AddActivity.class);
                startActivity(intent);
            }
        });
        games_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, Games.class);
                startActivity(intent);
            }
        });
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        appColorS = sharedPreferences.getString("app_color_pref", "#FFFFFFFF");
        try {
            appColor = Color.parseColor(appColorS);
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
            appColor = Color.WHITE;
        }

        View rootView = findViewById(android.R.id.content);
        rootView.setBackgroundColor(appColor);
        username = sharedPreferences.getString("username", "Username");
        username_text.setText(username);
        String languageValue = sharedPreferences.getString("language_preference", "en");
        Locale locale = new Locale(languageValue);
        Locale.setDefault(locale);
        Configuration config = new Configuration();
        config.setLocale(locale);
        getResources().updateConfiguration(config, getBaseContext().getResources().getDisplayMetrics());
        if(count==0){
            recreate();
            count++;
        }
        // Register a listener for preference changes
        sharedPreferences.registerOnSharedPreferenceChangeListener(this);
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
        // Check if the changed preference is the username preference
        if (key.equals("username")) {
            // Update the username value
            username = sharedPreferences.getString("username", "Username");

            // Set the username to the updated value
            TextView usernameTextView = findViewById(R.id.app_title_text);
            usernameTextView.setText(username);
        }
        if (key.equals("app_color_pref")) {
            // Load the new app color preference value
            String appColorString = sharedPreferences.getString("app_color_pref", "#FFFFFFFF");

            // Convert the new app color string to an int value
            appColor = Color.parseColor(appColorString);

            View rootView = findViewById(android.R.id.content);
            rootView.setBackgroundColor(appColor);
        }
        if (key.equals("language_preference")) {
            String languageValue = sharedPreferences.getString(key, "en");
            Locale locale = new Locale(languageValue);
            Configuration config = new Configuration();
            config.setLocale(locale);
            getResources().updateConfiguration(config, getBaseContext().getResources().getDisplayMetrics());

            recreate();
        }
        if (key.equals("language_preference")) {
            String languageValue = sharedPreferences.getString(key, "en");
            Locale locale = new Locale(languageValue);
            Configuration config = new Configuration();
            config.setLocale(locale);
            getResources().updateConfiguration(config, getBaseContext().getResources().getDisplayMetrics());

            recreate();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        // Unregister the preference change listener
        PreferenceManager.getDefaultSharedPreferences(this).unregisterOnSharedPreferenceChangeListener(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            Intent intent = new Intent(MainActivity.this, Settings.class);
            startActivity(intent);
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onPointerCaptureChanged(boolean hasCapture) {
        super.onPointerCaptureChanged(hasCapture);
    }
}