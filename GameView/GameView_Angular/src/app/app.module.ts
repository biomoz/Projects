import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HeaderComponent } from './header/header.component';
import { HomeComponent } from './home/home.component';
import { GamesComponent } from './games/games.component';
import { AddGameComponent } from './add-game/add-game.component';
import { GameComponent } from './game/game.component';
import { EditGameComponent } from './edit-game/edit-game.component';
import { GameListComponent } from './game-list/game-list.component';
import { ReactiveFormsModule } from '@angular/forms';
import { TitleCasePipe } from './title-case.pipe';
import { HttpClientModule } from '@angular/common/http';

@NgModule({
  declarations: [
    AppComponent,
    HeaderComponent,
    HomeComponent,
    GamesComponent,
    AddGameComponent,
    GameComponent,
    EditGameComponent,
    GameListComponent,
    TitleCasePipe,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    ReactiveFormsModule,
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
