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
echo " * Compiling Plasma.NucleusLib.pnSceneObject"
javac Plasma/NucleusLib/pnSceneObject/*.java
echo
echo " * Compiling Plasma.PubUtilLib.plAvatar"
javac Plasma/PubUtilLib/plAvatar/*.java
echo
echo " * Compiling Plasma.PubUtilLib.plDrawable"
javac Plasma/PubUtilLib/plDrawable/*.java
echo
echo " * Compiling Plasma.PubUtilLib.plGImage"
javac Plasma/PubUtilLib/plGImage/*.java
echo
echo " * Compiling Plasma.PubUtilLib.plScene"
javac Plasma/PubUtilLib/plScene/*.java
echo
echo " * Compiling Plasma.PubUtilLib.plSurface"
javac Plasma/PubUtilLib/plSurface/*.java
echo
echo " * Compiling Plasma"
javac Plasma/*.java
echo
echo " * Making Plasma.jar"
jar cf Plasma.jar Plasma/*.class Plasma/CoreLib/*.class Plasma/DynLib/*.class \
       Plasma/NucleusLib/pnKeyedObject/*.class \
       Plasma/NucleusLib/pnMessage/*.class \
       Plasma/NucleusLib/pnNetCommon/*.class \
       Plasma/NucleusLib/pnSceneObject/*.class \
       Plasma/PubUtilLib/plAvatar/*.class \
       Plasma/PubUtilLib/plDrawable/*.class \
       Plasma/PubUtilLib/plGImage/*.class \
       Plasma/PubUtilLib/plScene/*.class \
       Plasma/PubUtilLib/plSurface/*.class
echo

