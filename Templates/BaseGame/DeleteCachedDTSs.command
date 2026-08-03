#!/bin/sh

cd "`dirname "$0"`"

for i in $(find . -type f \( -iname "*.dae" -o -iname "*.fbx" -o -iname "*.gltf" -o -iname "*.glb" \))
do
   file="${i%.*}.cached.dts"
   if [ -e "$file" ]
   then
   	echo "Removing ${file}"
   	rm "$file"
   fi
done

