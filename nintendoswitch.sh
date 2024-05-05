#!/bin/bash

modify_source_code() {
    sed -i 's|fondid/|romfs:/fondid/|g' paastatudrukut.cpp
    sed -i 's|pilt/|romfs:/pilt/|g' paastatudrukut.cpp
    sed -i 's|sfx/|romfs:/sfx/|g' paastatudrukut.cpp
    sed -i 's|muusika/|romfs:/muusika/|g' paastatudrukut.cpp
}

revert_source_code() {
    sed -i 's|romfs:/fondid/|fondid/|g' paastatudrukut.cpp
    sed -i 's|romfs:/pilt/|pilt/|g' paastatudrukut.cpp
    sed -i 's|romfs:/sfx/|sfx/|g' paastatudrukut.cpp
    sed -i 's|romfs:/muusika/|muusika/|g' paastatudrukut.cpp
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
