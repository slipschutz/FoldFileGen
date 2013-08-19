#!/bin/bash
####################################################################################
#
#  This script takes two output files from NuShell and parse them to find 
#  which nucleus the files corresponds to.  Then it finds the spot where the 
#  the binding energy results are printed and puts them into a simple format for
#  use in FoldFileGen.  
#
# The first file should be the initial nucleus (target) and the second file should be the 
# final nucleus (residual)
#
# To find the A and Z of nuclei it looks for line with 'ia,iz' on it and prints the following numbers 
# To find the binding energies it looks for a line with 'proton (or neutron) bound state' and prints the   
# next set of lines containing 'radii'
#
# The output is:
# Initial iA iZ 
# state binding_energy -9
# ...
# Final fA fZ
# state binding_energy -9
# ...
#
# Where the -9 are column fillers 
#
###################################################################################
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


##clean up
rm -f ${ftemp1};
rm -f ${ftemp2};
