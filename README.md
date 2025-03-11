#Documentation Whiteboard-B3


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

L'interface consiste en une page principale ou on peut se connecter et heberger, un formulaire de connexion avec des champs ip et mot de passe, un formulaire d'hebergement avec
