project('The Word', 'cpp', version: 'Stable 1.0.0')

cmake = import('cmake')
ziplib = cmake.subproject('ZipLib')
ziplib_dep = ziplib.dependency('ZipLib')
bz2 = cmake.subproject('bzip2')
bzip2 = bz2.dependency('libbzip2')

lzma_dep = dependency('liblzma')
zlib_dep = dependency('zlib')

message('CMake targets:\n - ' + '\n - '.join(bz2.target_list()))

executable('main', 'src/main.cpp', 'src/files.cpp', include_directories: 'Include/', dependencies: [ziplib_dep, lzma_dep, zlib_dep, bzip2])