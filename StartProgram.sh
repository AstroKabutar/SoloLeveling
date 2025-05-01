#! /bin/bash

clear

# upping the mysql docker
#docker compose up -d

# trigger cmake compilation
#rm -r build
mkdir -p build
cd build
cmake ..
make

# delay for letting the database to start
time=3;

# waiting time for the mysql docker container to start up
for((i=time; ; --i)); do
    if((i == 0)); then
        echo "Starting Application...";
        break;
    fi

    echo -ne "Starting Application in ...${i} sec [/] \r";
    sleep 0.2;
    echo -ne "Starting Application in ...${i} sec [-] \r";
    sleep 0.2;
    echo -ne "Starting Application in ...${i} sec [|] \r";
    sleep 0.2;
    echo -ne "Starting Application in ...${i} sec [-] \r";
    sleep 0.2;
    echo -ne "Starting Application in ...${i} sec [\\] \r";
    sleep 0.2;


done

cd ..

rm SoloLeveling
mv ./build/SoloLeveling .

# begin running the executable
#cp build/SoloLeveling .
#source ENV/Mysql.env
#./build/SoloLeveling
#valgrind ./build/SoloLeveling

# cleaning up
#docker compose down
