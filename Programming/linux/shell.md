#!/bin/bash

read  -p "enter grade:" GRADE
if [ $GRADE -lt 0 ] || [ $GRADE -gt 100 ]
then
    echo "error"
elif [ $GRADE -ge 85 ] && [ $GRADE -le 100 ]
then 
    echo "excelent"
elif [ $GRADE -ge 70 ] && [ $GRADE -le 85 ]
then
    echo "pass"
else 
    echo "not pass"
fi