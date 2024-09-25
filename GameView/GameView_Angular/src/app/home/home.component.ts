import { Component } from '@angular/core';
import { Game } from '../game.model';
import { GameService } from '../game.service';
import { map } from 'rxjs/operators';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent {

games: Game[] = [];
rGames: Game[] = [];

constructor(private gameService: GameService) { }

ngOnInit(): void {
  this.gameService.getGames().subscribe(games => this.games = games);
  this.gameService.getGames().pipe(
    map(games => games.sort((a, b) => b.rating - a.rating)),
    map(games => games.slice(0, 3))
  ).subscribe(games => this.rGames = games);
}

setDefaultImage(game: Game) {
  game.image = 'https://www.publicdomainpictures.net/pictures/280000/velka/not-found-image-15383864787lu.jpg';
}

}
