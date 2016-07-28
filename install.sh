#!/bin/env bash

PERL_BINARY_PATH=/opt/perl5.24/bin/perl
PYTHON_BINARY_PATH=/usr/bin/python
PERL_SOURCES_PATH=/root/perl-5.24.0
PYTHON_SOURCES_PATH=

#saving curent working directory
CWD=$(pwd)



if [ -f "MULTI_PERL" ]
then
	echo "MULTI_PERL found."
else
	echo "MULTI_PERL not found."
fi



if [[ $($PERL_BINARY_PATH -V | grep 'useithreads=define') = "" ]]; then
	cat << EOF
	You can select between 2 flavours for how to build the Perl for Python
	extension.  Which flavour to build is selected by the presence (or
	absence) of the MULTI_PERL file in this directory.  When MULTI_PERL is
	enabled, each python thread will get its own separate perl
	interpreter.  For -DMULTI_PERL builds an ithread eanabled perl is
	required.  It means that if you build your own perl you should pass
	the -Dusethreads option to 'Configure'.
EOF
  exit 1
fi


cd ./Python-Object







#return to the working directory
cd $CWD
exit 0