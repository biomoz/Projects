import { Component } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Game } from '../game.model';
import { GameListComponent } from '../game-list/game-list.component';
import { GameService } from '../game.service';
import { OnInit } from '@angular/core';

@Component({
  selector: 'app-games',
  templateUrl: './games.component.html',
  styleUrls: ['./games.component.css']
})
export class GamesComponent {

  games: Game[] = [];

  constructor(private gameService: GameService) { }

  ngOnInit() {
    this.getGames();
  }

  getGames(): void {
    this.gameService.getGames().subscribe(games => this.games = games);
  }

  search: string = '';


}
