import { Component } from '@angular/core';
import { Game } from '../game.model';
import { GameService } from '../game.service';
import { FormGroup, FormControl } from '@angular/forms';
import { Router } from '@angular/router';

@Component({
  selector: 'app-add-game',
  templateUrl: './add-game.component.html',
  styleUrls: ['./add-game.component.css']
})
export class AddGameComponent {

  game: Game = { title: '', genre: '', releaseDate: '', description: '', image: '', rating: 0, id: 0};
  games: Game[] = [];

  gameForm = new FormGroup({
    title: new FormControl(''),
    image: new FormControl(''),
    rating: new FormControl(''),
    genre: new FormControl(''),
    releaseDate: new FormControl(''),
    description: new FormControl('')
  });

  constructor(private gameService: GameService, private router: Router) { }

  ngOnInit() {
    this.getGames();
  }

  addGame(): void {
    console.log(this.game);
    this.gameService.addGame(this.game).subscribe();
  }

  onSubmit(): void {
    console.log(this.gameForm.value);
    console.log(this.gameForm.valid);
    if (this.gameForm.value.title !== null && this.gameForm.value.title !== undefined && this.gameForm.value.title !== '' 
    && this.gameForm.value.genre !== null && this.gameForm.value.genre !== undefined && this.gameForm.value.genre !== '' 
    && this.gameForm.value.releaseDate !== null && this.gameForm.value.releaseDate !== undefined && this.gameForm.value.releaseDate !== '' 
    && this.gameForm.value.description !== null && this.gameForm.value.description !== undefined && this.gameForm.value.description !== '' 
    && this.gameForm.value.image !== null && this.gameForm.value.image !== undefined && this.gameForm.value.image !== '' 
    && this.gameForm.value.rating !== null && this.gameForm.value.rating !== undefined && this.gameForm.value.rating !== '' && !isNaN(Number(this.gameForm.value.rating))) {
      this.game.title = this.gameForm.value.title;
      this.game.genre = this.gameForm.value.genre;
      this.game.releaseDate = this.gameForm.value.releaseDate;
      this.game.description = this.gameForm.value.description;
      this.game.image = this.gameForm.value.image;
      this.game.rating =+ this.gameForm.value.rating;
      this.game.id = this.generateId(this.games);
      this.addGame();
      this.gameForm.reset();
      this.router.navigate(['/games']);
    }else {
      alert('Form is not valid');
    }
  }

  generateId(games: Game[]): number {
    let id = 0;
    for (let i = 0; i < games.length; i++) {
      if (games[i].id > id) {
        id = games[i].id;
      }
    }
    return id + 1;
  }
  
  getGames(): void {
    this.gameService.getGames().subscribe(games => this.games = games);
  }

}
