Instructions d’exécution du programme « Projet_micro_sujet4_hamza_maram_2AGE2 » sur la carte STM32F407

Ce document décrit les étapes nécessaires pour compiler, programmer et exécuter ce programme sur la carte STM32F407 à l’aide de Keil uVision5.
Le programme permet de générer un signal sinusoïdal via le DAC, d’en ajuster l’amplitude et la fréquence à l’aide de potentiomètres, et de calculer la valeur efficace (RMS) du signal par acquisition ADC.

Toutes les connexions matérielles doivent être réalisées conformément au rapport « RAPPORT Sujet4 2AGE2 Hamza & Maram ».
---
Prérequis

Avant de commencer, vérifier les éléments suivants :

1. Dossier du projet
Assurez-vous de disposer du dossier complet du projet, contenant tous les fichiers sources et sous-dossiers nécessaires, notamment :Projet_micro_sujet4_hamza_maram_2AGE2

2. Logiciel Keil uVision5
Installer Keil uVision5 sur votre ordinateur avec le compilateur ARM requis.

3.MONTAGE MATÉRIEL – connexions :

PA4 (DAC Channel 1) est relié à l’entrée de l’oscilloscope afin d’observer le signal sinusoïdal généré.
Cette même broche PA4 est également reliée à une entrée du convertisseur analogique–numérique (ADC) afin de mesurer le signal généré.

Le potentiomètre de réglage de l’amplitude est câblé de la façon suivante :
– borne 1 reliée au 3,3 V
– borne 2 (curseur) reliée à l’entrée PC1 du microcontrôleur
– borne 3 reliée à la masse (GND)

Le potentiomètre de réglage de la fréquence est câblé de la façon suivante :
– borne 1 reliée au 3,3 V
– borne 2 (curseur) reliée à l’entrée PC2 du microcontrôleur
– borne 3 reliée à la masse (GND)

La carte STM32 est alimentée en 3,3 V.
Toutes les masses sont communes : masse de la carte STM32, masse des potentiomètres et masse de l’oscilloscope.
------------
Étapes d’exécution

Étape 1 : Localisation du projet
   .Ouvrir le dossier Projet_micro_sujet4_hamza_maram_2AGE2
   .Localiser le fichier projet Keil:Projet_micro_sujet4_hamza_maram_2AGE2

Étape 2 : Lancement de Keil uVision5
   .Lancer Keil uVision5
   .Cliquer sur Open Project
   .Sélectionner le fichier Projet_micro_sujet4_hamza_maram_2AGE2.uvprojx

Étape 3 : Vérification de la configuration du compilateur
   .Aller dans Flash → Configure Flash Tools → Target
   .Vérifier la configuration du microcontrôleur STM32F407
   .Sélectionner Compiler Version 6 (ARM Compiler 6) afin d’éviter tout problème de compatibilité

Étape 4 : Compilation du projet
   .Cliquer sur Build pour compiler le programme
   .Vérifier qu’aucune erreur de compilation n’est présente
   .En cas d’erreur, s’assurer que :
          -Le bon compilateur est sélectionné
          -Tous les fichiers du projet sont présents

Étape 5 : Connexion de la carte STM32F407
    .Connecter la carte STM32F407 à l’ordinateur
    .Vérifier que le câblage correspond exactement à celui décrit dans le rapport :
          -Potentiomètres correctement branchés sur PC1 et PC2
          -Sortie DAC PA4 reliée à l’ADC pour le calcul RMS
          -Sonde de l’oscilloscope connectée sur PA4 pour visualisation du signal

Étape 6 : Programmation et exécution
   .Flasher le programme sur la carte STM32F407 à l’aide de Keil uVision5
   .Lancer l’exécution du programme
   .Observer :
          -Un signal sinusoïdal en sortie du DAC
          -Une variation de l’amplitude via le potentiomètre PC1
          -Une variation de la fréquence (1 à 100 Hz) via le potentiomètre PC2
          -La valeur efficace (RMS) calculée à partir du signal acquis par l’ADC
---
Ressources supplémentaires

Une vidéo démonstrative est fournie et présente la génération du signal sinusoïdal ainsi que le réglage en temps réel de l’amplitude et de la fréquence.

Pour une description détaillée du projet, du câblage matériel et du fonctionnement du programme, se référer au « RAPPORT Sujet4 2AGE2 Hamza & Maram ».