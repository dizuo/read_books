#!/bin/bash

function ifErrorExit()
{
	exit_var=$?
    if [ $exit_var -ne 0 ]; then 
    {       
	    echo "process error = [ $exit_var ] ,exit!!!!"
	}       
	else    
	{       
		echo "process sucess ,go  go go !!!"
		return 0
	}       
	fi      
}

echo "python first step ==>"
python test.py
ifErrorExit

echo "python second step ==>"
python test.py 12
ifErrorExit

echo "c first step ==>"
./test_app helloworld
ifErrorExit

echo "c second step ==>"
./test_app
ifErrorExit

python judge.py /data4/zmying/backup/map_nav_data.228/map_nav_data/2014-12-09/41f81ba095094c13e39132bb39fd354e_1418056264023
ifErrorExit

