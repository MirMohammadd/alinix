import unittest
import copy
import datetime
import argparse
import subprocess


COMMANDS = {
    "Build" : "make run",
    "vm": "make qemu"
}


########################################################
#Defining exception classes

class MakeFileCompilerException(Exception):
    pass
########################################################


class Debugger(unittest.TestCase):
    def testCompilerMake(self):
        pass

def parse_arguments(debug=False):
    parser = argparse.ArgumentParser(description='Advanced Debugger')
    parser.add_argument("--level",type=int,default=1,required=False,help="Debug level, range should be 1 to 6 (default: 1)")
    parser.add_argument('-d', '--debug', action='store_true', help='Enable debug output')
    return parser.parse_args(
        
    )