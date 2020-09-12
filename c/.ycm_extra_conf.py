from distutils.sysconfig import get_python_inc
import platform
import os
import sys
import subprocess
import ycm_core

DIR_OF_THIS_SCRIPT = os.path.abspath( os.path.dirname( __file__ ) )
DIR_OF_THIRD_PARTY = os.path.join( DIR_OF_THIS_SCRIPT, 'third_party' )
SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

clangIncludeAdded = False

flags = [
'-x', 'c',
'-Wall',
'-Wextra',
'-Werror',
# only the YCM source code needs it.
'-DUSE_CLANG_COMPLETER',
'-DYCM_EXPORT=',
get_python_inc(),
'-I',
'.',
]

flags.append( '-std=c99' )

compilation_database_folder = ''

if os.path.exists( compilation_database_folder ):
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None


def IsHeaderFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]


def FindCorrespondingSourceFile( filename ):
  if IsHeaderFile( filename ):
    basename = os.path.splitext( filename )[ 0 ]
    for extension in SOURCE_EXTENSIONS:
      replacement_file = basename + extension
      if os.path.exists( replacement_file ):
        return replacement_file
  return filename

def addClanIncludeDirs():
    global flags
    if os.path.exists("source.dirs"):
        with open("source.dirs", "r") as file:
            for line in file.readlines():
                dirName = line.strip()
                for (dirPath, dirNames, fileNames) in os.walk(dirName):
                    for fileName in fileNames:
                        ext = os.path.splitext(fileName)[1]
                        if ext in [".h", ".hpp", ".c", ".cpp"]:
                            flags.append('-I')
                            flags.append(dirPath)
                            break

#    global flags
#    if os.path.exists("source.dirs"):
#        with open("source.dirs", "r") as file:
#            for line in file.readlines():
#                directory = line.strip()
#                #flags.append('-I')
#                #flags.append(directory)
#                #continue
#                subdirs = [x[0] for x in os.walk(directory)]
#                for dirSub in subdirs:
#                    flags.append('-I')
#                    flags.append(dirSub)
#
    with open("/tmp/dump", "w+") as fileDump:
        for each in flags:
            fileDump.write(each)
            fileDump.write("\n")


def Settings( **kwargs ):
  if kwargs[ 'language' ] == 'cfamily':
    # If the file is a header, try to find the corresponding source file and
    # retrieve its flags from the compilation database if using one. This is
    # necessary since compilation databases don't have entries for header files.
    # In addition, use this source file as the translation unit. This makes it
    # possible to jump from a declaration in the header file to its definition
    # in the corresponding source file.
    global clangIncludeAdded
    if False == clangIncludeAdded:
        addClanIncludeDirs()
        clangIncludeAdded = True

    filename = FindCorrespondingSourceFile( kwargs[ 'filename' ] )

    if not database:
      return {
        'flags': flags,
        'include_paths_relative_to_dir': DIR_OF_THIS_SCRIPT,
        'override_filename': filename
      }

    compilation_info = database.GetCompilationInfoForFile( filename )
    if not compilation_info.compiler_flags_:
      return {}

    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object.
    final_flags = list( compilation_info.compiler_flags_ )

    # NOTE: This is just for YouCompleteMe; it's highly likely that your project
    # does NOT need to remove the stdlib flag. DO NOT USE THIS IN YOUR
    # ycm_extra_conf IF YOU'RE NOT 100% SURE YOU NEED IT.
    try:
      final_flags.remove( '-stdlib=libc++' )
    except ValueError:
      pass

    return {
      'flags': final_flags,
      'include_paths_relative_to_dir': compilation_info.compiler_working_dir_,
      'override_filename': filename
    }
  return {}


def GetStandardLibraryIndexInSysPath( sys_path ):
  for path in sys_path:
    if os.path.isfile( os.path.join( path, 'os.py' ) ):
      return sys_path.index( path )
  raise RuntimeError( 'Could not find standard library path in Python path.' )


def PythonSysPath( **kwargs ):
  sys_path = kwargs[ 'sys_path' ]
  for folder in os.listdir( DIR_OF_THIRD_PARTY ):
    if folder == 'python-future':
      folder = os.path.join( folder, 'src' )
      sys_path.insert( GetStandardLibraryIndexInSysPath( sys_path ) + 1,
                       os.path.realpath( os.path.join( DIR_OF_THIRD_PARTY,
                                                       folder ) ) )
      continue

    if folder == 'cregex':
      interpreter_path = kwargs[ 'interpreter_path' ]
      major_version = subprocess.check_output( [
        interpreter_path, '-c', 'import sys; print( sys.version_info[ 0 ] )' ]
      ).rstrip().decode( 'utf8' )
      folder = os.path.join( folder, 'regex_{}'.format( major_version ) )

    sys_path.insert( 0, os.path.realpath( os.path.join( DIR_OF_THIRD_PARTY, folder ) ) )
  return sys_path

