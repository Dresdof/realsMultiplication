#!/bin/bash

# Pour activer le deamon mpd, si pas actif.

if [ $# == 0 ]; then
    echo "usage:"
    echo "  activer-mpdboot.sh nbNoeuds listeMachines [num]"
    exit -1
fi

MPDTRACE=mpdtrace
NB_NOEUDS=$1
LES_NOEUDS=~/$2

if [ $# == 2 ]; then
    QUEL=""
else
    QUEL="$3"
fi

statut=$( $MPDTRACE >/dev/null; echo $?)
if [ $statut != 0 ]; then
    if [ $NB_NOEUDS == 1 ]; then
	echo "*** On active mpdboot avec un seul processeur"
    else
	echo "*** On active mpdboot avec $NB_NOEUDS processeurs"
    fi
    #echo "mpdboot -n $NB_NOEUDS -f $LES_NOEUDS"
    mpdboot -n $NB_NOEUDS -f $LES_NOEUDS
    touch .mpdboot$QUEL
fi
