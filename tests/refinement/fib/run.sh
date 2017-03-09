#! /bin/bash

CBMC="/home/sumanth/cmi/thesis/cbmc/src/cbmc/cbmc"
REFINE_OPTION=" --refine-cpu"
TIMEOUT=300
VER_MSG="VERIFICATION" #verfication failed or success message
LOG_DIR="log_"`date +%s`

#filename, NUM, unwind, apply_refinement
function run_and_log {
    file_name="${1%.*}""_"$2

    if [ "$4" -eq "0" ]; then
	timeout $TIMEOUT $CBMC --unwind $3 -DNUM=$2 $1 > $LOG_DIR"/"$file_name 2>&1
    else
	timeout $TIMEOUT $CBMC $REFINE_OPTION --unwind $3 -DNUM=$2 $1 > $LOG_DIR"/"$file_name 2>&1
    fi
    
    if [ "$?" -eq "124" ]; then
	STATUS="TIMEOUT"
	DP_TIME=">$TIMEOUT"
    else
	STATUS=`tail -1 $LOG_DIR"/"$file_name`
	DP_TIME=`grep "Runtime decision procedure" $LOG_DIR"/"$file_name | cut -d':' -f2`
    fi
    echo $1", NUM="$2", unwind="$3", status="$STATUS", dp time="$DP_TIME >> $LOG_DIR"/result"
}
    
#timeout 100 ../../cbmc/src/cbmc/cbmc  --refine-cpu  --unwind 25  0_false_seq_inv.c

mkdir $LOG_DIR

#filename, NUM, unwind, apply_refinement
run_and_log fb_false.c 5 7 0
run_and_log fb_false_inv.c 5 7 1

run_and_log fb_true.c 5 7 0
run_and_log fb_true_inv.c 5 7 1

run_and_log fb2_false.c 6 8 0
run_and_log fb2_false_inv.c 6 8 1

run_and_log fb2_true.c 6 8 0
run_and_log fb2_true_inv.c 6 8 1

run_and_log fb3_false.c 11 15 0
run_and_log fb3_false_inv.c 11 15 1

run_and_log fb3_true.c 11 15 0
run_and_log fb3_true_inv.c 11 15 1


cat $LOG_DIR/result
    
