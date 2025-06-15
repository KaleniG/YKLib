pushd ..
Scripts/Premake/Linux/premake5 --file=premake5.lua gmake
if [ $? -ne 0 ]; then
    read -p "Premake5 failed. Press Enter to continue..."
fi
popd