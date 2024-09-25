import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { GamesComponent } from './games/games.component';
import { AddGameComponent } from './add-game/add-game.component';
import { GameComponent } from './game/game.component';
import { EditGameComponent } from './edit-game/edit-game.component';

const routes: Routes = [ 
  { path: '', redirectTo: '/home', pathMatch: 'full' },
  { path: 'home', component: HomeComponent }, 
  { path: 'games', component: GamesComponent }, 
  { path: 'add-game', component: AddGameComponent }, 
  { path: 'games/:id', component: GameComponent }, 
  { path: 'games/:id/edit', component: EditGameComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
