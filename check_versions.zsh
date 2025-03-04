echo Listing of available conan package versions
conan search opencascade -r=conancenter
conan search imgui -r=conancenter
conan search gtest -r=conancenter
conan search immer -r=conancenter
conan search pugixml
conan search spdlog
echo Compare with conanfile.py requires listing
cat conanfile.py | grep 'self.requires'
echo Listing of brew installed packages
brew --prefix coin3d
