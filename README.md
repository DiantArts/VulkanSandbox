# Vulkan sandbox
Small scale game engine to learn vulkan and multi player game engines

# How to run
Run the following commands to install the dependencies (ubuntu-22.04 example):
```
apt-get install -y python3-pip cppcheck clang-tidy ccache moreutils cmake gcovr llvm
```
```
pip install conan ninja
```

Launch the server first (compiling the client first prevent the compilation of the server - sorry):
```
./.toolchain/compile --server
```
Launch the client
```
./.toolchain/compile
```

Use `-d` to enable debug.
