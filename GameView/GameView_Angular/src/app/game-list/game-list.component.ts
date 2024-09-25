import { Component } from '@angular/core';
import { Game } from '../game.model';
import { Input } from '@angular/core';
import { FormGroup, FormControl } from '@angular/forms';

@Component({
  selector: 'app-game-list',
  templateUrl: './game-list.component.html',
  styleUrls: ['./game-list.component.css']
})
export class GameListComponent {

  @Input() games: Game[] = [];
  sGames: Game[] = [];

  searchQuery: string = '';
  sortOption: string = 'name';
  searchForm = new FormGroup({
    searchQuery: new FormControl(''),
    sortOption: new FormControl('')
  });

  constructor() { }

  ngOnInit() {
    this.sGames = this.games;
    this.sGames = this.games.sort((a, b) => { return a.title.localeCompare(b.title); });
  }

  ngOnChanges(): void {
    this.sGames = this.games;
    this.sGames = this.games.sort((a, b) => { return a.title.localeCompare(b.title); });
  }

  setDefaultImage(game: Game) {
    game.image = 'https://www.publicdomainpictures.net/pictures/280000/velka/not-found-image-15383864787lu.jpg';
  }

  searchGames() {
    if (this.searchForm.value.searchQuery !== null && this.searchForm.value.searchQuery !== undefined && this.searchForm.value.searchQuery !== '') {
      this.searchQuery = this.searchForm.value.searchQuery;
      this.sGames = this.games.filter(game => game.title.toLowerCase().includes(this.searchQuery.toLowerCase()));
    }
    else if (this.searchForm.value.sortOption !== null && this.searchForm.value.sortOption !== undefined && this.searchForm.value.sortOption !== '') {
      this.sortOption = this.searchForm.value.sortOption;
      this.sGames = this.games.sort((a, b) => {
        if (this.sortOption === 'name') {
          return a.title.localeCompare(b.title);
        } else if (this.sortOption === 'rating') {
          return b.rating - a.rating;
        } else if (this.sortOption === 'releaseDate') {
          return new Date(b.releaseDate).getTime() - new Date(a.releaseDate).getTime();
        } else {
          return 0;
        }
      });
    }   
    else {
      this.sGames = this.games;
    }
  }



}
