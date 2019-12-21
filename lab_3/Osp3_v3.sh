#!/bin/bash
file=`ls -ln $1`

print_all_users()
{
        cat /etc/passwd | awk -F: '{print $1}'
}
print_group_users()
{
        cat /etc/passwd | grep $1 | awk -F: '{print $1}'
}
print_user()
{
        ls -l $1 | awk '{print $3;}'
}

acces_mode=`echo $file | awk '{print $1;}'`
uid=`echo $file | awk '{print $3;}'`
gid=`echo $file | awk '{print $4;}'`

user_possibility=${acces_mode:3:1}
group_possibility=${acces_mode:6:1}
all_possibility=${acces_mode:9:1}

if [[ "$all_possibility" ==  "x" ]]; then
        print_all_users
elif [[ "$group_possibility" == "x" ]]; then
        print_group_users $gid
elif [[ "$user_possibility" == "x" ]]; then
        print_user $1
fi
