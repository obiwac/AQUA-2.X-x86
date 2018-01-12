
#!/bin/bash

mkdir -p cross_compiler
cd cross_compiler/

mkdir -p src/
cd src/

wget ftp://ftp.gnu.org/gnu/binutils/binutils-2.29.1.tar.gz
wget ftp://ftp.gnu.org/gnu/gcc/gcc-7.2.0/gcc-7.2.0.tar.gz

tar -xzf binutils-2.29.1.tar.gz
tar -xzf gcc-7.2.0.tar.gz

cd ..
mkdir -p opt/cross/ 

export PREFIX="$(pwd)/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

cd src/
mkdir build-binutils/
cd build-binutils/

../binutils-2.29.1/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror

make
make install

which -- $TARGET-as || echo "$TARGET-as is not in the PATH ..."

cd ..
mkdir build-gcc/
cd build-gcc/

../gcc-7.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers

make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

cd ../..

echo -n "Please copy `export PATH=\"$(pwd)/opt/cross/bin:$PATH\"` to the end of the upcoming file [press enter to continue] ..."
read a

nano ~/.profile
exit;
