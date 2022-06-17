#/bin/sh
extension="glsl"
compileFragment(){
    for file in $(find ./sources/Shader/fragment -name *.$extension); do
        printf "\e[1;36m[Compilation][Shaders][fragment]\e[0m $file\n"
        /usr/bin/glslc -fshader-stage="fragment" "$file" -o "${file%%.$extension}.spv"
    done
}
compileShader(){
    for file in $(find ./sources/Shader/vertex -name *.$extension); do
        printf "\e[1;36m[Compilation][Shaders][vertex]\e[0m $file\n"
        /usr/bin/glslc -fshader-stage="vertex" "$file" -o "${file%%.$extension}.spv"
    done
}

compileFragment
compileShader
