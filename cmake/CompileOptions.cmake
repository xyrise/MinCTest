if (MSVC)
  add_compile_options (
    /Wall
    /WX
    /wd4710
    /wd4711
    /wd5045
    /wd4820
    /wd4706
    /wd4255
    /wd4090
    /Qspectre
  )
  add_definitions (-D_CRT_SECURE_NO_WARNINGS)
else()
  add_compile_options (
    -Wall
    -Wextra
    -pedantic
    -Werror
  )
endif()
