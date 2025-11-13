<a id="fr"></a>

<div align="center">
  <a href="#en">🇬🇧 English</a> · 
  <a href="#fr">🇫🇷 français</a>
</div>

# Casse-briques

Bienvenue dans Casse-Bugues, le jeu où tu ne détruis pas seulement des briques, mais aussi les bugs qui hantent ton code. Chaque rebond est un pas de plus vers un programme plus propre… et un mur totalement pulvérisé.

## Introduction du sujet

Le projet consiste à créer en C++ avec SFML, un jeu de type casse-briques.

Le *Casse-Briques* est un jeu vidéo classique qui met en scène une raquette, une balle, et un ensemble de briques à détruire. Le but du joueur est de contrôler la raquette pour faire rebondir la balle de manière à casser toutes les briques, sans laisser tomber la balle hors de l’écran.

## Étape 1 : Construisons notre mini moteur de jeu avec SFML

Avant de tirer des balles et de casser des briques comme des pros, on va poser les fondations d’un petit moteur de jeu maison. L’objectif ? Manipuler des objets à l’écran, gérer les entrées clavier/souris, et détecter des collisions… le tout en **C++ avec SFML**.

**Ce qu’on veut construire dans cette première partie :**

- **Gestion des GameObjects**
    - Affichage d’un cercle ou d’un rectangle à des coordonnées (x, y)
    avec une taille définie.
    - Déplacement dynamique grâce à une vitesse.
    - Rotation possible.
    - Ajout d’une zone de collision avec une boîte englobante (AABB).
    - Détection de collisions avec d’autres GameObjects.

- **L'InputManager : notre maître du clavier et de la souris**
    - Écoute des événements clavier et souris.
    - Permet de lier des fonctions (callbacks) à des actions spécifiques (ex: clic gauche = tirer, touche E = exploser).
    - Prêt à faire réagir ton jeu comme tu veux, quand tu veux.

## **Étape 2 : Casse-Briques Reborn – avec un canon !**

## Pour aller plus loin…

**Bonus techniques (si t’aimes les challenges) :**

- Gérer la collision entre un **cercle** et une **AABB**.
- Ajouter des **images/ressources** dans tes objets via un **AssetManager**
(singleton FTW).
- Charger un **niveau via un fichier texte :** rapide, customisable, pro.
- Permettre plusieurs tirs simultanés (limités) et gérer leurs collisions.
- **Clic droit = onde de choc :**
    - Une attaque de zone rectangulaire dans la direction du canon.
    - Repousse toutes les balles touchées sur son passage.

## Compétences visées

- Installer et configurer son environnement de travail en fonction du projet.
- Développer des interfaces utilisateur
- Développer des composants métier
- Contribuer à la gestion d'un projet informatique
- Analyser les besoins et maquetter une application
- Définir l'architecture logicielle d'une application

## Rendu

- Votre travail est évalué en présentation avec un support et une revue de code. Le slide doit être composé de :
- De l’organisation de votre équipe
- De vos problèmes rencontrés ainsi que les solutions apportées
- La démonstration jouable de votre jeu
- Le projet est à rendre sur https://github.com/prenom-nom/CasseBriques

## Base de connaissances

- [Installation de la SDL](https://www.libsdl.org/)
- [Cours de C++ avancé](https://cplusplus.com/doc/tutorial/)
- [Installation de la SFML](https://www.sfml-dev.org/tutorials/2.6/start-vc.php)
- [Tutoriel SFML](https://www.sfml-dev.org/tutorials/2.6/)
- [Casse-brique](https://www.crazygames.fr/jeu/atari-breakout)
- [Frozen-bubble](https://www.crazygames.fr/jeu/bubble-blast-pwd)

<a id="en"></a>

<div align="center">
  <a href="#en">🇬🇧 English</a> · 
  <a href="#fr">🇫🇷 français</a>
</div>

# Brick Breaker

Welcome to Brick Breaker, the game where you don't just destroy bricks, but also the bugs that haunt your code. Every bounce is another step towards cleaner code… and a completely pulverized wall.

## Subject Introduction

The project consists of creating a brick breaker-type game in C++ with SFML.

*Brick Breaker* is a classic video game that features a paddle, a ball, and a set of bricks to destroy. The player's goal is to control the paddle to bounce the ball in such a way as to break all the bricks without letting the ball fall off the screen.

## Step 1: Building Our Mini Game Engine with SFML

Before firing balls and smashing bricks like pros, we'll lay the foundations of a small in-house game engine. The objective? Manipulate objects on screen, manage keyboard/mouse input, and detect collisions… all in **C++ with SFML**.

**What we want to build in this first part:**

- **GameObject Management**
    - Display a circle or rectangle at coordinates (x, y)
    with a defined size.
    - Dynamic movement through velocity.
    - Possible rotation.
    - Adding a collision zone with a bounding box (AABB).
    - Collision detection with other GameObjects.

- **The InputManager: Our Master of Keyboard and Mouse**
    - Listening for keyboard and mouse events.
    - Allows binding functions (callbacks) to specific actions (e.g., left click = shoot, E key = explode).
    - Ready to make your game react however and whenever you want.

## **Step 2: Brick Breaker Reborn – with a Cannon!**

## To Go Further…

**Technical Bonuses (if you like challenges):**

- Handle collision between a **circle** and an **AABB**.
- Add **images/resources** to your objects via an **AssetManager**
(singleton FTW).
- Load a **level from a text file:** fast, customizable, professional.
- Allow multiple simultaneous shots (limited) and manage their collisions.
- **Right click = shockwave:**
    - A rectangular area attack in the direction of the cannon.
    - Repels all balls touched in its path.

## Target Skills

- Install and configure your work environment according to the project.
- Develop user interfaces
- Develop business components
- Contribute to the management of an IT project
- Analyze requirements and mockup an application
- Define the software architecture of an application

## Deliverables

- Your work is evaluated through a presentation with supporting materials and code review. The slides should include:
- Your team's organization
- The problems you encountered and the solutions provided
- A playable demonstration of your game
- The project must be submitted to https://github.com/first-name-last-name/CasseBriques

## Knowledge Base

- [SDL Installation](https://www.libsdl.org/)
- [Advanced C++ Course](https://cplusplus.com/doc/tutorial/)
- [SFML Installation](https://www.sfml-dev.org/tutorials/2.6/start-vc.php)
- [SFML Tutorial](https://www.sfml-dev.org/tutorials/2.6/)
- [Brick Breaker](https://www.crazygames.fr/jeu/atari-breakout)
- [Frozen Bubble](https://www.crazygames.fr/jeu/bubble-blast-pwd)