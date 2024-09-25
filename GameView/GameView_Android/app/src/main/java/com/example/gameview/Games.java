package com.example.gameview;

import androidx.annotation.Nullable;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.database.Cursor;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Locale;

public class Games extends AppCompatActivity implements SharedPreferences.OnSharedPreferenceChangeListener {

    private RecyclerView rv_games;

    ImageView empty_imageview;
    TextView no_data;

    CustomAdapter customAdapter;

    ArrayList<String> game_title,game_dt, game_rd, game_score, game_genre, game_id;

    DatabaseHelper DB;

    String appColorS;

    int appColor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_games);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }
        String games = getString(R.string.games);
        setTitle(games);

        empty_imageview = findViewById(R.id.empty_imageview);
        no_data = findViewById(R.id.no_data);
        rv_games = findViewById(R.id.rv_games);
        DB = new DatabaseHelper(Games.this);
        game_id = new ArrayList<>();
        game_title = new ArrayList<>();
        game_genre = new ArrayList<>();
        game_score = new ArrayList<>();
        game_rd = new ArrayList<>();
        game_dt = new ArrayList<>();

        storeDataInArrays();

        customAdapter = new CustomAdapter(Games.this,this, game_id, game_title, game_genre, game_score, game_rd, game_dt);
        rv_games.setAdapter(customAdapter);
        rv_games.setLayoutManager(new LinearLayoutManager(Games.this));

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
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode == 1){
            recreate();
        }
    }

    void storeDataInArrays(){
        Cursor cursor = DB.readAllData();
        if(cursor.getCount() == 0){
            empty_imageview.setVisibility(View.VISIBLE);
            no_data.setVisibility(View.VISIBLE);
        }else{
            while (cursor.moveToNext()){
                game_id.add(cursor.getString(cursor.getColumnIndex("_id")));
                game_title.add(cursor.getString(cursor.getColumnIndex("game_title")));
                game_genre.add(cursor.getString(cursor.getColumnIndex("game_genre")));
                game_score.add(cursor.getString(cursor.getColumnIndex("game_score")));
                game_rd.add(cursor.getString(cursor.getColumnIndex("game_rd")));
                game_dt.add(cursor.getString(cursor.getColumnIndex("game_details")));
            }
            empty_imageview.setVisibility(View.GONE);
            no_data.setVisibility(View.GONE);
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