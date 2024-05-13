import glob
import subprocess
import os
import mmap

def findInFile(filename,string):
    with open(filename,"rb",0) as f:
        s = mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ)
        if s.find(bytes(string,"utf-8")) != -1:
            return True
        else:
            return False

for filename in glob.iglob("cpp"+"**/**/CMakeLists.txt",recursive=True):   
    os.remove(filename)

main_cmake = f = open("CMakeLists.txt", "w")
f.write("""# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)\n
""")
f.write("cmake_minimum_required(VERSION 3.17)\n\n")
f.write("""project(Examples
DESCRIPTION "Book examples"
LANGUAGES CXX)\n""")
f.write("SET(WITH_MPI OFF CACHE BOOL \"Build MPI example\")\n")
f.write("SET(WITH_HPX OFF CACHE BOOL \"Build HPX examples\")\n")
f.write("include(CTest)\n")
f.write("add_subdirectory(cpp)\n")
f.write("include(CheckCXXCompilerFlag)\n\n")
f.write("check_cxx_compiler_flag(-std=c++20 HAVE_FLAG_STD_CXX20)\n\n")
f.write("""if(${WITH_MPI})
    find_package(MPI REQUIRED COMPONENTS CXX )
endif()""")
f.close()

folders = set()

for filename in glob.iglob("cpp"+"**/**/*.cpp",recursive=True):
    filepath = filename.replace("cpp/","")
    name = filename.split("/")[2]
    exe = name.replace(".cpp","")
    folder = filepath.split("/")[0]
    folders.add(folder)

    file = open("cpp/"+folder+"/CMakeLists.txt","a")
    
    if findInFile(filename,"mpi.h"):
        file.write("if(${WITH_MPI})\n")
        command="add_executable(" + exe + " " + name + ")\n"
        file.write("\t"+command)
        if findInFile(filename,"pbm.hpp") or findInFile(filename,"config.hpp"):
            file.write("target_include_directories("+exe+" PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)\n\n")
        file.write("endif()\n")
    elif findInFile(filename,"hpx.hpp"):
        file.write("if(${WITH_HPX})\n")
        file.write("\t# add hpx compile\n")
        if findInFile(filename,"pbm.hpp"):
            file.write("target_include_directories("+exe+" PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)\n\n")
        file.write("endif()\n")
    else:
        if findInFile(filename,"std::views") or findInFile(filename,"for (int index = 0; const int value : values)"):
            file.write("if(\"${HAVE_FLAG_STD_CXX20}\" AND NOT (\"${CMAKE_CXX_COMPILER_ID}\" MATCHES \"Clang\"))\n")
            command="add_executable(" + exe + " " + name + ")\n"
            file.write(command)
            file.write("SET_PROPERTY(TARGET "+exe+" PROPERTY CXX_STANDARD 20)\n")
            file.write("endif()\n")
        else:
            command="add_executable(" + exe + " " + name + ")\n"
            file.write(command)
        if findInFile(filename,"pbm.hpp"):
            file.write("target_include_directories("+exe+" PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)\n\n")

    file.close()
    #print(filename,name,exe,folder)

file = open("cpp/CMakeLists.txt","w")
for folder in folders:
    file.write("add_subdirectory("  + folder + ")\n")
file.close()
