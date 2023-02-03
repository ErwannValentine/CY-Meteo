#!/bin/bash

make

pmode='-1'
tmode='-1'
croissant='1'
nom_fichier='0'

while getopts :p:t:f:r: opt; do

case $opt in
    f) nom_fichier=$OPTARG
    ;;
    p) pmode=$OPTARG
    ;;
    t) tmode=$OPTARG
    ;;
    r) croissant=$OPTARG
    ;;
    \?) echo "erreur options non existantes"
        exit 2
esac

done

#sed '/;$/d' temp.csv > temporaire.csv
#sed '1d' temporaire.csv > temporaire2.csv

#sed '/;$/d' press.csv > pressporaire.csv
#sed '1d' pressporaire.csv > pressporaire2.csv

#./AVL pressporaire2.csv dateee.dat


if (( $pmode == 1 ))
then
	echo A
    cut -d';' -f 1,7 $nom_fichier > press.csv
	echo B
    sed '/;$/d' press.csv > pressporaire.csv
    sed '1d' pressporaire.csv > pressporaire2.csv
    ./exec pressporaire2.csv datap1.dat $croissant
    gnuplot gnup1.gnu
else

    if [[ "$pmode" != '-1' ]]
    then
        echo "le mode de pression spécifié n'existe pas"
    fi
fi








if (( $tmode == 1 ))
then
	echo C
    cut -d';' -f 1,11 $nom_fichier > temp.csv
	echo D
    sed '/;$/d' temp.csv > temporaire.csv
    sed '1d' temporaire.csv > temporaire2.csv
    ./exec temporaire2.csv datat1.dat 1
    gnuplot gnut1.gnu
else

    if [ $tmode -ne -1 ]
    then
    	echo "le mode de température spécifié n'existe pas"
    fi
fi



make clean



exit 0


