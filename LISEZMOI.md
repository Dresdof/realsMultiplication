realsMultiplication
===================

Multiplication de nombres réels à grande précision en C avec MPI
----------------------------------------------------------------

Pour fonctionner, ce programme nécessite un système sur lequel MPI (Message Passing Interface) est installé. 

Il peut être exécuté selon trois modes de parallélisme :
+ Séquentiel
+ Parallélisme de données
+ Parallélisme à sac de tâches

La cible principale du makefile est une exécution parallèle de type parallélisme de données avec mesure du temps d'exécution. 
Pour exécuter la version séquentielle, utilisez make run-sequential.
Pour exécuter la version parallèle à sac de tâches, utilisez make TYPE=2.
Pour modifier la taille du problème, ajoutez le paramètre SIZE=*** (la taille par défaut est de 1000, taille minimum pour une mesure valable).
Pour modifier le nombre de processurs, ajoutez NP=* (Nombre par défaut : 8).

Le résultat calculé ne sera pas affiché car les nombres utilisés pour les mesures sont générés aléatoirement et le résultat sera généralement de grande taille. Seul, il n'a donc aucun intérêt.


Pour exécuter les tests, utilisez make tests, en pécisant éventuellement le type d'exécution. 
Encore une fois, l'exécution séquentielle dispose d'une cible spécifique: make tests-sequential.
Note : les tests de la version parallèle à sac de tâche peuvent échouer, pour une raison inconnue.
