<?xml version="1.0" encoding="utf-8" ?>

<!-- This is a sample .prc file, just for showing the idea of "PrpRC" off...
     Compiling this file would produce the files MyAge.age,
     MyAge_District_BuiltIn.prp, MyAge_District_Textures.prp,
     MyAge_District_MainRoom.prp and MyAge_District_Dummy.prp.
     
     This format could, of course, get rather large, so I also propose
     having the <District> tag with an optional src= parameter, which
     specifies another .prc file containing the District data.  This
     parameter would be optional, so that a district can either be
     in-line (such as the AgeGlobal districts), or in an external file
     for the larger districts.  Obviously, other formats that do better
     in an external file (such as images, as shown below) should also be
     specified with a src= parameter.
     
     Another point:  As was recommended at a recent meeting, it should be
     possible to specify a small set of properties as an individual object,
     which can be used in other projects for those who wish to have a small
     library of "base objects" from which they can build off of.  In this
     case, a top-level node of <Resource> can be specified, including a
     set of PRP-type objects that a PRC-compatible application can import
     (or export) for more flexility.
     
     -->

<!-- Author: Michael Hansen -->
<!-- Created: 2007/01/17 16:51:32 -->
<!-- Modified: 2007/01/17 18:15:01 -->
<!-- Revision: 1.0 -->
<!-- Generator: (Any application or plugin with PRC support :D) -->

<Age name="MyAge" prefix="444" maxcapacity="20">
    <District name="BuiltIn">
        <PythonFileMod name="VeryVerySpecialPythonFileMod">
            <PythonFileName>MyAge</PythonFileName>
        </PythonFileMod>
        <SceneObject name="AgeSDLHook">
            <Modifiers>
                <Key type="PythonFileMod" name="VeryVerySpecialPythonFileMod" />
            </Modifiers>
        </SceneObject>
    </District>
    <District name="Textures">
        <Mipmap type="DXT5" name="MyDXTImage" src="img/MyDXTImage.dds" />
        <Mipmap type="JPEG" name="MyJPEGImage" src="img/MyJPEGImage.jpg" />
    </District>
    <District name="MainRoom">
        <SceneNode>
            <SceneObjectList>
                <Key type="SceneObject" name="SomeObject" />
                <Key type="SceneObject" name="SomeOtherObject" />
            </SceneObjectList>
            <GenericPoolList>
                <Key type="MessageForwarder" name="MsgFwdObj" />
            </GenericPoolList>
        </SceneNode>
        <SceneObject name="SomeObject">
            <DrawInterface>
                <!-- DrawIntf specific parameters -->
            </DrawInterface>
            <CoordinateInterface>
                <!-- CoordIntf specific parameters -->
            </CoordinateInterface>
            <Interfaces>
                <Key type="SoftVolumeSimple" name="SoftReg Whatever" />
            </Interfaces>
            <Modifiers>
                <Key type="ResponderModifier" name="SomeResponder" />
            </Modifiers>
        </SceneObject>
        <SoftVolumeSimple name="SoftReg Whatever">
            <!-- SoftVolumeSimple parameters -->
        </SoftVolumeSimple>
        <ResponderModifier>
            <!-- Responder parameters -->
        </ResponderModifier>
        <SceneObject name="SomeOtherObject">
            <!-- missing properties either mean non-existant or Defaults -->
        </SceneObject>
        <MessageForwarder name="MsgFwdObj">
            <!-- you get the picture -->
        </MessageForwarder>
        <Material name="MyMat">
            <Layers>
                <Key type="Layer" name="MyLayer" />
            </Layers>
        </Material>
        <Layer name="MyLayer">
            <Texture type="Mipmap" source="AgeGlobal" name="MyDXTImage" />
            <Color type="Ambient" red="1.0" green="0.5" blue="0.0" alpha="1.0" />
            <Color type="Emissive" red="0.0" green="0.0" blue="0.0" alpha="1.0" />
            <Color type="Diffuse" red="1.0" green="0.0" blue="0.0" alpha="1.0" />
            <Color type="Specular" red="0.0" green="0.8" blue="0.1" alpha="1.0" />
        </Layer>
    </District>
    <District name="Dummy" autoload="false" src="Districts/Dummy.prc" />
</Age>

