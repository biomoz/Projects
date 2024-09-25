package com.example.gameview;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class CustomAdapter extends RecyclerView.Adapter<CustomAdapter.MyViewHolder> {

    private Context context;
    private Activity activity;
    private ArrayList game_id;
    private ArrayList game_title;
    private ArrayList game_dt;
    private ArrayList game_rd;
    private ArrayList game_score;
    private ArrayList game_genre;

    int position;

    public CustomAdapter(Activity activity, Context context, ArrayList game_id, ArrayList game_title, ArrayList game_genre,
                         ArrayList game_score, ArrayList game_rd, ArrayList game_dt) {
        this.activity = activity;
        this.context = context;
        this.game_id = game_id;
        this.game_title = game_title;
        this.game_genre = game_genre;
        this.game_score = game_score;
        this.game_rd = game_rd;
        this.game_dt = game_dt;
    }

    @NonNull
    @Override
    public MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(context);
        View view = inflater.inflate(R.layout.game, parent, false);
        return new MyViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull MyViewHolder holder, int position) {
        this.position = position;
        holder.game_id_txt.setText(String.valueOf(game_id.get(position)));
        holder.game_title_txt.setText(String.valueOf(game_title.get(position)));
        holder.game_genre_txt.setText(String.valueOf(game_genre.get(position)));
        holder.game_score_txt.setText(String.valueOf(game_score.get(position)));
        holder.game_rd_txt.setText(String.valueOf(game_rd.get(position)));

        holder.mainLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(context, UpdateActivity.class);
                intent.putExtra("id", String.valueOf(game_id.get(position)));
                intent.putExtra("title", String.valueOf(game_title.get(position)));
                intent.putExtra("genre", String.valueOf(game_genre.get(position)));
                intent.putExtra("score", String.valueOf(game_score.get(position)));
                intent.putExtra("rd", String.valueOf(game_rd.get(position)));
                intent.putExtra("dt", String.valueOf(game_dt.get(position)));
                activity.startActivityForResult(intent, 1);
            }
        });
        String gameTitle = holder.game_title_txt.getText().toString().replaceAll("[^a-zA-Z0-9]", "_").toLowerCase();
        int drawableResId = context.getResources().getIdentifier(gameTitle, "drawable", context.getPackageName());
        if (drawableResId != 0) {
            //If there's a problem concerning the line below, wiping the data of the virtual machine might solve the problem.
            holder.game_cover.setImageResource(drawableResId);
        } else{
            holder.game_cover.setImageResource(R.drawable.default_cover);
        }
    }

    @Override
    public int getItemCount() {
        return game_id.size();
    }

    class MyViewHolder extends RecyclerView.ViewHolder {

        ImageView game_cover;
        TextView game_id_txt, game_title_txt, game_genre_txt, game_score_txt, game_rd_txt;
        LinearLayout mainLayout;

        MyViewHolder(@NonNull View itemView) {
            super(itemView);
            game_cover = itemView.findViewById(R.id.game_cover);
            game_id_txt = itemView.findViewById(R.id.game_id_txt);
            game_title_txt= itemView.findViewById(R.id.game_title_txt);
            game_genre_txt= itemView.findViewById(R.id.game_genre_txt);
            game_score_txt= itemView.findViewById(R.id.game_score_txt);
            game_rd_txt= itemView.findViewById(R.id.game_rd_txt);
            mainLayout = itemView.findViewById(R.id.mainLayout);

        }

    }
}
