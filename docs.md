# Gestion de table en C

Ce document décrit le travail réalisé pour la gestion d'une table en langage C.

Le principe est simple : implémenter différents prototypes de tables et comparer les bonnes pratiques et les mauvaises pratiques.

Une table est implémentée sous forme d’un tableau statique contenant une structure définie.

# Description de la structure

J’ai créé une fausse table contenant X éléments avec les caractéristiques suivantes :

- Un booléen indiquant si un élément est utilisé ou non,

- Un identifiant unique permettant d’identifier chaque élément de manière univoque,

- Une valeur associée à chaque élément.

# Prototype A

Ce prototype est le plus simple. Il utilise un tableau statique et des fonctions simples pour gérer la table.

Le problème que je souhaite mettre en évidence est le suivant :
comment gérer le parcours de la table autrement qu'avec des boucles for classiques, afin d’optimiser les performances en temps réel ?
