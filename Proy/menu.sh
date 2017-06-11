#!/bin/bash
 #usage
 #  -c cifrar enc/dec  -k llave    -e nombre archivo entrada -s nombre archivo salida 
 # generar clabes RSA -genKeys 
#usage -k key -e archent -s salida 
while getopts ":c:s:e:k:v:o:g" opt; do
  case $opt in
    s)
        #echo "s"
        archSal=$OPTARG
        ;;
    e)
        #echo "e"
        archEnt=$OPTARG
        ;;
    k)
        #echo "k"
        keyPlane=$OPTARG
        ;;
    c)
        #echo "c"
        encWork=$OPTARG
        #echo -n "value" | openssl sha1 -hmac $keyPlane
        #sha=$(echo $keyPlane |openssl sha1 )
        sha=$(echo -n $keyPlane | openssl dgst -sha1 | sed 's/^.* //')
        echo "./AEScipher $sha $archEnt $archSal $encWork "
        ./AEScipher $sha $archEnt $archSal $encWork 
        ;;
    g)
        echo "genKeys"
        openssl genrsa -des3 -out private.pem 2048
        openssl rsa -in private.pem -outform PEM -pubout -out public.pem
        ;;
    o)  
        echo "signature"
        echo $OPTARG
        openssl dgst -sha256 -sign private.pem -out /tmp/sign.sha256 $OPTARG
        openssl base64 -in /tmp/sign.sha256 -out signature.sig
        ;;
    v) 
        openssl base64 -d -in $archEnt -out /tmp/sign.sha256
        openssl dgst -sha256 -verify public.pem -signature /tmp/sign.sha256 $OPTARG
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