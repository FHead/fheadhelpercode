for filename in `ls | grep cpp$`
do
   exename=`echo $filename | sed "s/.cpp//g"`;
   g++ $filename -o $exename;
   mv $exename ..;
done
