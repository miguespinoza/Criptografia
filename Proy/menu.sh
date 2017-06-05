#!/bin/bash
 #usage
 #  -c cifrar enc/dec  -k llave    -e nombre archivo entrada -s nombre archivo salida 

while getopts ":c:s:e:k:" opt; do
  case $opt in
    s)
        echo "s"
        archSal=$OPTARG
        ;;
    e)
        echo "e"
        archEnt=$OPTARG
        ;;
    k)
        echo "k"
        keyPlane=$OPTARG
        ;;
    c)
        echo "c"
        encWork=$OPTARG
        #echo -n "value" | openssl sha1 -hmac $keyPlane
        sha=$(echo $keyPlane |openssl sha1 )
        echo $sha
        ;;
    \?)
      echo "Invalid option: -$:OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done