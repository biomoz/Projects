package com.example.gameview;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.graphics.Color;
import android.os.Bundle;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;

import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.Locale;

public class UpdateActivity extends AppCompatActivity implements SharedPreferences.OnSharedPreferenceChangeListener {

    EditText title_input, genre_input, score_input, date_input, details_input;
    Button update_button, delete_button;

    String id, title, genre, date, details, score;

    String appColorS;

    int appColor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_update);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        title_input = findViewById(R.id.game_title);
        genre_input = findViewById(R.id.game_genre);
        score_input = findViewById(R.id.game_score);
        date_input = findViewById(R.id.game_rd);
        details_input = findViewById(R.id.game_details);
        update_button = findViewById(R.id.update_button);
        delete_button = findViewById(R.id.delete_button);
        //First we call this
        getAndSetIntentData();

        ActionBar ab = getSupportActionBar();
        if (ab != null) {
            ab.setTitle(title);
        }

        update_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //And only then we call this
                DatabaseHelper myDB = new DatabaseHelper(UpdateActivity.this);
                title = title_input.getText().toString().trim();
                genre = genre_input.getText().toString().trim();
                score = score_input.getText().toString().trim();
                date = date_input.getText().toString().trim();
                details = details_input.getText().toString().trim();
                myDB.updateData(id, title, genre, Integer.parseInt(score), date, details);
            }
        });
        delete_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                confirmDialog();
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

    void getAndSetIntentData(){
        if(getIntent().hasExtra("id") && getIntent().hasExtra("title") &&
                getIntent().hasExtra("genre") && getIntent().hasExtra("score") && getIntent().hasExtra("rd")
                && getIntent().hasExtra("dt")){
            //Getting Data from Intent

            id = getIntent().getStringExtra("id");
            title = getIntent().getStringExtra("title");
            genre = getIntent().getStringExtra("genre");
            score = getIntent().getStringExtra("score");
            date = getIntent().getStringExtra("rd");
            details = getIntent().getStringExtra("dt");

            //Setting Intent Data
            title_input.setText(title);
            genre_input.setText(genre);
            score_input.setText(score);
            date_input.setText(date);
            details_input.setText(details);

            Log.d("Game", title+" "+genre+" "+score+" "+date+" "+details);
        }else{
            Toast.makeText(this, "No data.", Toast.LENGTH_SHORT).show();
        }
    }

    void confirmDialog(){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Delete " + title + " ?");
        builder.setMessage("Are you sure you want to delete " + title + " ?");
        builder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                DatabaseHelper myDB = new DatabaseHelper(UpdateActivity.this);
                myDB.deleteOneRow(id);
                finish();
            }
        });
        builder.setNegativeButton("No", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {

            }
        });
        builder.create().show();
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
