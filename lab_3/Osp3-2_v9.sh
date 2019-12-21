#!/bin/bash
files=`ls`

arg_uid=`getent passwd $1 | awk -F: '{print $3;}'`
arg_gid=`getent passwd $1 | awk -F: '{print $4;}'`

for file in $files
do

        acces_mode=`ls -ln $file | awk '{print $1;}'`
        uid=`ls -ln $file | awk '{print $3;}'`
        gid=`ls -ln $file | awk '{print $4;}'`

        user_possibility=${acces_mode:3:1}
        group_possibility=${acces_mode:6:1}
        all_possibility=${acces_mode:9:1}

        if [[ "$uid" ==  "$arg_uid" ]] && [[ "$user_possibility" == "x" ]]; then
                echo $file
        elif [[ "$gid" == "$arg_uid" ]] && [[ "$group_possibility" == "x" ]]; then
                echo $file
        elif [[ "$all_possibility" == "x" ]]; then
                echo $file
        fi
done
