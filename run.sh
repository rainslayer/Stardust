#!/bin/bash

cd stardust_build

if [ "$1" == "-c" ];
then
	rm -rf .stardust/
else
	./stardust $@
fi
