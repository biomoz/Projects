import { Component } from '@angular/core';
import { Game } from '../game.model';
import { GameService } from '../game.service';
import { FormGroup, FormControl } from '@angular/forms';
import { ActivatedRoute } from '@angular/router';
import { Router } from '@angular/router';

@Component({
  selector: 'app-edit-game',
  templateUrl: './edit-game.component.html',
  styleUrls: ['./edit-game.component.css']
})
export class EditGameComponent {
  game: Game = { title: '', genre: '', releaseDate: '', description: '', image: '', rating: 0, id: 0};
  id = 0;
  
  gameForm = new FormGroup({
    title: new FormControl(''),
    image: new FormControl(''),
    rating: new FormControl(''),
    genre: new FormControl(''),
    releaseDate: new FormControl(''),
    description: new FormControl('')
  });

  constructor(private route: ActivatedRoute , private gameService: GameService, private router: Router) { }
    
  ngOnInit() {
    this.id = +this.route.snapshot.paramMap.get('id')!;
    this.gameService.getGame(this.id).subscribe(game => {
      this.game = game;
      this.gameForm.setValue({
        title: this.game.title,
        image: this.game.image,
        rating: this.game.rating.toString(),
        genre: this.game.genre,
        releaseDate: this.game.releaseDate,
        description: this.game.description
    });
    });
  }

  ngOnChanges() {
    this.gameForm.setValue({
      title: this.game.title,
      image: this.game.image,
      rating: this.game.rating.toString(),
      genre: this.game.genre,
      releaseDate: this.game.releaseDate,
      description: this.game.description
    });
  }

  updateGame(): void {
    console.log(this.game);
    this.gameService.updateGame(this.game).subscribe();
  }

  onSubmit(): void {
    console.log(this.gameForm.value);
    console.log(this.gameForm.valid);
    if (this.gameForm.value.title !== null && this.gameForm.value.title !== undefined && this.gameForm.value.title !== '' 
    && this.gameForm.value.genre !== null && this.gameForm.value.genre !== undefined && this.gameForm.value.genre !== '' 
    && this.gameForm.value.releaseDate !== null && this.gameForm.value.releaseDate !== undefined && this.gameForm.value.releaseDate !== '' 
    && this.gameForm.value.description !== null && this.gameForm.value.description !== undefined && this.gameForm.value.description !== '' 
    && this.gameForm.value.image !== null && this.gameForm.value.image !== undefined && this.gameForm.value.image !== '' 
    && this.gameForm.value.rating !== null && this.gameForm.value.rating !== undefined && this.gameForm.value.rating !== '') {
      this.game.title = this.gameForm.value.title;
      this.game.genre = this.gameForm.value.genre;
      this.game.releaseDate = this.gameForm.value.releaseDate;
      this.game.description = this.gameForm.value.description;
      this.game.image = this.gameForm.value.image;
      this.game.rating =+ this.gameForm.value.rating;
      this.game.id = this.id;
      this.updateGame();
      this.gameForm.reset();
      this.router.navigate(['/games/' + this.game.id]);
    }else {
      alert('Form is not valid');
    }
  }
  
}
