# Documentation Whiteboard-B3
# Par Bertaud Nathan, Swan Breton, Louis Colombel, Bamody Doumbia


## Objectif
Ce projet permet d'ouvrir des tableaux blancs, de maniere a pouvoir y dessiner a plusieurs.
Un utilisateur peut ainsi ouvrir son tableau, blanc ou à partir d'une image, et un ou plusieurs autres s'y connecter et dessiner.

Un utilisateur peut également sauvegarder son tableau pour pouvoir le réouvrir plus tard.

## Technologies

- C++ et le framework qt : Permet une implementation complete, offrant un modele de développement robuste et eficace, ainsi qu'une variété de composantes graphiques et de librairies.
- Stack Reseau : Socket tcp qui heberge, ou des clients tcp se connectent pour partager les informations.

## Fonctionnalités

- Heberger un serveur, lui donner un nom , un mot de passe, une image de base, d'environ 10ko max pour le moment.
- Se connecter a une adresse ip
- Dessiner sur le tableau
- Changer la taille
- Changer la couleur
- Sauvegarder le tableau en image
- Voir les curseurs se deplacer en temps réel


## Fonctionnement

Le serveur fonctionne sur le principe de socket tcp. le tcp permet d'avoir un accusé de reception des paquets avec un renvoi en cas d'echec, tout en etant un protocole bas niveau donc plus rapide qu'un socket web par exemple, et en assurant une integrité des données contrairement a UDP.
Toutes les requetes reseaux envoient des structures converties a l'envoie en binaire, avec un type en en tete, ce qui permet a l'entité qui recoit de la reconvertir pour l'utiliser. Cela permet des requetes plus petites qu'un transport de l'information en json ou xml.


A la connexion d'un client, le serveur lui envoie l'image du tableau ainsi que l'identifiant que va adopter le client, ce qui va lui permettre d'etre identifiable par la suite.

Le client va ensuite envoyer des curseurs au serveur, correspondant au mouvement de la souris, avec la position, taille , couleur et si il faut dessiner ou pas.

Le serveur repartit ce qu'il envoie a tous les autres clients, qui traite de leurs coté l'information.

Quand un client reçoit un curseur, il deplace sur le tableau  le curseur correspondant a l'identifiant de la requete, et dessine ou non avec les informations de la requete.

## Interface utilisateur

L'interface consiste en une page principale ou on peut se connecter et heberger, un formulaire de connexion avec des champs ip et mot de passe, un formulaire d'hebergement avec le nom, le mot de passe et un boutton permettant de choisir un fichier, en ouvrant un explorateur de fichier.
L'interface de connexion débouche sur la page du tableau, ou l'utilisateur peut dessiner, changer la taille et la couleur, et sauvegarder le tableau, ce qui ouvre également un explorateur de fichier.

## Fonctionnalités non implementées

Le systeme d'information ne présente pas de redondance, ce qui signifie que si le serveur principal s'arrete, tous les clients sont deconnéctés et tout est perdu. La systeme de redondance qui aurait pu etre implémenté est un systeme ou tous les clients ont connaissance des adresses ip connectées, et le client qvec l'identifiant "1" ouvre un nouveau serveur si le premier s'arrete. Tous les autres clients se reconnecteraient ainsi à ce nouveau serveur, qui enverraient ainsi sa version du tableau à tous le monde pour re-synchroniser.

Le check du mot de passe n'est également pour le moment pas implémenté.

## User stories

En tant qu’utilisateur je veux pouvoir créer un tableau afin de dessiner

En tant qu’utilisateur je veux pouvoir ouvrir l'accès à un tableau afin de dessiner avec d’autres utilisateurs.

En tant qu’utilisateur je veux pouvoir rejoindre un tableau afin de dessiner avec d’autres utilisateurs.

En tant qu’utilisateur je veux pouvoir sauvegarder un tableau afin de le rouvrir plus tard.

En tant qu’utilisateur je veux pouvoir ouvrir un tableau existant afin de travailler sur un projet existant.


## Gestion de projet

Pour la gestion de projet, nous avons utilisé Trello, pour séparer les taches de manière a avoir une idée claire du travail a fournir. Le travail a été séparées en sous taches par domaines, avec le temps estimés pour chacune d'entre elles.
Chaque tâche est soit dans la colonne "A reflechir", "A faire", "En cours" ou "Fini".

## Diagrammes 

Diagramme des classes :

![image diagramme classe](https://github.com/BertaudNathan/Whiteboard-B3/blob/main/documentation/diagramme-classes.png?raw=true)


Diagramme des interactions client-serveur :

![image diagramme interactions](https://github.com/BertaudNathan/Whiteboard-B3/blob/main/documentation/interactions.png?raw=true)


## images de l'application

menu principal :
![image menu principal](https://github.com/BertaudNathan/Whiteboard-B3/blob/main/documentation/menu.png?raw=true)

formulaire hebergement :
![image menu principal](https://github.com/BertaudNathan/Whiteboard-B3/blob/main/documentation/formulaire-hebergement.png?raw=true)


formulaire connexion :
![image menu principal](https://github.com/BertaudNathan/Whiteboard-B3/blob/main/documentation/formulaire-connexion.png?raw=true)


ecran tableau :
![image menu principal](https://github.com/BertaudNathan/Whiteboard-B3/blob/main/documentation/whiteboard.png?raw=true)


ecran tableau avec image :
![image menu principal](https://github.com/BertaudNathan/Whiteboard-B3/blob/main/documentation/whiteboard-image.png?raw=true)



