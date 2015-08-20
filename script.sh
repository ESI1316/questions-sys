#!/bin/bash

couille="couille"

echo "Afficher des trucs"
echo "press enter to continue"
read var

./as_trefle

if [ $? -eq 0 ]; then
	echo "ok"
else
	echo "nok"
fi
