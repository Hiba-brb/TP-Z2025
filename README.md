# Optimized Word Search Using BST Variants

Projet en langage C issu d’un TP du module ** Algorithmique et Structures de Données Dynamiques ** (1ère année prepa / semestre 2 – 2025).

## 🎯 Objectif

Optimiser la recherche de mots commençant par certaines lettres à l’aide d’un triplet d’arbres binaires de recherche (BST1, BST2, BST3), avec des règles de rotation spécifiques :

- **BST1** : mots commençant par `X`, `Y` ou `Z` → amenés à la racine. (X = 'Y', Y = 'Z', or Z = 'a')
- **BST2** : mêmes lettres → amenées au milieu du chemin de recherche.
- **BST3** : autres lettres → amenées à la racine.

##  Fonctionnalités principales

- Construction des BST à partir d’un fichier de mots généré automatiquement.
- Recherche de mots simples selon leur première lettre.
- Recherche dans une plage de mots (`[Word1, Word2]`).
- Visualisation et amélioration de l'affichage des résultats.
- Statistiques sur l’efficacité des recherches (succès/échec).

## 📁 Fichiers

- `main.c` → Implémentation principale en C du projet
- (Optionnel) `words.txt` → Fichier de mots générés (à créer dynamiquement)


```bash
gcc main.c -o word_search
./word_search
