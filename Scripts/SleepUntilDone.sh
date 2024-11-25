#!/bin/bash

Scheduler=$1

function GetNumberFromCondor
{
   if [[ "$1" == "" ]]; then
      String=`condor_q $USER | grep "Total for query" | tail -1 | cut --delim=' ' --field=4-`
   else
      String=`condor_q $USER -name "$1" | grep "Total for query" | tail -1 | cut --delim=' ' --field=4-`
   fi

   Total=`echo $String | cut --delim=' ' --field=1`
   Completed=0
   Removed=0
   Idle=0
   Running=0
   Held=0
   Suspended=0
}

function CheckFromCondor
{
   String=
   Total=0
   Completed=0
   Removed=0
   Idle=0
   Running=0
   Held=0
   Suspended=0
   GetNumberFromCondor "$1"

   while [[ "$Total" != "0" ]]
   do
      echo "`date`; $String"

      if test $Total -lt 10
      then
         sleep 5
      elif test $Total -lt 50
      then
         sleep 15
      else
         sleep 60
      fi

      GetNumberFromCondor "$1"
   done
}

function CheckFromLSF
{
   while [[ "`bjobs | grep -v "JOBID" | wc -l`" != "0" ]]
   do
      JobsRemaining=`bjobs | grep -v " dt " | wc -l | SubtractConst 1`
      echo "`date`; Jobs remaining: $JobsRemaining; Running: `bjobs | grep ' RUN ' | wc -l`"

      if test $JobsRemaining -lt 10
      then
         sleep 5
      elif test $JobsRemaining -lt 50
      then
         sleep 15
      else
         sleep 60
      fi
   done
}

function CheckFromQSub
{
   while [[ "`qstat | grep -v " dt " | grep -v "\-\-\-\-\-\-" | grep -v "^job-ID" | wc -l`" != "0" ]]
   do
      for i in `qstat | grep Eqw | grep yichen | awk '{print $1}'`
      do
         qresub $i
         qdel $i
      done
   
      JobsRemaining=`qstat | grep -v " dt " | wc -l | SubtractConst 2`
      echo "`date`; Jobs remaining: $JobsRemaining; Running: `qstat | grep '   r   ' | wc -l`"
   
      if test $JobsRemaining -lt 10
      then
         sleep 5
      elif test $JobsRemaining -lt 50
      then
         sleep 15
      else
         sleep 60
      fi
   done
}

CheckFromCondor "$1"

sh ~/Scripts/AsciiFin

