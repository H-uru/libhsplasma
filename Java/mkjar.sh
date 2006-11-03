#!/bin/bash

echo " * Compiling Plasma.CoreLib"
javac Plasma/CoreLib/*.java
echo
echo " * Compiling Plasma.DynLib"
javac Plasma/DynLib/*.java
echo
echo " * Compiling Plasma.NucleusLib.pnKeyedObject"
javac Plasma/NucleusLib/pnKeyedObject/*.java
echo
echo " * Compiling Plasma.NucleusLib.pnMessage"
javac Plasma/NucleusLib/pnMessage/*.java
echo
echo " * Compiling Plasma.NucleusLib.pnNetCommon"
javac Plasma/NucleusLib/pnNetCommon/*.java
echo
echo " * Compiling Plasma.PubUtilLib.plGImage"
javac Plasma/PubUtilLib/plGImage/*.java
echo
echo " * Compiling Plasma"
javac Plasma/*.java
echo
echo " * Making Plasma.jar"
jar cf Plasma.jar Plasma/*.class Plasma/CoreLib/*.class Plasma/DynLib/*.class \
       Plasma/NucleusLib/pnKeyedObject/*.class \
       Plasma/NucleusLib/pnMessage/*.class \
       Plasma/NucleusLib/pnNetCommon/*.class \
       Plasma/PubUtilLib/plGImage/*.class
echo

