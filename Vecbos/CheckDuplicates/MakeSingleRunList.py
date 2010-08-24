#!/usr/bin/python

import sys, os

if len(sys.argv) < 3:
   print "Usage:"
   print sys.argv[0].strip(), "FileList", "RunNumber", "[TagBase]"
   sys.exit(255)

TagBase = "Run2010A-PromptReco-v4"
if len(sys.argv) >= 4:
   TagBase = sys.argv[3].strip()
FileList = sys.argv[1].strip()
RunNumber = sys.argv[2].strip()
Tag = TagBase + "_" + RunNumber

RootFiles = open(FileList, 'r').readlines()

OutputFile = open("SingleRunLists/" + Tag + ".list", 'w')
OutputScript = open("SingleRunScripts/" + Tag + ".sh", 'w')

CurrentDirectory = os.getcwd().strip()

for File in RootFiles:

   File = File.strip()

   Position = File.find(RunNumber)

   if Position == -1:
      continue

   OutputFile.write("rfio:" + File + "\n")

OutputScript.write("#!/bin/sh" + "\n")
OutputScript.write("" + "\n")
OutputScript.write("cd ~/CMSSW_3_5_6/src; eval `scramv1 runtime -sh`" + "\n")    ######## Change to your CMSSW area! ########
OutputScript.write("cd " + CurrentDirectory + "\n")
OutputScript.write("" + "\n")
OutputScript.write(r'root -l -b -q CheckDuplicates.C+"(\"SingleRunLists/' + Tag + r".list\", \"" + Tag + r"\", \"SingleRunRootFiles/" + Tag + r'.root\")"' + "\n")
OutputScript.write("" + "\n")

OutputScript.close()
OutputFile.close()


