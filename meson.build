project('The Word', 'cpp', version: 'Stable 2.0.1')

cmake = import('cmake')

opt_var = cmake.subproject_options()
opt_var.add_cmake_defines({
    'ENABLE_LIB_ONLY': true
})

ziplib = cmake.subproject('ZipLib')
ziplib_dep = ziplib.dependency('ZipLib')

bz2 = cmake.subproject('bzip2', options: opt_var)
bz2_target = bz2.target('bz2')

lzma = cmake.subproject('plzmaSDK')
lzma_dep = lzma.dependency('plzma')

zlib_dep = dependency('zlib')

executable('main', 'src/main.cpp', 'src/files.cpp', include_directories: 'Include/', dependencies: [ziplib_dep, lzma_dep, zlib_dep], link_with: bz2_target)