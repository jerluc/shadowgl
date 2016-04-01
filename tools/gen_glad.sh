#!/bin/bash

OUTPUTDIR=libs/glad

# Install/upgrade glad
pip install --upgrade git+https://github.com/dav1dde/glad.git#egg=glad

# Remove the (maybe) existing directories
rm -rf $OUTPUTDIR

# Actually generate the OpenGL loader
glad --generator=c --out-path=$OUTPUTDIR
