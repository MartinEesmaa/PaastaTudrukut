#!/bin/bash

modify_source_code() {

    if [ ! -d "romfailid" ]; then
        mkdir romfailid
    fi

    cp -rf fondid/* romfailid
    cp -rf pilt/* romfailid
    cp -rf muusika/* romfailid
    cp -rf fondid/* romfailid

    cp paastatudrukut.cpp paastatudrukut-varu.cpp

    sed -i 's|fondid/|romfs:/romfailid/|g' paastatudrukut.cpp
    sed -i 's|pilt/|romfs:/romfailid/|g' paastatudrukut.cpp
    sed -i 's|sfx/|romfs:/romfailid/|g' paastatudrukut.cpp
    sed -i 's|muusika/|romfs:/romfailid/|g' paastatudrukut.cpp
}

revert_source_code() {
    rm -rf romfailid
    if [ -f paastatudrukut-varu.cpp ]; then
        mv paastatudrukut-varu.cpp paastatudrukut.cpp
    fi
}

handle_cancel() {
    echo "Katkestatud, tagasi..."
    if [ -f Makefile.bak ]; then
        mv Makefile Makefile.NX
        mv Makefile.bak Makefile
    fi
    revert_source_code
    exit 1
}

mv -n Makefile Makefile.bak
mv -n Makefile.NX Makefile

trap handle_cancel INT TERM

modify_source_code

if ! make PLATFORM=PLATFORM_NX; then
    echo "Make vigu. Tagasi..."
    if [ -f Makefile.bak ]; then
        mv Makefile Makefile.NX
        mv Makefile.bak Makefile
    fi
    revert_source_code
    exit 1
fi

revert_source_code

if [ -f Makefile.bak ]; then
    mv Makefile Makefile.NX
    mv Makefile.bak Makefile
fi
