# Projet-EPFL
Projet d'informatique pour l'EPFL, Propagatio

**Présentation générale :**

Ce projet est un programme de code c++ créé pour un problème d'informatique évalué lors de mon premier semestre à l'EPFL. Nommé Propagatio il a pour but d'évaluer la connexité d'un graphe sous forme Bitmap/Matrice d'adjacence et donner les étapes auquel les noeuds (en partant du 0) apartiennent si une information passait d'un noeud à un ou plusieurs autres une fois part unité de temps et ne pouvant pas revenir sur un noeud déjà visité. Et donne également le degré moyen de spération du graphe.

Mon programme, comme stipulé dans l'énoncé du problème (dont je n'ai plus accès), est composé de 4 fonction principale servant chacune une tâche précise du projet, elles-mêmes regroupées dans une fonction globale permettant à la fonction main d’être complétement dénuée de variables. La **première tâche** composée d’une part de la détection éventuelle d’erreur dans l’input et d’autre part d’une fonction permettant la **transformation** de l’image pbm en matrice d’adjacence. La **seconde tâche** quant à elle, inclut une fonction qui génère les nœuds visité de la matrice sous forme de vecteur, nommé **connexe**, permettant à la tâche de déterminé si le graphe associé est connexe ou non. Les **tâches 3 et 4** utilisent une fonction commune qui donne le **degré de séparation** des nœuds, nommé **propagation**, au sein même de laquelle se trouve une fonction déterminant le **critère d’arrêt** à plusieurs endroits de la fonction principale, nommé **recursion**. Cela permet, à la **tâche 3** de donner l’ordre de passage des nœuds depuis le nœud zéro, et à la **tâche 4** de calculer le degré moyen de séparation du graphe. Les tâches 3 et 4 utilisent donc une même fonction dans laquelle une fonction auxiliaire est répétée.

**Exemple et pratique :**

En input une matrice d'adjacence aurait cette forme :

P1

55

0 0 0 0 1 

0 0 0 1 0

1 0 0 0 0 

1 0 0 0 1

1 0 0 0 0


Le résultat du programme si on lui avait donné cet input serai : 

0

2 3 4

1

1,6


L'interprétation générale de ce résultat est le suivant :
- Le dernier nombre est le degré moyen de séparation du graphe en question
- Les nombres précédents sont les numéros des noeuds organisés par étapes croissantes depuis le noeuds zéro

Ici, pour notre exemple, le degré moyen de sépration du graphe est 1,6. La première étape de propagation de l'information est le noeud zéro, la deuxième étape de propagation de l'information sont les noeuds 2-3-4 et la troisième et dernière étape est le noeud 1.

Il est pratique de noter que dans le programme une **transformation** de la matrice est faîte ce qui la rend plus lisible. Dans notre cas la matrice deviendrai la suivante :

0 0 1 1 1 

0 0 0 1 0

1 0 0 0 0

1 1 0 0 1

1 0 0 1 0

D'après cette matrice, si chaque colonne et ligne représente un noeud et chaque 1 représente une connection, le noeud 0 est connecté aux noeuds 2-3-4, le noeud 1 au noeud 3, le noeud 2 au noeud 0, le noeud 3 aux noeuds 0-1-4 et le noeud 4 au noeud 0. Il est ainsi plus facile de comprendre le résultat obtenu car le graphe représenté par la matrice transformée est maintenant complétement lié. On peut donc suivre intuitivement le graphe pour obtenir les mêmes résultats que précédemment.
![propa 55 paint 3D fin](https://user-images.githubusercontent.com/111185446/189665104-f7857b2b-e19c-44d0-b6e7-ba1e6702c0c7.png)
(*fig.1*)

En première étape le noeud 0, en deuxième les noeuds 2-3-4 et en troisième le noeud 1.

Concernant le degré moyen de séparation du graphe cela correspond à la moyenne de : la moyenne des degrés de séparation des noeuds, en partant d'un noeud différent à chaque fois. Le degré de séparation d'un noeud étant l'étape à laquelle il se trouve dans la propagation de l'information depuis le noeud de départ, on peut trouver plusieurs noeuds à un même degré de séparation. La moyenne des degrés de séparation des noeuds, dépend ainsi du noeud de départ choisit, et, correspond pour ce noeud de départ à la distance moyenne à laquelle il est par rapport aux autres noeuds. Dans l'exemple précédent (voir *fig.1*), le noeud 0 est à un "pas" de trois noeuds et à deux "pas" d'un noeud, le dégré de séparation moyen des noeuds part rapport au noeud zéro est donc : 

{(3 noeuds * à 1 pas / 4 noeuds au total)+( 1 noeud * à 2 pas / 4 noeuds au total)} = 1.25 pas nécessaire en moyenne à effectuer depuis le noeud zéro pour en trouver                                                                                         un autre

Pour obtenir la moyenne de la moyenne des degrés de séparation des noeuds en partant d'un noeud différent à chaque fois, il suffit donc de calculer la moyenne des degrés de séparation des noeuds depuis chaque noeuds et de calculer la moyenne de la somme des moyennes des degrés de spération de chaque noeud de départ. Dans notre cas on devra calculer cinq fois la moyenne des degrés de séparation pour les cinq noeuds de départ différents, qui sont dans l'ordre croissant des noeuds :

 - 1.25 pour le noeud 0
 - 2 pour le noeud 1
 - 2 pour le noeud 2
 - 1.25 pour le noeud 3
 - 1.5 pour le noeud 4

La moyenne de ces moyennes des degrés de séparation des noeuds est donc :

(1.25 + 2 + 2 + 1.25 + 1.5)/5 = 8/5 = 1.6

Traduction du degré moyen de séparation du graphe ci-dessus (*fig.1*) : En partant de n'importe où dans le graphe il faudrat effectuer pour une information en moyenne 1.6 étapes pour atteindre tous les noeuds du graphes, une étape correspondant à une salve de "pas" possible depuis chaque noeud possédant l'information en une unité de temps. 
