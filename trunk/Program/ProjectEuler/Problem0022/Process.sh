for i in `cat p022_names.txt | tr ',' '\n' | tr -d '"' | sort`
do
   j=`echo $i | \
      sed "s/A/ + 1/g" | \
      sed "s/B/ + 2/g" | \
      sed "s/C/ + 3/g" | \
      sed "s/D/ + 4/g" | \
      sed "s/E/ + 5/g" | \
      sed "s/F/ + 6/g" | \
      sed "s/G/ + 7/g" | \
      sed "s/H/ + 8/g" | \
      sed "s/I/ + 9/g" | \
      sed "s/J/ + 10/g" | \
      sed "s/K/ + 11/g" | \
      sed "s/L/ + 12/g" | \
      sed "s/M/ + 13/g" | \
      sed "s/N/ + 14/g" | \
      sed "s/O/ + 15/g" | \
      sed "s/P/ + 16/g" | \
      sed "s/Q/ + 17/g" | \
      sed "s/R/ + 18/g" | \
      sed "s/S/ + 19/g" | \
      sed "s/T/ + 20/g" | \
      sed "s/U/ + 21/g" | \
      sed "s/V/ + 22/g" | \
      sed "s/W/ + 23/g" | \
      sed "s/X/ + 24/g" | \
      sed "s/Y/ + 25/g" | \
      sed "s/Z/ + 26/g"`
   echo $i `expr 0 $j`
done | cat -n | tee Meow | awk '{print $1 * $3}' | Total

