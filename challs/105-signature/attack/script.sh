#!/bin/bash

for f in ./*.txt; do
	x=$(openssl dgst -sha256 -verify alice.pub -signature alice-ecdsa-sha256-signature.bin $f);
      	echo $f::$x;
done



