# Projet-EPFL
Projet d'informatique pour l'EPFL, Propagatio

**Présentation générale :**

Ce projet est un programme de code c++ créé pour un problème d'informatique évalué lors de mon premier semestre à l'EPFL. Nommé Propagatio il a pour but d'évaluer la connexité d'un graphe sous forme Bitmap/Matrice d'adjacence et donner les étapes auquel les noeuds (en partant du 0) apartiennent si une information passait d'un noeud à un ou plusieurs autres une fois part unité de temps et ne pouvant pas revenir sur un noeud déjà visité. Et donne également le degré moyen de spération du graphe.

Mon programme, comme stipulé dans l'énoncé du problème (dont je n'ai plus accès), est composé de 4 fonction principale servant chacune une tâche précise du projet, elles-mêmes regroupées dans une fonction globale permettant à la fonction main d’être complétement dénuée de variables. La **première tâche** composée d’une part de la détection éventuelle d’erreur dans l’input et d’autre part d’une fonction permettant la **transformation** de l’image pbm en matrice d’adjacence. La **seconde tâche** quant à elle, inclut une fonction qui génère les nœuds visité de la matrice sous forme de vecteur, nommé **connexe**, permettant à la tâche de déterminé si le graphe associé est connexe ou non. Les **tâches 3 et 4** utilisent une fonction commune qui donne le **degré de séparation** des nœuds, nommé **propagation**, au sein même de laquelle se trouve une fonction déterminant le **critère d’arrêt** à plusieurs endroits de la fonction principale, nommé **recursion**. Cela permet, à la **tâche 3** de donner l’ordre de passage des nœuds depuis le nœud zéro, et à la **tâche 4** de calculer le degré moyen de séparation du graphe. Les tâches 3 et 4 utilisent donc une même fonction dans laquelle une fonction auxiliaire est répétée.

**Exemple et pratique :**

En input une matrice d'adjacence aurait cette forme :

P1

55

00001

00010

10000

10001

10000


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

00111

00010

10000

11001

10010

D'après cette matrice, si chaque colonne et ligne représente un noeud et chaque 1 représente une connection, le noeud 0 est connecté aux noeuds 2-3-4, le noeud 1 au noeud 3, le noeud 2 au noeud 0, le noeud 3 aux noeuds 0-1-4 et le noeud 4 au noeud 0. Il est ainsi plus facile de comprendre le résultat obtenu car le graphe représenté par la matrice transformée est maintenant complétement lié. On peut donc suivre intuitivement le graphe pour obtenir les mêmes résultats que précédemment.


![propagatio 55](https://user-images.githubusercontent.com/111185446/189409269-3af06c14-ce56-4a41-9fe6-86782114792e.jpg)

