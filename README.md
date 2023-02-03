# Projet CY-Météo de Valentin FERNANDES et Erwann DURANEL
***
Ce projet vise à créer une application qui traitera les données météo d'un fichier pour afficher des graphiques.
Les données traitées peuvent être choisies par l'utilisateur et comprennent la température et les pressions atmospheriques.
Un script Shell permettra à l'utilisateur de spécifier les données à analyser, de filtrer les données et de créer des graphiques.

## Installation
*** 
La configuration système des PC de CYtech est nécessaire et suffisante

## Execution
***
Pour executer le programme il suffit, dans le terminal, de saisir bash deb.sh suivies des bonnes options et arguments dans un ordre arbitraires :
bash deb.sh <options1> <option2> <option3> 

## Options
***
Toutes les options désirées par l'utilisateur doivent être ajoutées à la suite de la commande principale (exemple : bash deb.sh -t1 -f meteo_filtered_data_v1 -r0)

Il est possible d'ajouter au moins une ou plusieurs options pour que le programme traite le(s) type(s) de données choisi(s).
-t : pour la température
-p : pour la pression atmosphérique
Les options -t et -p doivent être accompagnées d'un mode :
-t<mode>
-p<mode>
Il faut donc indiquer la valeur du mode que l'on veut utiliser.
Mode 1 (exemple d'utilisation : -t1) : sorties des températures (ou pressions) minimale, maximale et moyenne par station dans l'ordre croissant du numéro de station.

L'option -r permet de choisir dans quel ordre se fait le trie, elle doit être accompagnée d'un mode :
-r<mode>
Il faut indiquer la valeur du mode que l'on veut utiliser.
Mode 0 (exemple d'utilisation : -r0) : trie les données dans l'ordre decroissant.
Mode 1 (exemple d'utilisation : -r1) : trie les données dans l'ordre croissant.

Le nom du fichier d’entrée doit être renseigné grâce à l'option -f pour que le script puisse acquérir toutes les données.
L'option doit être accompagnée du nom du fichier a traité : 
-f<nom_fichier>

l'option --help permet l’affichage d’une aide détaillée quant à l’utilisation du script.
