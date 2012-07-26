#!/bin/bash

# Activates the mpd deamon if not active.

if [ $# == 0 ]; then
    echo "usage:"
    echo "  activate-mpdboot.sh numberOfNodes machinesList [number]"
    exit -1
fi

MPDTRACE=mpdtrace
NB_NODES=$1
NODES=~/$2

if [ $# == 2 ]; then
    QUEL=""
else
    QUEL="$3"
fi

statut=$( $MPDTRACE >/dev/null; echo $?)
if [ $statut != 0 ]; then
    if [ $NB_NODES == 1 ]; then
	echo "*** Activation of mpdboot with one processor."
    else
	echo "*** Activation of mdpboot with $NB_NODES processors."
    fi
    #echo "mpdboot -n $NB_NODES -f $NODES"
    mpdboot -n $NB_NODES -f $NODES
    touch .mpdboot$QUEL
fi
