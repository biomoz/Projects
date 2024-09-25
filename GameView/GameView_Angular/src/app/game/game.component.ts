import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Game } from '../game.model';
import { GameService } from '../game.service';

@Component({
  selector: 'app-game',
  templateUrl: './game.component.html',
  styleUrls: ['./game.component.css']
})
export class GameComponent {

  game: Game = { title: '', genre: '', releaseDate: '', description: '', image: '', rating: 0, id: 0};
  id = 0;

  constructor(private route: ActivatedRoute , private gameService: GameService) { }
    
  ngOnInit() {
    this.id = +this.route.snapshot.paramMap.get('id')!;
    this.gameService.getGame(this.id).subscribe(game => this.game = game);
  }

  deleteGame(id: number): void {
    this.gameService.deleteGame(id).subscribe();
    window.location.href = '/games';
  }

  setDefaultImage(game: Game) {
    game.image = 'https://www.publicdomainpictures.net/pictures/280000/velka/not-found-image-15383864787lu.jpg';
  }

}
