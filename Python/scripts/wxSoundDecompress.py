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

"""SoundDecompress.py

    A Utility for decompressing Uru audio
    by Joseph Davies (deledrius@gmail.com)

  * Requires sox (http://sox.sourceforge.net/)
  * Requires libHSPlasma and PyHSPlasma (https://github.com/H-uru/libhsplasma
    with Python support.)
  * Requires wxPython (http://wxpython.org/)
"""

import os
import sys
import glob
import threading
import time
import subprocess
from xml.dom.minidom import parse

try:
    import wx
except ImportError as e:
    print("Unable to load module: {0}\nThis program requires wxPython.".format(e))
    sys.exit()

try:
    import PyHSPlasma
except ImportError as e:
    libPlasma = False
else:
    libPlasma = True

version = 1.11

## Default paths
PlatformDefaultDir = {
    "darwin": "/Applications/Myst Online.app/Contents/Resources/Myst Online.app/Contents/Resources/transgaming/c_drive/Program Files/Uru Live/",
    "linux2": "~/.wine/drive_c/Program Files/Uru Live/",
    "win32": "C:\\Program Files\\Uru Live\\",
    }

DefaultUruDir = PlatformDefaultDir[sys.platform]
DefaultDataDir = "dat"
DefaultSFXDir = "sfx"
DefaultCacheDir = os.path.join(DefaultSFXDir,"streamingCache")

## Events
myEVT_QUEUE_DISPATCH = wx.NewEventType()
EVT_QUEUE_DISPATCH = wx.PyEventBinder(myEVT_QUEUE_DISPATCH)

def postEvent(source, etype, evalue):
    evt = DispatchEvent(myEVT_QUEUE_DISPATCH, -1, {"MessageType": etype, "MessageValue": evalue})
    wx.PostEvent(source._parent, evt)

class DispatchEvent(wx.PyCommandEvent):
    """Event to carry event dispatch messages."""

    EventUpdateStatus       = 0
    EventUpdateProgress     = 1
    EventQueueBuildComplete = 2
    EventQueueBuildFail     = 3
    EventDialogBox          = 4
    EventDecompressComplete = 5
    EventDecompressFail     = 6

    def __init__(self, etype, eid, value=None):
        wx.PyCommandEvent.__init__(self, etype, eid)
        self.MessageType = value["MessageType"]
        self.MessageValue = value["MessageValue"]


## Main User Interface
class Interface(wx.Frame):
    inputChoices = ["From Age Files", "From XML File"]

    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, size = (500, 300),
                          style = wx.MAXIMIZE_BOX | wx.MINIMIZE_BOX | wx.SYSTEM_MENU | wx.CAPTION | wx.CLOSE_BOX | wx.RESIZE_BORDER )

        self._doLayout()

        self.Bind(wx.EVT_BUTTON, self.OnBrowse, id = self.browseButton.GetId())
        self.Bind(wx.EVT_BUTTON, self.OnBrowseXML, id = self.xmlBrowseButton.GetId())
        self.Bind(wx.EVT_CHECKBOX, self.OnImportXMLChecked, id = self.xmlImport.GetId())
        self.Bind(wx.EVT_BUTTON, self.OnActionButton, id = self.goButton.GetId())

        self.DispatchMap = {}
        self.DispatchBind(DispatchEvent.EventUpdateStatus, self.OnUpdateStatus)
        self.DispatchBind(DispatchEvent.EventUpdateProgress, self.OnUpdateProgress)
        self.DispatchBind(DispatchEvent.EventQueueBuildComplete, self.OnQueueBuildComplete)
        self.DispatchBind(DispatchEvent.EventQueueBuildFail, self.OnQueueBuildFail)
        self.DispatchBind(DispatchEvent.EventDialogBox, self.OnDoDialog)
        self.DispatchBind(DispatchEvent.EventDecompressComplete, self.OnDecompressComplete)
        self.DispatchBind(DispatchEvent.EventDecompressFail, self.OnDecompressFail)
        self.Bind(EVT_QUEUE_DISPATCH, self.OnQueueDispatch)

        self.Centre()
        self.Show(True)

        self.queue = {}
        self.worker = None
        self.abort = False

        if not libPlasma:
            dlg = wx.MessageDialog(None, "This program requires PyHSPlasma for full functionality. Only the XML Import option will be available.", "Missing PyHSPlasma Module",
                                   wx.OK | wx.ICON_INFORMATION | wx.CENTRE)
            dlg.Centre()
            dlg.ShowModal()
            dlg.Destroy()
            self.xmlImport.SetValue(True)
            self.xmlPathField.Enabled = True
            self.xmlBrowseButton.Enabled = True
            self.xmlPathField.SetValue(os.getcwd())
        self.pathField.SetValue(os.path.expanduser(DefaultUruDir))

    def _doLayout(self):
        panel = wx.Panel(self, -1)

        self.inputStaticText = wx.StaticText(panel, -1, 'Uru Location:')
        self.pathField = wx.TextCtrl(panel, -1)
        self.browseButton = wx.Button(panel, -1, "Browse...")
        self.xmlGroup = wx.StaticBox(panel, -1, "XML Options")
        self.xmlImport = wx.CheckBox(panel, -1, "Import Queue from XML")
        self.xmlPathField = wx.TextCtrl(panel, -1)
        self.xmlPathField.Enabled = False
        self.xmlBrowseButton = wx.Button(panel, -1, "Browse...")
        self.xmlBrowseButton.Enabled = False
        self.goButton = wx.Button(panel, -1, "Start!")
        self.progressBar = wx.Gauge(panel, -1)
        #self.progressBar.Hide()
        self.statusBox = wx.TextCtrl(panel, -1, "Press 'Start!' when ready.", style = wx.TE_MULTILINE | wx.TE_READONLY)

        self.vbox = wx.BoxSizer(wx.VERTICAL)
        self.hbox1 = wx.BoxSizer(wx.HORIZONTAL)
        self.hbox1.Add(self.inputStaticText, 0)

        self.hbox2 = wx.BoxSizer(wx.HORIZONTAL)
        self.hbox2.Add(self.pathField, 2, wx.EXPAND | wx.LEFT | wx.RIGHT, border = 10)
        self.hbox2.Add(self.browseButton, 0)

        self.hbox3 = wx.StaticBoxSizer(self.xmlGroup, wx.HORIZONTAL)
        self.vbox2 = wx.BoxSizer(wx.VERTICAL)
        self.hbox3_1 = wx.BoxSizer(wx.HORIZONTAL)
        self.hbox3_1.Add(self.xmlImport, 0)
        self.hbox3_2 = wx.BoxSizer(wx.HORIZONTAL)
        self.hbox3_2.Add(self.xmlPathField, 2, wx.EXPAND | wx.LEFT | wx.RIGHT, border = 10)
        self.hbox3_2.Add(self.xmlBrowseButton, 0)
        self.vbox2.Add(self.hbox3_1, 2, wx.EXPAND)
        self.vbox2.Add(self.hbox3_2, 2, wx.EXPAND | wx.RIGHT, border = 10)
        self.vbox2.Add((-1,5))
        self.hbox3.Add(self.vbox2, 2)

        self.hbox4 = wx.BoxSizer(wx.HORIZONTAL)
        self.hbox4.Add(self.goButton, 0, wx.TOP, border = 3)
        self.hbox4.Add(self.progressBar, 2, wx.EXPAND | wx.LEFT, border = 10)

        self.hbox5 = wx.BoxSizer(wx.HORIZONTAL)
        self.hbox5.Add(self.statusBox, 2, wx.EXPAND | wx.TOP, border = 3)

        self.vbox.Add(self.hbox1, 0, wx.EXPAND | wx.ALL, border = 5)
        self.vbox.Add(self.hbox2, 0, wx.EXPAND | wx.RIGHT, border = 10)
        self.vbox.Add((-1, 10))
        self.vbox.Add(self.hbox3, 0, wx.EXPAND | wx.LEFT | wx.RIGHT, border = 10)
        self.vbox.Add(self.hbox4, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, border = 10)
        self.vbox.Add((-1, 10))
        self.vbox.Add(self.hbox5, 1, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.BOTTOM, border = 10)

        panel.SetSizer(self.vbox)

    def DispatchBind(self, etype, target):
        self.DispatchMap[etype] = target

    ## UI Event Handlers
    def OnBrowse(self, event):
        if sys.platform == "darwin":
            ## The wxDirDialog doesn't allow traversing .app bundles in OSX, so
            ##  a file picker will have to do
            dlg = wx.FileDialog(self, "Please choose a file in your MOUL directory:", defaultDir = os.path.expanduser(self.pathField.GetValue()), wildcard = "EXE files (*.exe)|*.exe", style = wx.OPEN)
            dlg.Centre()
            if dlg.ShowModal() == wx.ID_OK:
                self.pathField.SetValue(os.path.dirname(dlg.GetPath()))
            dlg.Destroy()
        else:
            dlg = wx.DirDialog(self, "Please choose your MOUL directory:", defaultPath = os.path.expanduser(self.pathField.GetValue()))
            dlg.Centre()
            if dlg.ShowModal() == wx.ID_OK:
                self.pathField.SetValue(dlg.GetPath())
            dlg.Destroy()

    def OnBrowseXML(self, event):
        dlg = wx.FileDialog(self, "Please choose an XML queue file:", defaultDir = os.path.expanduser(self.xmlPathField.GetValue()), wildcard = "XML files (*.xml)|*.xml", style = wx.OPEN)
        dlg.Centre()
        if dlg.ShowModal() == wx.ID_OK:
            self.xmlPathField.SetValue(dlg.GetPath())
        dlg.Destroy()

    def OnImportXMLChecked(self, event):
        if not libPlasma:
            dlg = wx.MessageDialog(None, "This option cannot be disabled in the absence of the PyHSPlasma module.", "Missing PyHSPlasma Module",
                                   wx.OK | wx.ICON_INFORMATION | wx.CENTRE)
            dlg.Centre()
            dlg.ShowModal()
            dlg.Destroy()
            self.xmlImport.SetValue(True)
        else:
            self.xmlPathField.Enabled = self.xmlImport.GetValue()
            self.xmlBrowseButton.Enabled = self.xmlImport.GetValue()
            if self.xmlPathField.GetValue() == "":
                self.xmlPathField.SetValue(os.getcwd())

    def OnActionButton(self, event):
        if not self.worker:
            self.browseButton.Disable()
            self.pathField.Disable()
            self.goButton.SetLabel("Abort")
            self.progressBar.Show()

            if self.xmlImport.GetValue() == True:
                self.worker = BuildQueueThread(self, self.xmlPathField.GetValue(), fromXML = True)
            else:
                self.worker = BuildQueueThread(self, self.pathField.GetValue())
            self.worker.start()
        else:
            self.abort = True
            self.worker.join()
            self.browseButton.Enable()
            self.pathField.Enable()
            self.goButton.SetLabel("Start!")
            self.progressBar.Hide()
            self.abort = False

    ## Logic Event Handlers
    def OnUpdateStatus(self, value):
        self.statusBox.AppendText("\n{0}".format(value))

    def OnUpdateProgress(self, value):
        self.progressBar.SetValue(value)

    def OnQueueBuildFail(self, reason):
        if self.worker:
            self.abort = True
            self.worker.join()
            self.worker = None
        self.OnUpdateStatus(reason)
        self.browseButton.Enable()
        self.pathField.Enable()
        self.goButton.SetLabel("Go!")
        self.progressBar.Hide()
        self.abort = False

    def OnQueueBuildComplete(self, result):
        if self.worker:
            self.worker.join()
            self.worker = None
            self.queue = result
        else:
            if result:
                self.queue = result

        if len(self.queue) > 0:
            self.worker = DecompressQueueThread(self, self.pathField.GetValue(), self.queue)
            self.worker.start()

    def OnDecompressFail(self, reason):
        if self.worker:
            self.abort = True
            self.worker.join()
            self.worker = None
        self.OnUpdateStatus(reason)
        self.browseButton.Enable()
        self.pathField.Enable()
        self.goButton.SetLabel("Go!")
        self.progressBar.Hide()
        self.abort = False

    def OnDecompressComplete(self, result):
        if self.worker:
            self.worker.join()
            self.worker = None
            self.browseButton.Enable()
            self.pathField.Enable()
            self.goButton.SetLabel("Go!")
            self.progressBar.Hide()
            self.abort = False

        dlg = wx.MessageDialog(None, "Sound Decompression Complete!", "Success", wx.OK)
        dlg.Centre()
        dlg.ShowModal()
        dlg.Destroy()

    def OnDoDialog(self, options):
        dlg = wx.MessageDialog(None, options[0], options[1], options[2] | wx.CENTRE)
        dlg.ShowModal()
        dlg.Destroy()

    def OnQueueDispatch(self, event):
        self.DispatchMap[event.MessageType](event.MessageValue)


class BuildQueueThread(threading.Thread):
    def __init__(self, parent, inpath, fromXML = False):
        threading.Thread.__init__(self)
        self._parent = parent
        self._inpath = inpath
        self._fromXML = fromXML
        self._queue = {}

    ## Event Helpers
    def postUpdateStatus(self, statustext):
        postEvent(self, DispatchEvent.EventUpdateStatus, statustext)

    def postUpdateProgress(self, value):
        postEvent(self, DispatchEvent.EventUpdateProgress, value)

    def postDialogBox(self, dlgoptions):
        postEvent(self, DispatchEvent.EventDialogBox, dlgoptions)

    def postQueueBuildComplete(self, result=None):
        postEvent(self, DispatchEvent.EventQueueBuildComplete, result)

    def postQueueBuildFail(self, reason=None):
        postEvent(self, DispatchEvent.EventQueueBuildFail, reason)

    def shouldAbort(self):
        if self._parent.abort == True:
            self.postQueueBuildFail("** Aborted by user **")
            return True

    ## XML Queue Reader
    def readQueueFromXML(self):
        self.postUpdateStatus("Reading queue from xml: {0}".format(self._inpath))
        queueXML = parse(self._inpath)
        soundfiles = queueXML.getElementsByTagName("soundfile")

        numFilesProcessed = 0
        numFiles = len(soundfiles)
        self.postUpdateProgress(float(numFilesProcessed)/float(numFiles) * 100)

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
            self._queue[soundfile.attributes["name"].value] = channelOptions

            numFilesProcessed = numFilesProcessed + 1
            self.postUpdateProgress(float(numFilesProcessed)/float(numFiles) * 100)

        self.postUpdateStatus("{0} sound files added to queue.".format(len(self._queue)))
        self.postQueueBuildComplete(self._queue)
        self.postUpdateProgress(100)
        return True

    ## Main Thread Worker
    def run(self):
        if self._fromXML:
            return self.readQueueFromXML()

        datadir = os.path.join(self._inpath, DefaultDataDir)

        ## Only display Errors
        PyHSPlasma.plDebug.Init(PyHSPlasma.plDebug.kDLError)

        ## Create our Resource Manager
        plResMgr = PyHSPlasma.plResManager()

        ## Get Age list for progress
        self.postUpdateStatus("Loading Age files...")

        numAges = len(glob.glob(os.path.join(datadir, "*.age")))
        numAgesRead = 0
        if numAges == 0:
            self.postDialogBox(("No Age files found in {0}\n\nDecompression aborted.".format(datadir), 'No Ages Found',
                                wx.OK | wx.ICON_EXCLAMATION))
            self.postQueueBuildFail("No Age files found in {0}.  Aborted.".format(datadir))
            return False

        self.postUpdateStatus("{0} Ages found in {1}.\nScanning...".format(numAges, datadir))

        ## Flip through all ages
        self.postUpdateProgress(float(numAgesRead)/float(numAges) * 100)
        for ageFile in glob.iglob(os.path.join(datadir,"*.age")):
            fullpath = os.path.abspath(ageFile)

            self.postUpdateStatus("Scanning {0} ...".format(os.path.basename(ageFile)))

            ## Too fast and the message event pump gets stuck, so wait
            time.sleep(0.5)

            if self.shouldAbort(): return False

            try:
                age = plResMgr.ReadAge(fullpath, True)
            except IOError as e:
                self.postUpdateStatus("Skipping {0} - Unable to read Age.".format(os.path.basename(ageFile)))
            except Exception as e:
                self.postDialogBox(("Error loading Age - {0}".format(e), "Fatal Error",
                                    wx.OK | wx.ICON_ERROR))
                self.postQueueBuildFail("Error loading Age - {0}".format(ageFile))
                return False
            else:
                try:
                    ## Get the plSoundBuffer in each page and queue sounds
                    ##  which are not set to StreamCompressed
                    for pageNum in range(0, age.getNumPages()):
                        if self.shouldAbort(): return False

                        page = plResMgr.FindPage(age.getPageLoc(pageNum, plResMgr.getVer()))
                        if PyHSPlasma.plFactory.kSoundBuffer in plResMgr.getTypes(page.location):
                            for key in plResMgr.getKeys(page.location, PyHSPlasma.plFactory.kSoundBuffer):
                                soundBuffer = key.object

                                if soundBuffer.fileName in self._queue.keys():
                                    channelOptions = self._queue[soundBuffer.fileName]
                                else:
                                    channelOptions = {}

                                if (soundBuffer.flags & soundBuffer.kOnlyRightChannel):
                                    channel = channelOptions["Right"] = True
                                if (soundBuffer.flags & soundBuffer.kOnlyLeftChannel):
                                    channel = channelOptions["Left"] = True
                                if not channelOptions:
                                    channelOptions["Both"] = True

                                if not (soundBuffer.flags & soundBuffer.kStreamCompressed):
                                    self._queue[soundBuffer.fileName] = channelOptions
                except MemoryError as e:
                    self.postDialogBox(("Fatal Error - Unable to process Age ({0}) - {1}".format(age.name, e), "Fatal Error",
                                        wx.OK | wx.ICON_ERROR))
                    self.postQueueBuildFail("Unable to process Age ({0}) - {1}".format(age.name))
                    return False

                plResMgr.UnloadAge(age.name)

            ## Onto the next
            numAgesRead = numAgesRead + 1
            self.postUpdateProgress(float(numAgesRead)/float(numAges) * 100)

        self.postUpdateStatus("{0} sound files added to queue.".format(len(self._queue)))
        self.postQueueBuildComplete(self._queue)
        self.postUpdateProgress(100)
        return True

class DecompressQueueThread(threading.Thread):
    def __init__(self, parent, urupath, queue):
        threading.Thread.__init__(self)
        self._parent = parent
        self._urupath = urupath
        self._queue = queue

    ## Event Helpers
    def postUpdateStatus(self, statustext):
        postEvent(self, DispatchEvent.EventUpdateStatus, statustext)

    def postUpdateProgress(self, value):
        postEvent(self, DispatchEvent.EventUpdateProgress, value)

    def postDialogBox(self, dlgoptions):
        postEvent(self, DispatchEvent.EventDialogBox, dlgoptions)

    def postDecompressComplete(self, result=None):
        postEvent(self, DispatchEvent.EventDecompressComplete, result)

    def postDecompressFail(self, reason=None):
        postEvent(self, DispatchEvent.EventDecompressFail, reason)

    def shouldAbort(self):
        if self._parent.abort == True:
            self.postDecompressFail("** Aborted by user **")
            return True

    ## Main Thread Worker
    def run(self):
        sfxdir = os.path.join(self._urupath, DefaultSFXDir)
        cachedir = os.path.join(self._urupath, DefaultCacheDir)

        if not os.path.exists(os.path.abspath(sfxdir)):
            self.postDialogBox(("Unable to find input sounds.", "Fatal Error",
                        wx.OK | wx.ICON_ERROR))
            self.postDecompressFail("Unable to find input sounds at {0}".format(sfxdir))
            return False

        ## Make sure the cache dir exists
        if not os.path.exists(os.path.abspath(cachedir)):
            self.postUpdateStatus("Creating streamingCache directory.")
            os.mkdir(cachedir)

        ## Prepare progress
        self.postUpdateStatus("Decompressing audio files... (This may take a while)")
        numFilesProcessed = 0
        numFiles = len(self._queue)

        ## Flip through all sound files
        self.postUpdateProgress(float(numFilesProcessed)/float(numFiles) * 100)
        for oggFile in self._queue.keys():

            ## Too fast and the message event pump gets stuck, so wait
            time.sleep(0.5)

            inpath = os.path.abspath(os.path.join(sfxdir, oggFile))
            if os.path.exists(inpath):
                for channel in self._queue[oggFile]:
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

                    if self.shouldAbort(): return False

                    ## Conversion from OGG to WAV
                    try:
                        retcode = subprocess.check_call(soxCommand, shell=True, stderr=open(os.devnull,"w"))
                    except subprocess.CalledProcessError as e:
                        self.postDialogBox(("Unable to execute SoX! - {0}".format(e), "Fatal Error",
                                    wx.OK | wx.ICON_ERROR))
                        self.postDecompressFail("Unable to execute SoX")
                        return False
                    except OSError as e:
                        self.postDialogBox(("Unable to execute SoX! - {0}".format(e), "Fatal Error",
                                    wx.OK | wx.ICON_ERROR))
                        self.postDecompressFail("Unable to execute SoX")
                        return False

            ## Onto the next
            numFilesProcessed = numFilesProcessed + 1
            self.postUpdateProgress(float(numFilesProcessed)/float(numFiles) * 100)


        self.postUpdateStatus("Sound Decompression Complete.")
        self.postDecompressComplete()
        self.postUpdateProgress(100)
        return True

if __name__ == '__main__':
    app = wx.App(0)
    Interface(None, -1, "MOUL Sound Decompressor v{0}".format(version))
    app.MainLoop()
