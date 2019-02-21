#!/bin/bash

. ${RUMPRUN_MKCONF}

${SOLO5SRC}/tenders/spt/solo5-spt hello.spt '{"cmdline":"hello.bin"}' > /tmp/verify_gc

sleep 2

bob=`grep lastgc /tmp/verify_gc`
num=`echo $bob | cut -d ':' -f2 | tr -dc '0-9'`
rnum=`echo "$num + 0" | bc -l`
if [ $rnum -gt 1000 ];
then
		echo -e "gc is working: \t $rnum";
else
		echo "gc is not working";
		exit 1;
fi;

bob=`grep gcs /tmp/verify_gc`
num=`echo $bob | cut -d ':' -f2 | tr -dc '0-9'`
rnum=`echo "$num + 0" | bc -l`
if [ $rnum -gt 0 ];
then
		echo -e "go_routine cnt is > 0: \t $rnum";
else
		echo "go_routine is not present";
		exit 1;
fi;
