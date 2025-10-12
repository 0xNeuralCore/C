# Gestion de table en C

Ce document décrit le travail réalisé pour la gestion d'une table en langage C.
Le principe est simple : implémenter différents prototypes de tables et comparer les bonnes et les mauvaises pratiques.

Une table est implémentée sous la forme d’un tableau statique contenant une structure définie.

# Description de la structure

J’ai créé une fausse table contenant X éléments, avec les caractéristiques suivantes :

- Un booléen indiquant si un élément est utilisé ou non.

- Un identifiant permettant d’identifier chaque élément de manière unique.

- Une valeur associée à chaque élément.

# Description des fonctionnalités

Deux fonctions principales ont été implémentées :

- F_add_element() : permet d’ajouter un élément dans la table,

- F_search_element() : permet de rechercher la valeur associée à un identifiant dans la table.

# Prototype A

Ce prototype est le plus simple.
Il utilise des boucles for classiques pour parcourir la table lors de l’ajout et de la recherche d’éléments.

L’objectif est de mettre en évidence le problème suivant :
la recherche d’un élément n’est pas optimisée.
En effet, dans le pire des cas, il faut parcourir l’intégralité de la table pour trouver (ou ne pas trouver) un élément, ce qui peut devenir très coûteux en temps pour des tables de grande taille.

# Prototype B

Ce prototype illustre une gestion par hachage sans problème de collision, c’est-à-dire que la table de hachage contient le même nombre d’entrées que la table principale.

Le fonctionnement est simple :
la table de hachage contient des pointeurs vers les éléments de la table principale.
Ces pointeurs sont mis à jour lors de l’ajout d’un élément dans la table principale.

Ainsi, lors d’une recherche, il suffit de calculer l’index de hachage à partir de l’identifiant, puis d’accéder directement à l’élément correspondant dans la table principale via le pointeur stocké dans la table de hachage.

Ce mécanisme permet d’obtenir un temps d’accès constant.