TOKENIZERS_LIBRARY_PATH=$1
CMAKE_BUILD_TYPE=$2

LIB_DIR=$TOKENIZERS_LIBRARY_PATH/bindings/cpp/target/$CMAKE_BUILD_TYPE
BUILD_DIR=$LIB_DIR/build

find $BUILD_DIR -name "libcxxbridge1.a" | xargs ln -sf
if [ -L "libcxxbridge1.a" ]; then
	mv "libcxxbridge1.a" $LIB_DIR
fi

find $BUILD_DIR -name 'libtokenizers-cpp.a' | xargs ln -sf
if [ -L "libtokenizers-cpp.a" ]; then
	mv "libtokenizers-cpp.a" $LIB_DIR
fi

find $BUILD_DIR -type d -regex ".*/tokenizers-cpp-.*?/include/tokenizers-cpp" | xargs ln -sf
if [ -L "tokenizers-cpp" ]; then
	mv "tokenizers-cpp" $LIB_DIR
fi
