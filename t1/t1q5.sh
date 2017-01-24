#!/bin/bash
ARG1="$1"
if [ "$ARG1" == "loop" ]
    then
    for i in {1..5}
    do
        echo $i >> count.log
        echo $ARG1
    done;
fi

ps > process.log