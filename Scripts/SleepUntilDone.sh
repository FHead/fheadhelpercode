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

sh $ScriptBase/Scripts/AsciiFin

