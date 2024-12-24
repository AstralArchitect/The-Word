all: compile

compile:
	meson compile -C builddir/
run: compile
	builddir/main
setup:
	meson setup builddir/
runC: compile
	builddir/main cheat
clean:
	rm -rf builddir/ subprojects/bzip2/ subprojects/plzmaSDK/ subprojects/ziplib/