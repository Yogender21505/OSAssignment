cd linux-5.19.9
make mrproper
lynx is.am/56er
mv config-rev-9-gold .config
make nconfig
make
make -C /lib/modules/5.19.9/source && make -j $(nproc)