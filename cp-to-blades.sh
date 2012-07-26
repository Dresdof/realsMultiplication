#!/bin/bash

#
# Checking args
#
if [ $# == 0 ]; then
    echo "usage:"
    echo "  cp-to-blades.sh <fileToCopy> [<fileWithNodeNames>]"
    echo ""
    exit -1
fi

#
# Making the copy to the machines
#
exec=$1

if [ $# == 1 ]; then
    nodes="mpd.hosts"
else
    nodes="$2"
fi

\cp -f $nodes ~/$nodes

nbBlades=0
echo "* Copying '$exec' on blades."
for blade in $(cat ~/$nodes); do
    scp $exec "$blade:$exec" > /dev/null
    nbBlades=$(( $nbBlades + 1 ))
done
echo "* '$exec' copied on $nbBlades machines."
exit 0
