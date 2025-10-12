# Gestion de table en C

## Introduction

Ce document présente différents prototypes d’implémentation d’une table en langage C.
L’objectif est de comparer plusieurs approches afin de comprendre leurs avantages, leurs limites et leur impact sur les performances.

Une table est représentée sous la forme d’un tableau statique contenant une structure d’éléments.

## Description de la structure

Chaque élément de la table contient :

- Un booléen indiquant si l’élément est utilisé ou non.

- Un identifiant unique permettant de distinguer chaque élément.

- Une valeur associée à cet identifiant.

## Fonctions principales

Deux fonctions de base ont été implémentées :

- F_add_element() : ajoute un nouvel élément dans la table.

- F_search_element() : recherche la valeur associée à un identifiant donné.

# Prototype A — Table simple

## Introduction

Le premier prototype est le plus basique.
Il utilise des boucles for classiques pour parcourir la table lors de l’ajout et de la recherche d’éléments.

## Principe

Lors de l’ajout, la fonction parcourt la table pour trouver une case libre.

Lors de la recherche, elle parcourt la table jusqu’à trouver le bon identifiant.

## Limite

Cette approche fonctionne bien pour de petites tables, mais devient peu performante lorsque la table grandit.
Dans le pire des cas, il faut parcourir tous les éléments pour trouver (ou ne pas trouver) la donnée recherchée.

# Prototype B — Table avec hachage

## Introduction

Le second prototype introduit une table de hachage, permettant d’accéder plus rapidement aux éléments.
Il s’agit d’une version simplifiée, sans gestion des collisions.

## Principe

### Fonction de hachage

Une fonction de hachage calcule un index à partir de l’identifiant :

```
index = id % N;
```

où N est la taille de la table de hachage.
L’index obtenu est toujours compris entre 0 et N - 1.

La table de hachage contient des pointeurs vers les éléments de la table principale.
Lorsqu’un nouvel élément est ajouté, le pointeur correspondant est mis à jour.

### Recherche

Pour retrouver un élément, il suffit de :

- Calculer l’index avec la fonction de hachage.

- Accéder directement à l’élément pointé dans la table principale.

- Cette méthode permet un temps d’accès constant (O(1)), ce qui améliore fortement les performances par rapport au prototype A.

## Limite

Ce prototype ne gère pas les collisions (plusieurs identifiants qui produisent le même index).
Dans la pratique, une liste chaînée ou une stratégie de résolution de collision est nécessaire pour éviter la perte de données.
C’est ce que montrera le prototype C.

# Prototype C — Table avec hachage et table chainée

TODO: Ajouter une description du prototype C.

# Prototype D — Table avec hachage plus complexe

TODO: Ajouter une description du prototype D.