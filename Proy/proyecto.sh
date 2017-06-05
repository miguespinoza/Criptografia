#!/bin/bash   


echo -n "value" | openssl sha1 -hmac "HOLA"
       
#./AEScipher enc mundo.jpg sal.cr
#./AEScipher dec sal.cr	mundo2.jpg