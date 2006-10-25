#!/bin/bash

echo " * Compiling Plasma.CoreLib.*"
javac Plasma/CoreLib/*.java
echo
echo " * Compiling Plasma.DynLib.*"
javac Plasma/DynLib/*.java
echo
echo " * Compiling Plasma.*"
javac Plasma/*.java
echo
echo " * Making Plasma.jar"
jar cf Plasma.jar Plasma/*.class Plasma/CoreLib/*.class Plasma/DynLib/*.class
echo

