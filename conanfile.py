from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class cadanceRecipe(ConanFile):
    name = "cadance"
    version = "0.0"
    package_type = "application"

    # Optional metadata
    license = "Create Commons Zero 1.0"
    author = "Kjell-Olov Högdahl kjell-olov.hogdahl@itfied.se"
    url = "https://github.com/kjelloh/cadance.git"
    description = "A CAD / CAM initiative based on Immutable data model, ELM architecture and key-input based effective non window based UX"
    topics = ("CAD", "CAM", "The Elm Architecture", "TEA", "Open Cascade", "Coin3D", "ImGui", "Immer")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    

    
