echo "Creating webbuild folder"
mkdir webbuild
echo "going to webbuild folder"
cd webbuild
echo "First cmake (emscripten sdk should be in your path)"
call emcmake cmake ..
echo "ninja build (building with ninja because it works.)"
ninja
echo "done."
cd ..
