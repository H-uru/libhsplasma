" Vim syntax file
" Language:     (Uru) State Descriptor Language
" Maintainer:   Michael Hansen <zrax@comcast.net>
" Last Change:  2006 November 22

if exists("b:current_syntax")
  finish
endif

" Shared language features
syn keyword sdlConstant     true false nil
syn match   sdlNumber       display "-\=\<\d\+\>"
syn match   sdlComment      "#.*$"
syn region  sdlString       matchgroup=Normal start=+"+ end=+"+


" Uru SDL defs
if ! exists("g:urusdl_noUru")
  syn keyword sdlKeyword      STATEDESC VERSION VAR
  syn keyword sdlOption       DEFAULT DEFAULTOPTION DISPLAYOPTION
  syn keyword sdlOption       INTERNAL PHASED
  syn case ignore
  syn keyword sdlType         bool int short byte float double string32
  syn keyword sdlType         rgb rgba rgb8 rgba8 point3 vector3 quat quaternion
  syn keyword sdlType         creatable time ageTimeOfDay plKey message
  syn keyword sdlConstant     vault hidden
  syn match   sdlIdentifier   "$\h\w*"
endif


" EOA SDL defs
if ! exists("g:urusdl_noEoa")
  syn keyword sdlKeyword      struct version
  syn keyword sdlOption       default
  syn keyword sdlType         bool buffer byte short int uint double float
  syn keyword sdlType         matrix44 point3 quaternion string uoid vector3
  syn keyword sdlType         AgeTimeElapsed AgeTimeOfDay GameTimeElapsed
  syn match   sdlComment      "//.*$"
  syn region  sdlCommentBlock start="/\*" end="\*/"
endif


" Color defaults
hi def link sdlKeyword      Statement
hi def link sdlOption       PreProc
hi def link sdlConstant     Constant
hi def link sdlType         Type
hi def link sdlCommentBlock sdlComment
hi def link sdlComment      Comment
hi def link sdlNumber       Number
hi def link sdlIdentifier   Identifier
hi def link sdlString       String

let b:current_syntax = "urusdl"

