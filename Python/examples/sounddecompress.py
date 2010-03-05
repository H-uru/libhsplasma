#!/usr/bin/env python

"""sounddecompress.py

    A Utility for decompressing Uru audio
    by Joseph Davies (deledrius@gmail.com)

  * Requires sox (http://sox.sourceforge.net/)
  * Requires libHSPlasma and PyHSPlasma (http://uru.zrax.net/svn/Plasma/)
  
  Usage:
    ./sounddecompress.py -u /path/to/uru
        (Override base Uru using the default subdirectories)
    ./sounddecompress.py -d /path/to/agefiles -s /path/to/oggs -c /path/to/outputwavs
        (Override default subdirectories)
    ./sounddecompress.py -u /path/to/uru -c /path/to/outputwavs
        (Override base Uru and output directory only)
"""


from __future__ import print_function

import os, sys, glob, math
import subprocess
from optparse import OptionParser

try:
    import PyHSPlasma
except ImportError as e:
    print("Unable to load module: {0}\nThis program requires PyHSPlasma.".format(e))
    sys.exit()


version = 1.01

## Default Paths
DefaultUruDir = "."
DefaultDataDir = "dat"
DefaultSFXDir = "sfx"
DefaultCacheDir = os.path.join(DefaultSFXDir,"streamingCache")

## Initialize empty queue of sound files to decompress
queue = {}


def getDecompressQueue(datadir):
    ## Only display Errors
    PyHSPlasma.plDebug.Init(PyHSPlasma.plDebug.kDLError)

    ## Create our Resource Manager
    plResMgr = PyHSPlasma.plResManager(PyHSPlasma.pvLive)

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
                    if PyHSPlasma.plFactory.kSoundBuffer in plResMgr.getTypes(page.location):
                        for key in plResMgr.getKeys(page.location, PyHSPlasma.plFactory.kSoundBuffer):	            
                            soundBuffer = PyHSPlasma.plSoundBuffer.Convert(key.object)

                            if soundBuffer.fileName in queue.keys():
                                channelOptions = queue[soundBuffer.fileName]
                            else:
                                channelOptions = {}

                            if (soundBuffer.flags & soundBuffer.kOnlyRightChannel): channel = channelOptions["Right"] = True
                            if (soundBuffer.flags & soundBuffer.kOnlyLeftChannel): channel = channelOptions["Left"] = True
                            if channelOptions == {}: channelOptions["Both"] = True

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
    parser.add_option("-u", "--uru", dest="urudir", default=DefaultUruDir, help="Sets base path for Uru")
    parser.add_option("-d", "--data", dest="datadir", help="Override path for input data files")
    parser.add_option("-s", "--sfx", dest="sfxdir", help="Override path for input sound files")
    parser.add_option("-c", "--cache", dest="cachedir", help="Override path for output sound files")
    parser.add_option("-q", "--quiet", dest="verbose", default=True, action="store_false", help="Don't print status messages")

    (options, args) = parser.parse_args()
    
    ## Send output to OS's null if unwanted
    if not options.verbose:
        sys.stdout = open(os.devnull,"w")
        sys.stderr = open(os.devnull,"w")
        
    ## Compute Paths
    datadir = os.path.join(options.urudir, DefaultDataDir)
    sfxdir = os.path.join(options.urudir, DefaultSFXDir)
    cachedir = os.path.join(options.urudir, DefaultCacheDir)
    if options.datadir: datadir = os.path.abspath(options.datadir)
    if options.sfxdir: sfxdir = os.path.abspath(options.sfxdir)
    if options.cachedir: cachedir = os.path.abspath(options.cachedir) 
    
    ## Do the work!
    if getDecompressQueue(datadir):
        doDecompress(sfxdir, cachedir)
