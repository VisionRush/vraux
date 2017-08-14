# ***************************
# Dynamic link library model
# ***************************
# mkdir
mkdir -p .local/include
mkdir -p .local/lib
# copy header & file files
cp -rf ../include/vraux $HOME/.local/include/
cp -rf libvraux.so.0.1.5 $HOME/.local/lib/
cd $HOME/.local/lib
ln -s libvraux.so.0.1.5 libvraux.so.0 
ln -s libvraux.so.0 libvraux.so		  



# set env-var
export CPLUS_INCLUDE_PATH=$HOME/.local/include:$CPLUS_INCLUDE_PATH
export LIBRARY_PATH=$HOME/.local/lib:$LIBRARY_PATH
echo "you should modify .bash_profile: add $HOME/.local/include into CPLUS_INCLUDE_PATH"
echo "you should modify .bash_profile: add $HOME/.local/lib     into LIBRARY_PATH"