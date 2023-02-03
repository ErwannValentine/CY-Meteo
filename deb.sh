#!/bin/bash

if [[ "$1" == '--help' ]] || [[ "$2" == '--help' ]] || [[ "$3" == '--help' ]] || [[ "$4" == '--help' ]] || [[ "$5" == '--help' ]]
then
	#cat README.md
	exit 0
fi

make
if (( $? != 0 ))
then
	echo "la commande make ne doit pas avoir été utilisé en amont sans finir par make clean, le programme se réinitialise"
	make clean
	if (( $? != 0 ))
	then
		echo "la commande make rencontre une autre difficulté "
		exit 1
	fi
fi

#quelques initialisations
pmode='-1'
tmode='-1'
croissant='1' # si croissant = 1: sens de trie croissant  sinon, sens de trie décroissant
nom_fichier='0'
verificationF='0'

#parcours les options en paramètre pour enregistrer les informations utiles
while getopts :p:t:f:r: opt; do

case $opt in
    f) nom_fichier=$OPTARG; verificationF='1'
    ;;
    p) pmode=$OPTARG
    ;;
    t) tmode=$OPTARG
    ;;
    r) croissant=$OPTARG
    ;;
    \?) echo "erreur options non existantes"
        exit 1
esac

done

if [[ "$verificationF" != '1' ]]
then
    echo "le paramètre obligatoire -f n'a pas été spécifié, Donc le programme ne peut pas aller plus loin..."
	make clean
	exit 1
fi


#cas -p <mode>
if (( $pmode == 1 ))
then
	#sélectionne les colonnes pertinentes
    cut -d';' -f 1,7 $nom_fichier > press.csv

	#supprime les lignes dont la pression n'est pas renseigné
    sed '/;$/d' press.csv > pressporaire.csv

	#suprimme la première ligne (le titre est superflue)
    sed '1d' pressporaire.csv > pressporaire2.csv

	#enregistre dans datap1.dat l'id de chaque station dans l'ordre souhaité, avec respectivement leur pression minimale, maximale, et moyenne. 
    ./exec pressporaire2.csv datap1.dat $croissant
	if (( $? != 0 ))
	then
		echo "le trie n'a pas abouti"
		make clean
		exit 1
	fi

	#fabrique un diagramme type barre d'erreur en fonction des données de datat1.dat 
    gnuplot gnup1.gnu

	#affiche le diagramme
	display im_p1.png 
else
	#cas d'un mauvais <mode>
    if [[ "$pmode" != '-1' ]]
    then
        echo "le mode de pression spécifié n'existe pas"
    fi
fi

#cas -t <mode>
if (( $tmode == 1 ))
then
	#sélectionne les colonnes pertinentes
    cut -d';' -f 1,11 $nom_fichier > temp.csv

	#supprime les lignes dont la température n'est pas renseigné
    sed '/;$/d' temp.csv > temporaire.csv

	#suprimme la première ligne (le titre est superflue)
    sed '1d' temporaire.csv > temporaire2.csv

	#enregistre dans datat1.dat l'id de chaque station dans l'ordre souhaité, avec respectivement leur température minimale, maximale, et moyenne. 
    ./exec temporaire2.csv datat1.dat 1
	if (( $? != 0 ))
	then
		echo "le trie n'a pas abouti, vous pouvez retenter en entrant de nouveau la même commande"
		make clean
		exit 1
	fi

	#fabrique un diagramme type barre d'erreur en fonction des données de datat1.dat 
    gnuplot gnut1.gnu

	#affiche le diagramme
	display im_t1.png 
else
	#cas d'un mauvais <mode>
    if [[ "$tmode" != '-1' ]]
    then
    	echo "le mode de température spécifié n'existe pas"
    fi
fi



make clean



exit 0



