TOKENIZERS_LIBRARY_PATH=$1
CMAKE_BUILD_TYPE=$2

LIB_DIR=$TOKENIZERS_LIBRARY_PATH/bindings/cpp/target/$CMAKE_BUILD_TYPE/build

# echo "Creating symlink for cxxbridge"
find $LIB_DIR -name "libcxxbridge1.a" | xargs ln -sf
if [ -L "libcxxbridge1.a" ]; then
	mv "libcxxbridge1.a" $LIB_DIR
	# echo "Symlink created at $LIB_DIR/libcxxbridge1.a"
fi

# echo "Creating symlink for tokenizers-cpp"
find $LIB_DIR -name 'libtokenizers-cpp.a' | xargs ln -sf
if [ -L "libtokenizers-cpp.a" ]; then
	mv "libtokenizers-cpp.a" $LIB_DIR
	# echo "Symlink created at $LIB_DIR/libtokenizers-cpp.a"
fi
