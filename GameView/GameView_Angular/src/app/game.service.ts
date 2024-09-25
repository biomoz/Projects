import { Injectable } from '@angular/core';
import { Game } from './game.model';
import { Observable } from 'rxjs';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';

@Injectable({
  providedIn: 'root'
})
export class GameService {

  private apiUrl = 'http://localhost:3000/games';
  
  constructor(private http: HttpClient) { }

  getGames(): Observable<Game[]> {
    return this.http.get<Game[]>(this.apiUrl);
  }
  
  getGame(id: number): Observable<Game> {
    const url = `${this.apiUrl}/${id}`;
    return this.http.get<Game>(url);
  }
  
  addGame(game: Game): Observable<Game> {
    return this.http.post<Game>(this.apiUrl, game);
  }
  
  deleteGame(id: number): Observable<Game> {
    const url = `${this.apiUrl}/${id}`;
    return this.http.delete<Game>(url);
  }
  
  updateGame(game: Game): Observable<Game> {
    const url = `${this.apiUrl}/${game.id}`;
    return this.http.put<Game>(url, game);
  }
  
  generateId(games : Game[]): number {
    return games.length > 0 ? Math.max(...games.map(game => game.id)) + 1 : 1;
  }
  
}
