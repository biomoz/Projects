import pygame
import random
import math
from pygame import mixer

# I learned how to use pygame and the game logic from tutorials on youtube and websites like geeksforgeeks.org, stackoverflow.com and pygame.org

# Initialize the pygame
pygame.init()
clock = pygame.time.Clock()
screen = pygame.display.set_mode((800, 600))

# Background
background = pygame.image.load('./img/background.png') 

# Background Sound
mixer.music.load('./music/background.mp3') 
mixer.music.play(-1)

# Title and Icon
pygame.display.set_caption("S-Py-ace Invaders")
icon = pygame.image.load('./img/spaceship.png')  
pygame.display.set_icon(icon)

# Player
playerImg = pygame.image.load('./img/spaceship.png')
playerX = 370
playerY = 480
playerX_change = 0
player_hp = 3
player_dead = False

# Enemy
enemyImg = []
enemyX = []
enemyY = []
enemyX_change = []
enemyY_change = []
num_of_enemies = 5

for i in range(num_of_enemies):
    enemyImg.append(pygame.image.load('./img/enemy.png')) 
    enemyX.append(random.randint(0, 735))
    enemyY.append(random.randint(50, 150))  
    enemyX_change.append(4)
    enemyY_change.append(40)

# Boss
bossImg = pygame.image.load('./img/boss.png')
bossX = 0
bossY = 0
bossX_change = 0
boss_stage = False
boss_dead = False
boss_hp = 5

# Bullet
# Ready - You can't see the bullet on the screen
# Fire - The bullet is currently moving
bulletImg = pygame.image.load('./img/bullet.png')
bulletX = 0 
bulletY = 480  
bulletX_change = 0
bulletY_change = 10
bullet_state = "ready"

# Boss Bullet
boss_bulletImg = pygame.image.load('./img/boss_bullet.png')
boss_bulletX = 0
boss_bulletY = 0
boss_bulletX_change = 0
boss_bulletY_change = 10
boss_bullet_state = "ready"

# Score
score_value = 0
font = pygame.font.Font('freesansbold.ttf', 32)
textX = 10
textY = 10

# Extra Text
over_font = pygame.font.Font('freesansbold.ttf', 64)
controls_font = pygame.font.Font('freesansbold.ttf', 16)

def show_timer():
    timer_text = font.render("Time: " + str(elapsed_time), True, (255, 255, 255))
    screen.blit(timer_text, (300,250))

def game_over_text():
    global game_state
    over_text = over_font.render("GAME OVER", True, (255, 255, 255))
    screen.blit(over_text, (200, 250))
    font = pygame.font.Font(None, 32)
    enter_text = font.render("Press Enter to continue", True, (255, 255, 255))
    enter_box = pygame.draw.rect(screen, (255, 0, 0), (270, 350, 270, 40))
    screen.blit(enter_text, (280, 360))
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RETURN:
                    game_state = "menu"
                    return
        pygame.display.flip()
        clock.tick(60)

def win_text():
    global name
    global game_state
    name = "bot"
    show_timer()
    while True:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RETURN:
                    game_state = "menu"
                    return name
                elif event.key == pygame.K_BACKSPACE:
                    name = name[:-1]
                    #update screen after backspace
                    screen.fill((0, 0, 0))
                    # Background Image
                    screen.blit(background, (0, 0))
                    show_timer()
                else:
                    if len(name) < 12:
                        name += event.unicode
            elif event.type == pygame.QUIT:
                pygame.quit()
                exit()
        font = pygame.font.Font(None, 32)        
        win_text = over_font.render("YOU WIN !", True, (255, 255, 255))
        screen.blit(win_text, (230, 150))
        text = font.render("Enter your name: ", True, (255, 255, 255))
        name_text = font.render(name, True, (0, 0, 0))
        text_box = pygame.draw.rect(screen, (255, 255, 255), (340, 330, 195, 20))
        screen.blit(name_text, (345, 330))
        screen.blit(text, (150, 330))
        enter_text = font.render("Press Enter to continue", True, (255, 255, 255))
        enter_box = pygame.draw.rect(screen, (255, 0, 0), (270, 400, 270, 40))
        screen.blit(enter_text, (280, 410))
        pygame.display.flip()
        clock.tick(60)

def player(x, y):
    screen.blit(playerImg, (x, y))
    pygame.draw.rect(screen, (255, 0, 0), (x+17 , y + 60, 30, 10))
    pygame.draw.rect(screen, (0, 255, 0), (x+17 , y + 60 , 30 - (10 * (3 - player_hp)), 10))

def enemy(x, y, i):
    screen.blit(enemyImg[i], (x, y)) 

def boss(x, y):
    screen.blit(bossImg, (x, y)) 
    pygame.draw.rect(screen, (255, 0, 0), (x +150, y+70 , 100, 10))
    pygame.draw.rect(screen, (0, 255, 0), (x +150, y+70 , 100 - (20 * (5 - boss_hp)), 10))

def fire_bullet(x, y):
    global bullet_state
    bullet_state = "fire" 
    screen.blit(bulletImg, (x , y + 10))  

def fire_boss_bullet(x, y):
    global boss_bullet_state
    boss_bullet_state = "fire"
    screen.blit(boss_bulletImg, (x + 80, y + 250))
    screen.blit(boss_bulletImg, (x + 270, y + 250))

def isCollision(enemyX, enemyY, bulletX, bulletY):
    distance = math.sqrt((math.pow(enemyX - bulletX - 8, 2)) + (math.pow(enemyY - bulletY - 8, 2)))
    
    if distance < 24:
        return True
    else:
        return False

def isCollisionBoss(bossX, bossY, bulletX, bulletY):
    distance = math.sqrt((math.pow(bossX + 200 - bulletX - 16 - 8 , 2)) + (math.pow(bossY + 200 - bulletY - 16 - 8, 2))) 
    
    if distance < 116:
        return True
    else:
        return False

def reset_game():
    global playerX, playerY, playerX_change, player_hp, player_dead, enemyX, enemyY, enemyX_change, enemyY_change, bossX, bossY, bossX_change, boss_stage, boss_dead, boss_hp, bulletX, bulletY, bulletX_change, bulletY_change, bullet_state, boss_bulletX, boss_bulletY, boss_bulletX_change, boss_bulletY_change, boss_bullet_state, score_value, num_of_enemies
    global timer, elapsed_time
    playerX = 370
    playerY = 480
    playerX_change = 0
    player_hp = 3
    player_dead = False
    enemyX = []
    enemyY = []
    enemyX_change = []
    enemyY_change = []
    num_of_enemies = 5
    for i in range(num_of_enemies):
        enemyX.append(random.randint(0, 735))
        enemyY.append(random.randint(50, 150)) 
        enemyX_change.append(4)
        enemyY_change.append(40)
    bossX = 0
    bossY = 0
    bossX_change = 0
    boss_stage = False
    boss_dead = False
    boss_hp = 5
    bulletX = 0 
    bulletY = 480  
    bulletX_change = 0
    bulletY_change = 10
    bullet_state = "ready"
    boss_bulletX = 0
    boss_bulletY = 0
    boss_bulletX_change = 0
    boss_bulletY_change = 10
    boss_bullet_state = "ready"
    score_value = 0
    num_of_enemies = 5
    timer = False
    elapsed_time = 0

def leaderboard():
    with open('leaderboard.txt', 'r') as f:
        lines = f.readlines()
        lines = [line.strip() for line in lines]
        lines = [line.split(",") for line in lines]
        #sort by time using lambda function that I learned from blogboard.io in pytho sorted lambda page
        lines = sorted(lines, key=lambda x: float(x[1]))
        lines = lines[:5]
        lines = [" ".join(line) for line in lines]
        text = ":".join(lines)
        return text
    
def write_leaderboard(name, elapsed_time):
    with open('leaderboard.txt', 'a') as f:
        f.write(name + "," + str(elapsed_time) + "\n")
        f.close()

# Game Loop
running = True
elapsed_time = 0
timer = False
game_state = "menu"

while running:
    if game_state == "menu":
        screen.fill((0, 0, 0))
        # Background Image
        screen.blit(background, (0, 0))

        title_text = over_font.render("S-Py-ace Invaders", True, (255, 255, 0))
        screen.blit(title_text, (120, 100))
        controls_text = controls_font.render("Controls: Left/Right Arrow Keys to move, Space to shoot", True, (255, 255, 255))
        screen.blit(controls_text, (180, 250))
        start_button = pygame.draw.rect(screen, (255, 0, 0), (350, 330, 125, 50))
        start_text = font.render("START", True, (255, 255, 255))
        ranking_button = pygame.draw.rect(screen, (255, 0, 0), (325, 400, 175, 50))
        ranking_text = font.render("RANKING", True, (255, 255, 255))
        exit_button = pygame.draw.rect(screen, (255, 0, 0), (365, 470, 100, 50))
        exit_text = font.render("EXIT", True, (255, 255, 255))
        sound_button = pygame.draw.rect(screen, (255, 0, 0), (10, 10, 50, 50))
        if mixer.music.get_busy():
            sound_icon = pygame.image.load('./img/sound_on.png')
        else:
            sound_icon = pygame.image.load('./img/sound_off.png')
        screen.blit(sound_icon, (0, 5))
        screen.blit(start_text, (360, 340))
        screen.blit(ranking_text, (335, 410))
        screen.blit(exit_text, (375, 480))
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if pygame.mouse.get_pressed()[0]:
                if start_button.collidepoint(pygame.mouse.get_pos()):
                    game_state = "game"
                    reset_game()
                    timer = True
                if ranking_button.collidepoint(pygame.mouse.get_pos()):
                    game_state = "ranking"
                if sound_button.collidepoint(pygame.mouse.get_pos()):
                    if mixer.music.get_busy():
                        mixer.music.pause()
                        sound_icon = pygame.image.load('./img/sound_off.png')
                        screen.blit(sound_icon, (0, 5))
                    else:
                        mixer.music.unpause()
                        sound_icon = pygame.image.load('./img/sound_on.png')
                        screen.blit(sound_icon, (0, 5))
                if exit_button.collidepoint(pygame.mouse.get_pos()):
                    pygame.quit()
                    exit()
        pygame.display.update()
        clock.tick(60)

    elif game_state == "game":
        screen.fill((0, 0, 0))
        screen.blit(background, (0, 0))

        #A timer with miliseconds
        if timer == True:
            elapsed_time += clock.get_time() / 1000
            elapsed_time = round(elapsed_time, 3)
            timer_text = font.render("Time: " + str(elapsed_time), True, (255, 255, 255))
            screen.blit(timer_text, (600, 10))

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    game_state = "menu"
                    reset_game()
                    timer = False
                if event.key == pygame.K_LEFT:  
                    playerX_change = -5  
                if event.key == pygame.K_RIGHT:  
                    playerX_change = 5  
                if event.key == pygame.K_SPACE: 
                    if bullet_state == "ready":  
                        bullet_Sound = mixer.Sound('./music/laser.mp3')
                        bullet_Sound.play()
                        bulletX = playerX 
                        fire_bullet(bulletX, bulletY)
    
            if event.type == pygame.KEYUP:  
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT: 
                    playerX_change = 0
    
        playerX += playerX_change  
    
        if playerX <= 0:  
            playerX = 0  
        elif playerX >= 736:  
            playerX = 736  
    
        # Enemy Movement
        for i in range(num_of_enemies): 

            # Game Over
            if enemyY[i] > 440:
                num_of_enemies = 0
                player_dead = True
                break
    
            enemyX[i] += enemyX_change[i]
            if enemyX[i] <= 0:
                enemyX_change[i] = 4
                enemyY[i] += enemyY_change[i]
            elif enemyX[i] >= 736:
                enemyX_change[i] = -4
                enemyY[i] += enemyY_change[i]

            # Collision
            collision = isCollision(enemyX[i]+15, enemyY[i]+15, bulletX+8, bulletY+8)
            if collision:
                explosion_Sound = mixer.Sound('./music/explosion.mp3')
                explosion_Sound.play()
                bulletY = 480
                bullet_state = "ready"
                score_value += 1

                if(score_value > 9):
                    num_of_enemies = 0
                    boss_stage = True 

                enemyX[i] = random.randint(0, 735)
                enemyY[i] = random.randint(50, 150)

            enemy(enemyX[i], enemyY[i], i)

        # Bullet Movement
        if bulletY <= 0:
            bulletY = 480
            bullet_state = "ready"

        if bullet_state == "fire":
            fire_bullet(bulletX, bulletY)
            bulletY -= bulletY_change

        if boss_stage:
            boss(bossX, bossY)
            bossX += bossX_change
            if bossX <= 0:
                bossX_change = 4
            elif bossX >= 420:
                bossX_change = -4

            if boss_bullet_state == "ready":
                boss_bulletX = bossX
                boss_bulletY = bossY
                fire_boss_bullet(boss_bulletX, boss_bulletY)
                boss_bullet_state = "fire"

            if boss_bulletY >= 520:
                boss_bulletY = bossY
                boss_bullet_state = "ready"

            if boss_bullet_state == "fire":
                fire_boss_bullet(boss_bulletX, boss_bulletY)
                boss_bulletY += boss_bulletY_change

            collisionPlayer1 = isCollision(playerX+15, playerY, boss_bulletX +80 ,boss_bulletY+ 250)
            collisionPlayer2 = isCollision(playerX+15, playerY, boss_bulletX + 270, boss_bulletY+ 250)

            if collisionPlayer1 or collisionPlayer2:
                player_hp -= 1
                boss_bulletY = bossY
                boss_bullet_state = "ready"
                if player_hp == 0:
                    explosion_Sound = mixer.Sound('./music/explosion.mp3')
                    explosion_Sound.play()
                    screen.fill((0, 0, 0))
                    screen.blit(background, (0, 0))
                    boss_stage = False
                    player_dead = True
                
            collisionBoss = isCollisionBoss(bossX, bossY, bulletX+8, bulletY+8)
            if collisionBoss:
                boss_hp -= 1
                bulletY = 480
                bullet_state = "ready"
                if boss_hp == 0:
                    explosion_Sound = mixer.Sound('./music/explosion.mp3')
                    explosion_Sound.play()
                    boss_stage = False
                    #clear screen
                    screen.fill((0, 0, 0))
                    screen.blit(background, (0, 0))
                    boss_dead = True

        player(playerX, playerY)

        if boss_dead:
            name = win_text()
            timer = False
            write_leaderboard(name, elapsed_time) 
        if player_dead:
            game_over_text()
            timer = False

        pygame.display.update() 
        clock.tick(60) 

    elif game_state == "ranking":
        screen.fill((0, 0, 0))
        screen.blit(background, (0, 0))

        title_text = over_font.render("RANKING", True, (255, 255, 0))
        screen.blit(title_text, (250, 100))

        ranking_text = leaderboard()
        split_text = ranking_text.split(":")
        for i in range(len(split_text)):
            if i<5:
                text = font.render(str(i+1) + ". " + split_text[i], True, (255, 255, 255))
                screen.blit(text, (270, 200 + i*50))
        exit_button = pygame.draw.rect(screen, (255, 0, 0), (365, 470, 100, 50))
        exit_text = font.render("EXIT", True, (255, 255, 255))
        screen.blit(exit_text, (375, 480))

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if pygame.mouse.get_pressed()[0]:
                if exit_button.collidepoint(pygame.mouse.get_pos()):
                    game_state = "menu"
        pygame.display.update()
        clock.tick(60)

