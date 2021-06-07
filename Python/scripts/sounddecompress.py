#!/usr/bin/env python

# This file is part of HSPlasma.
#
# HSPlasma is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# HSPlasma is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.

"""sounddecompress.py

    A Utility for decompressing Uru audio
    by Joseph Davies (deledrius@gmail.com)

  * Requires sox (http://sox.sourceforge.net/)
  * Requires libHSPlasma and PyHSPlasma (https://github.com/H-uru/libhsplasma
    with Python support.)

  Usage:
    ./sounddecompress.py -u /path/to/uru
        (Override base Uru using the default subdirectories)
    ./sounddecompress.py -d /path/to/agefiles -s /path/to/oggs -c /path/to/outputwavs
        (Override default subdirectories)
    ./sounddecompress.py -u /path/to/uru -c /path/to/outputwavs
        (Override base Uru and output directory only)
"""

import os
import sys
import glob
import math
import subprocess
from xml.dom.minidom import parse, getDOMImplementation
from optparse import OptionParser, OptionGroup

try:
    import PyHSPlasma
except ImportError as e:
    libPlasma = False
else:
    libPlasma = True


version = 1.11

## Default Paths
DefaultUruDir = "."
DefaultDataDir = "dat"
DefaultSFXDir = "sfx"
DefaultCacheDir = os.path.join(DefaultSFXDir,"streamingCache")


## Initialize empty queue of sound files to decompress
queue = {}


def getDecompressQueue(datadir):
    if not libPlasma:
        print("\nFatal Error: PyHSPlasma module not loaded.  Reading of Age files unavailable.")
        return False
    ## Only display Errors
    PyHSPlasma.plDebug.Init(PyHSPlasma.plDebug.kDLError)

    ## Create our Resource Manager
    plResMgr = PyHSPlasma.plResManager()

    ## Get Age list for progress
    print("Loading Age files...")
    numAges = len(glob.glob(os.path.join(datadir, "*.age")))
    numAgesRead = 0
    if numAges == 0:
        print("No Age files found.  Quitting.")
        return False

    print("{0} Ages found in {1}.\nScanning...".format(numAges, datadir))

    ## Flip through all ages
    progress(50, float(numAgesRead)/float(numAges) * 100)
    for ageFile in glob.iglob(os.path.join(datadir,"*.age")):
        fullpath = os.path.abspath(ageFile)

        try:
            age = plResMgr.ReadAge(fullpath, True)
        except IOError as e:
            print("Warning - Unable to read Age: {0}".format(ageFile), file=sys.stderr)
        except KeyboardInterrupt:
            print("\nInterrupt detected. Aborting.")
            return False
        else:
            try:
                ## Get the plSoundBuffer in each page and queue sounds
                ##  which are not set to StreamCompressed
                for pageNum in range(0, age.getNumPages()):
                    page = plResMgr.FindPage(age.getPageLoc(pageNum, plResMgr.getVer()))
                    if (page == None):
                        raise Exception("Unable to completely load age "+age.name+": Can't find page "+str(age.getPageLoc(pageNum, plResMgr.getVer())))
                    if PyHSPlasma.plFactory.kSoundBuffer in plResMgr.getTypes(page.location):
                        for key in plResMgr.getKeys(page.location, PyHSPlasma.plFactory.kSoundBuffer):
                            soundBuffer = key.object

                            if soundBuffer.fileName in queue.keys():
                                channelOptions = queue[soundBuffer.fileName]
                            else:
                                channelOptions = {}

                            if (soundBuffer.flags & soundBuffer.kOnlyRightChannel):
                                channel = channelOptions["Right"] = True
                            if (soundBuffer.flags & soundBuffer.kOnlyLeftChannel):
                                channel = channelOptions["Left"] = True
                            if channelOptions == {}:
                                channelOptions["Both"] = True

                            if not (soundBuffer.flags & soundBuffer.kStreamCompressed):
                                queue[soundBuffer.fileName] = channelOptions
            except MemoryError as e:
                print("\nFatal Error - Unable to process Age ({0}) - {1}".format(age.name, e), file=sys.stderr)
                return False
            except KeyboardInterrupt:
                print("\nInterrupt detected. Aborting.")
                return False

            plResMgr.UnloadAge(age.name)

        ## Onto the next
        numAgesRead = numAgesRead + 1
        progress(50, float(numAgesRead)/float(numAges) * 100)

    print("{0} sound files added to queue.".format(len(queue)))
    return True


def doDecompress(sfxdir, cachedir):
    ## Make sure the cache dir exists
    if not os.path.exists(os.path.abspath(cachedir)):
        print("Creating streamingCache directory.")
        os.mkdir(cachedir)

    ## Prepare progress
    print("Decompressing audio files...")
    numFilesProcessed = 0
    numFiles = len(queue)

    ## Flip through all sound files
    progress(50, float(numFilesProcessed)/float(numFiles) * 100)
    for oggFile in queue.keys():
        inpath = os.path.abspath(os.path.join(sfxdir, oggFile))
        if os.path.exists(inpath):
            for channel in queue[oggFile]:
                if channel == "Both":
                    wavFile = oggFile.split('.')[0] + ".wav"
                    soxCommand = "sox \"{0}\" \"{1}\""
                elif channel == "Left":
                    wavFile = oggFile.split('.')[0] + "-Left.wav"
                    soxCommand = "sox \"{0}\" -c 1 \"{1}\" mixer -l"
                elif channel == "Right":
                    wavFile = oggFile.split('.')[0] + "-Right.wav"
                    soxCommand = "sox \"{0}\" -c 1 \"{1}\" mixer -r"

                outpath = os.path.abspath(os.path.join(cachedir, wavFile))
                soxCommand = soxCommand.format(inpath, outpath)

                ## Conversion from OGG to WAV
                try:
                    retcode = subprocess.check_call(soxCommand, shell=True, stderr=open(os.devnull,"w"))
                except subprocess.CalledProcessError as e:
                    print("\nFatal Error - Unable to execute Sox!\n", file=sys.stderr)
                    return False
                except OSError as e:
                    print("\nFatal Error - Unable to execute Sox!\n", file=sys.stderr)
                    return False
                except KeyboardInterrupt:
                    print("\nInterrupt detected. Aborting.")
                    return False

        ## Onto the next
        numFilesProcessed = numFilesProcessed + 1
        progress(50, float(numFilesProcessed)/float(numFiles) * 100)
    return True

## XML Queue Writer
def writeQueueToXML(outfile):
    print("Writing queue to xml: {0}".format(outfile))
    root = getDOMImplementation().createDocument(None, "conversionlist", None)
    with open(os.path.abspath(outfile), "w") as xmlfile:
        print("Writing XML file \"{0}\"".format(outfile))
        root.documentElement.setAttribute("version", str(version))
        root.documentElement.setAttribute("game", "Unknown")
        root.documentElement.setAttribute("gamebuild", "Unknown")

        numFilesProcessed = 0
        numFiles = len(queue)
        progress(50, float(numFilesProcessed)/float(numFiles) * 100)
        for soundfile in queue.keys():
            sfNode = root.createElement("soundfile")
            sfNode.setAttribute("name", soundfile)
            coNode = root.createElement("channeloutputs")
            coNode.setAttribute("stereo", str("Both" in queue[soundfile] and queue[soundfile]["Both"]))
            coNode.setAttribute("left", str("Left" in queue[soundfile] and queue[soundfile]["Left"]))
            coNode.setAttribute("right", str("Right" in queue[soundfile] and queue[soundfile]["Right"]))
            sfNode.appendChild(coNode)
            root.documentElement.appendChild(sfNode)

            numFilesProcessed = numFilesProcessed + 1
            progress(50, float(numFilesProcessed)/float(numFiles) * 100)
        root.writexml(xmlfile, addindent="\t", newl="\n", encoding="utf-8")

## XML Queue Reader
def readQueueFromXML(infile):
    print("Reading queue from xml: {0}".format(infile))
    queueXML = minidom.parse(infile)
    soundfiles = queueXML.getElementsByTagName("soundfile")

    numFilesProcessed = 0
    numFiles = len(soundfiles)
    progress(50, float(numFilesProcessed)/float(numFiles) * 100)

    for soundfile in soundfiles:
        channelOptions = {}
        channelXML = soundfile.getElementsByTagName("channeloutputs")
        for channelNode in channelXML:
            if "stereo" in channelNode.attributes.keys() and channelNode.attributes["stereo"].value == "True":
                channelOptions["Both"] = True
            if "left" in channelNode.attributes.keys() and channelNode.attributes["left"].value == "True":
                channelOptions["Left"] = True
            if "right" in channelNode.attributes.keys() and channelNode.attributes["right"].value == "True":
                channelOptions["Right"] = True
        queue[soundfile.attributes["name"].value] = channelOptions

        numFilesProcessed = numFilesProcessed + 1
        progress(50, float(numFilesProcessed)/float(numFiles) * 100)

    print("{0} sound files added to queue.".format(len(queue)))
    return True

## Handy Progress Meter
def progress(width, percent):
    marks = math.floor(width * (percent / 100.0))
    spaces = math.floor(width - marks)

    loader = '[ ' + ('=' * int(marks)) + (' ' * int(spaces)) + ' ]'

    sys.stdout.write("%s %d%%\r" % (loader, percent))
    if percent >= 100:
        sys.stdout.write("\n")
    sys.stdout.flush()

if __name__ == '__main__':
    parser = OptionParser(usage="usage: %prog [options]", version="%prog {0}".format(version))
    parser.add_option("-q", "--quiet", dest="verbose", default=True, action="store_false", help="Don't print status messages")

    pathgroup = OptionGroup(parser, "Path Output Options")
    pathgroup.add_option("-u", "--uru", dest="urudir", default=DefaultUruDir, help="Sets base path for Uru.")
    pathgroup.add_option("-d", "--data", dest="datadir", help="Override path for input data files.")
    pathgroup.add_option("-s", "--sfx", dest="sfxdir", help="Override path for input sound files.")
    pathgroup.add_option("-c", "--cache", dest="cachedir", help="Override path for output sound files.")
    parser.add_option_group(pathgroup)

    xmlgroup = OptionGroup(parser, "XML Output Options", "")
    xmlgroup.add_option("--xml", dest="xml", default=False, action="store_true", help="Dump queue to XML after Age processing and audio conversion.")
    xmlgroup.add_option("--xmlonly", dest="xmlonly", default=False, action="store_true", help="Don't convert audio after Age processing, only dump XML.")
    xmlgroup.add_option("--xmlof", dest="xmloutfile", metavar="OUTFILE", default="wavlist.xml", help="File to dump queue to after processing if --xml or --xmlonly option is specified.")
    xmlgroup.add_option("--xmlin", dest="xmlinfile", metavar="INFILE", help="Use specified XML file instead of local Age files, then do audio conversion.")
    parser.add_option_group(xmlgroup)

    (options, args) = parser.parse_args()

    ## Send output to OS's null if unwanted
    if not options.verbose:
        sys.stdout = open(os.devnull,"w")
        sys.stderr = open(os.devnull,"w")

    ## Compute Paths
    basedir = os.path.expanduser(options.urudir)
    datadir = os.path.join(basedir, DefaultDataDir)
    sfxdir = os.path.join(basedir, DefaultSFXDir)
    cachedir = os.path.join(basedir, DefaultCacheDir)
    if options.datadir: datadir = os.path.expanduser(options.datadir)
    if options.sfxdir: sfxdir = os.path.expanduser(options.sfxdir)
    if options.cachedir: cachedir = os.path.expanduser(options.cachedir)

    ## Do the work!
    if not options.xmlinfile:
        if getDecompressQueue(datadir):
            if not options.xmlonly:
                doDecompress(sfxdir, cachedir)

            if options.xml or options.xmlonly:
                writeQueueToXML(os.path.expanduser(options.xmloutfile))
    elif readQueueFromXML(os.path.expanduser(options.xmlinfile)):
        doDecompress(sfxdir, cachedir)
