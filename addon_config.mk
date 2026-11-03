# ofxPDSP addon configuration.
#
# Dependencies (clone them next to ofxPDSP in openFrameworks/addons):
#   ofxAudioFile  https://github.com/npisanti/ofxAudioFile   (sample loading)
#   ofxMidi       https://github.com/danomatika/ofxMidi      (midi in/out)
#   ofxOsc        bundled with openFrameworks                 (osc in/out)
#
# All platform flags live here, so projects (makefiles or the project
# generator) need no extra settings. Every source file includes what it uses.

meta:
	ADDON_NAME = ofxPDSP
	ADDON_DESCRIPTION = Patchable DSP library addon for openFrameworks
	ADDON_AUTHOR = Nicola Pisanti
	ADDON_TAGS = "audio" "synthesis" "music" "dsp" "sound"
	ADDON_URL = http://github.com/npisanti/ofxPDSP

common:
	ADDON_DEPENDENCIES = ofxAudioFile ofxMidi ofxOsc

linux64:

linux:

# Raspberry Pi OS 64 bit (Pi 3/4/5, Bookworm/Trixie). NEON is part of the
# ARMv8 baseline and enabled by the compiler automatically; -mfpu is not a
# valid option on aarch64, so no flags are needed.
linuxaarch64:

msys2:
	ADDON_CFLAGS = -msse2 -mstackrealign

vs:

linuxarmv6l:
	# ofxSIMDFloats is not useful without NEON, this flags are for running it on a raspbian rpi2
	ADDON_CFLAGS = -mfpu=neon -mfloat-abi=hard -ftree-vectorize

linuxarmv7l:
	# enable NEON as is not enabled by default, i'm assuming this is a raspberry Pi / other ARMhf
	ADDON_CFLAGS = -march=armv7-a -mfpu=neon -mfloat-abi=hard -ftree-vectorize

android/armeabi:

android/armeabi-v7a:
	# make sure NEON is enabled
	ADDON_CFLAGS = -mfpu=neon

osx:

ios:
