#! /bin/bash

CBMC="/home/sumanth/cmi/thesis/cbmc/src/cbmc/cbmc"
REFINE_OPTION=" --refine-cpu"
TIMEOUT=100
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

#run_and_log 0_false_seq.c 5 10 0
#run_and_log 0_false_seq_inv.c 5 10 1

#run_and_log 0_false_seq.c 10 15 0
#run_and_log 0_false_seq_inv.c 10 15 1

#run_and_log 0_false_seq.c 15 20 0
#run_and_log 0_false_seq_inv.c 15 20 1

#run_and_log 0_false_seq.c 20 25 0
#run_and_log 0_false_seq_inv.c 20 25 1

#run_and_log 0_true_seq.c 5 10 0
#run_and_log 0_true_seq_inv.c 5 10 1

#run_and_log 0_true_seq.c 10 15 0
#run_and_log 0_true_seq_inv.c 10 15 1

#run_and_log 0_true_seq.c 15 20 0
#run_and_log 0_true_seq_inv.c 15 20 1

#run_and_log 0_true_seq.c 20 25 0
#run_and_log 0_true_seq_inv.c 20 25 1

run_and_log 1_false_seq.c 20 45 0
run_and_log 1_false_seq_inv.c 20 45 1

run_and_log 1_false_seq.c 25 55 0
run_and_log 1_false_seq_inv.c 25 55 1

run_and_log 1_false_seq.c 30 65 0
run_and_log 1_false_seq_inv.c 30 65 1

run_and_log 1_false_seq.c 50 105 0
run_and_log 1_false_seq_inv.c 50 105 1

run_and_log 1_true_seq.c 20 45 0
run_and_log 1_true_seq_inv.c 20 45 1

run_and_log 1_true_seq.c 25 55 0
run_and_log 1_true_seq_inv.c 25 55 1

run_and_log 1_true_seq.c 30 65 0
run_and_log 1_true_seq_inv.c 30 65 1

run_and_log 1_true_seq.c 50 105 0
run_and_log 1_true_seq_inv.c 50 105 1



cat $LOG_DIR/result
    
