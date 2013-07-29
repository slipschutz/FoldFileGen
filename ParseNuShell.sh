#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Must give two files.  Initial nucleus then final"
    exit;
fi


ftemp1="_temp1"
ftemp2="_temp2"
OutputFile="Binding_Energies"

### Get A Z from first  file
cat $1 | awk 'BEGIN{f=0} {if ($0 ~/\* ia,iz/&&f==0){print;f=1;}}' > __t
AI=$(cat __t | awk '{print $4}')
ZI=$(cat __t | awk '{print $5}')
rm -f "__t"

### Get A Z from second file
cat $2 | awk 'BEGIN{f=0} {if ($0 ~/\* ia,iz/&&f==0){print;f=1}}' > __t
AF=$(cat __t | awk '{print $4}')
ZF=$(cat __t | awk '{print $5}')
rm -f "__t"

PTypeFile1="";
PTypeFile2="";

echo "zi is" ${ZI}
echo "zf is" ${ZF}

if [ $ZI -eq $(($ZF-1)) ]; then # (p,n) direction
    echo "(P,N)"
    PTypeFile2="proton";
    PTypeFile1="neutron";
elif [ $ZI -eq $(($ZF+1)) ]; then #(n,p) direction
    echo "(N,P)"
    PTypeFile2="neutron";
    PTypeFile1="proton";
fi

echo "file one has " $PTypeFile1
echo "file two has " $PTypeFile2




cat $1 | awk 'BEGIN{p=0;}{if($0~/'$PTypeFile1' bound state/){p=1;} if (p==1 && $0~/radii/){p=0} if(p==1){print}}' > ${ftemp1}

cat $2 | awk 'BEGIN{p=0;}{if($0~/'$PTypeFile2' bound state/){p=1;} if (p==1 && $0~/radii/){p=0} if(p==1){print}}' > ${ftemp2}


echo "Initial" $AI $ZI > $OutputFile
cat ${ftemp1} | awk ' { if (NF >8&&$1!="k" &&$5<-1){print $2 $3 $4 " " $5 " " "-9"}else if(NF >8&&$1!="k"){print  $2 $3 $4 " " "-1" " " "-9"} }' >> $OutputFile
echo "Final " $AF $ZF >> $OutputFile
cat ${ftemp2} | awk ' { if (NF >8&&$1!="k" &&$5<-1){print $2 $3 $4 " " $5 " " "-9"}else if(NF >8&&$1!="k"){print  $2 $3 $4 " " "-1" " " "-9"} }' >> $OutputFile


