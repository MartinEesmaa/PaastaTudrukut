#!/bin/bash

modify_source_code() {

    if [ ! -d "romfs" ]; then
        mkdir romfs
    fi

    cp -rf fondid romfs
    cp -rf pilt romfs
    cp -rf sfx romfs
    cp -rf muusika romfs

    if [ ! -d "source" ]; then
        mkdir source
    fi
    cp paastatudrukut.cpp source/paastatudrukut.cpp

    sed -i 's|fondid/|romfs:/fondid/|g' source/paastatudrukut.cpp
    sed -i 's|pilt/|romfs:/pilt/|g' source/paastatudrukut.cpp
    sed -i 's|sfx/|romfs:/sfx/|g' source/paastatudrukut.cpp
    sed -i 's|muusika/|romfs:/muusika/|g' source/paastatudrukut.cpp
}

revert_source_code() {
    rm -rf failid
    if [ -f source/paastatudrukut.cpp ]; then
        rm source/paastatudrukut.cpp
    fi
    rm -rf source
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
