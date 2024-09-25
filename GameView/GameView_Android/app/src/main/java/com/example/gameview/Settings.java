package com.example.gameview;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceFragmentCompat;
import androidx.preference.PreferenceManager;

import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.graphics.Color;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

import java.util.Locale;

public class Settings extends AppCompatActivity implements SharedPreferences.OnSharedPreferenceChangeListener {

    String appColorS;

    int appColor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }
        String settings_title = getString(R.string.settings_title);
        setTitle(settings_title);

        // Add the preference fragment to the activity
        getSupportFragmentManager()
                .beginTransaction()
                .replace(android.R.id.content, new MyPreferenceFragment())
                .commit();

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
    public void onPointerCaptureChanged(boolean hasCapture) {
        super.onPointerCaptureChanged(hasCapture);
    }

    public static class MyPreferenceFragment extends PreferenceFragmentCompat {

        @Override
        public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
            // Load the preferences from an XML resource
            setPreferencesFromResource(R.xml.preferences, rootKey);
        }
    }

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
}