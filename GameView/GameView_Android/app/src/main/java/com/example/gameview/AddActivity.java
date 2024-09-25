package com.example.gameview;

import android.annotation.SuppressLint;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;

import java.util.Locale;

public class AddActivity extends AppCompatActivity implements SharedPreferences.OnSharedPreferenceChangeListener {

    EditText title_input, genre_input, score_input, date_input, details_input;
    Button add_button;

    String appColorS;

    int appColor;

    @SuppressLint("WrongViewCast")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }
        String add_game = getString(R.string.add_game);
        setTitle(add_game);

        title_input = findViewById(R.id.game_title);
        genre_input = findViewById(R.id.game_genre);
        date_input = findViewById(R.id.game_rd);
        score_input = findViewById(R.id.game_score);
        details_input = findViewById(R.id.game_details);
        add_button = findViewById(R.id.add_button);
        add_button.setOnClickListener(view -> {
            DatabaseHelper myDB = new DatabaseHelper(AddActivity.this);
            myDB.addGame(title_input.getText().toString().trim(),
                    genre_input.getText().toString().trim(),
                    Integer.parseInt(score_input.getText().toString().trim()),
                    date_input.getText().toString().trim(),
                    details_input.getText().toString().trim()
            );
            Log.d("Game", title_input.getText()+" "+genre_input.getText()+" "+score_input.getText()+" "+date_input.getText()+" "+details_input.getText());
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

        // Register a listener for preference changes
        sharedPreferences.registerOnSharedPreferenceChangeListener(this);
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
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
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                onBackPressed();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onPointerCaptureChanged(boolean hasCapture) {
        super.onPointerCaptureChanged(hasCapture);
    }
}
