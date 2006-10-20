#!/bin/bash

javac Plasma/*.java
javac Plasma/CoreLib/*.java
jar cf Plasma.jar Plasma/*.class Plasma/CoreLib/*.class

