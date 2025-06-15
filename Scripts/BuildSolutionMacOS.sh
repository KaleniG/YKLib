pushd ..
Scripts/Premake/MacOS/premake5 --file=premake5.lua xcode4
if [ $? -ne 0 ]; then
    read -p "Premake5 failed. Press Enter to continue..."
fi
popd