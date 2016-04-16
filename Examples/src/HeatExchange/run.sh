#!/bin/bash
make main

mv parametersRn.pot parameters.pot
./main
mv parameters.pot parametersRn.pot

mv parametersL2.pot parameters.pot
./main
mv parameters.pot parametersL2.pot

mv parametersH1.pot parameters.pot
./main
mv parameters.pot parametersH1.pot