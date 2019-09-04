project (Kasa)

set(CMAKE_C_FLAGS "-fshort-wchar -fPIC -DHAVE_CONFIG_H -O0 -DNDEBUG")
set(CMAKE_CXX_FLAGS "-std=c++17 -fshort-wchar -frtti -fPIC -fexceptions -O0 -DNDEBUG" )

set(SRC_LIST
    ast.cpp
    interpreter.cpp
    kasa_assert.cpp
    kasa_log.cpp
    kasa.tab.cpp
    lex.cpp
    main.cpp
    object_code.cpp
    object.cpp
    
    ast.h
    interpreter.h
    kasa_assert.h
    kasa_log.h
    kasa.tab.hpp
    object_code.h
    object.h
    opcode.h
)

add_executable(Kasa ${SRC_LIST} )
