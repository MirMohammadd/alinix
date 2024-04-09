import unittest
import copy
import datetime
import argparse
import subprocess
import sys


COMMANDS = {
    "Build" : "make run",
    "vm": "make qemu",
    "MakeNFound":"No targets specified and no makefile found"
}


ERRORS = {
    "NotFound":"command not found",
    
}


########################################################
#Defining exception classes

class MakeFileCompilerException(Exception):
    pass
########################################################

class AttribClass(object):
    def __init__(self):
        self.runNormalMake = "make"
        self.runVmMake = "make qemu"
        self.runMakeRun = "make run"


class Debugger(unittest.TestCase,AttribClass):
    def __init__(self):
        pass
    
    
    def testCompilerMake(self):
        try:
            cmd = subprocess.run(self.runNormalMake,shell=True)
            self.assertEqual(cmd.returncode, 0)
        except subprocess.CalledProcessError as exc:
            sys.exit("[ERROR] Got error while running testing makefile command %s"%(str(getSafeExcStr(exc))))
        except AssertionError:
            excStr = getSafeExcStr(exc)

            if any(command for command in ERRORS in excStr):
                print("Make sure that you have the Make tools installed on your system")
                sys.exit("[ERROR] Got error while running testing makefile command %s"%(str(getSafeExcStr(exc))))

        except:
            pass

def parse_arguments(debug=False):
    parser = argparse.ArgumentParser(description='Advanced Debugger')
    parser.add_argument("--level",type=int,default=1,required=False,help="Debug level, range should be 1 to 6 (default: 1)")
    parser.add_argument('-d', '--debug', action='store_true', help='Enable debug output')
    return parser.parse_args(
        
    )

def getSafeExcStr(ex):
    retVal = None
    if getattr(ex,"message",None):
        retVal = ex.message
    elif getattr(ex,"__str__",None):
        retVal = ex.__str__()
    return retVal
