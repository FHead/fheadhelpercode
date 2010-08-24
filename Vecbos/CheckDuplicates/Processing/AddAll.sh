#!/bin/sh

hadd -f AllRootFiles.root ../SingleRunRootFiles/*
root -l -b -q ConvertToPdf.C+
