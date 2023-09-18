BUILD_DIR=./build
MODULE_DIR=./drv

#DEFAULT_ARCH=arm
#DEFAULT_CROSS_COMPILE=~/workspace/drivers/100ask_imx6ull_mini-sdk\
#/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin\
#/arm-buildroot-linux-gnueabihf-

echo -e "[INFO] " "\033[32mMake Start\033[0m"
PARAM1="$1"

# Cleaning project
if [ "$PARAM1" == "clean" ]; then
  echo -e "[INFO] " "\033[32mCleaning project...\033[0m"
  rm -rf $BUILD_DIR
  rm -rf ./*.exe ./*.ko
  for dir in ./drv*/
  do
    cd "$dir" || exit
    make clean
    cd ..
  done
  echo -e "[INFO] " "\033[32mMake Done\033[0m"
  exit
else
  # Selecting driver path
  if [ -n "$PARAM1" ]; then
    if [ -d "$PARAM1" ]; then
        MODULE_DIR=$PARAM1
      else
        echo -e "[ERROR] " "\033[31mDriver path is error\033[0m"
        exit
    fi
  fi
fi

# Check tool chain
#if [ -z "$ARCH" ]; then
#  echo -e "[WARN] " "\033[33mARCH is not set...\033[0m"
#  export ARCH=$DEFAULT_ARCH
#  echo -e "[INFO] " "\033[32mARCH was set to\033[0m" "\"$ARCH\""
#fi
#if [ -z "$CROSS_COMPILE" ]; then
#  echo -e "[WARN] " "\033[33mCROSS_COMPILE is not set...\033[0m"
#  export CROSS_COMPILE=$DEFAULT_CROSS_COMPILE
#  echo -e "[INFO] " "\033[32mCROSS_COMPILE was set to \033[0m" "\"$CROSS_COMPILE\""
#fi

# Creating build directory
if [ -d "$BUILD_DIR" ]; then
  echo -e "[INFO] " "\033[32mBuild directory is ready...\033[0m"
else
  echo -e "[INFO] " "\033[32mCreating build directory...\033[0m"
  mkdir build
fi

cd "$BUILD_DIR" || exit
cmake ..
cd ..

# Make
make -C $BUILD_DIR
if [ "$PARAM1" == "app" ]; then
  echo -e "[INFO] " "\033[32mMake App Done\033[0m"
  cp $BUILD_DIR/*.exe ./
  exit
fi
make -C $MODULE_DIR

# Copying output file
cp $BUILD_DIR/*.exe ./
cp $MODULE_DIR/*.ko ./

echo -e "[INFO] " "\033[32mMODULE_DIR: $MODULE_DIR\033[0m"
echo -e "[INFO] " "\033[32mMake Done\033[0m"
