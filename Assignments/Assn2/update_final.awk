#!/usr/bin/gawk -f

# NAME : PRANAV NYATI
# ROLL : 20CS30037

# this function finds the number of days between two consecutive transactions only when the year is same
function date_difference(date_prev, date_cur){
    diff = 0   #refers to the days difference

    # if both the transaction dates are of same month and year
    if(int(date_prev[2]) == int(date_cur[2]))
        return int(date_cur[1]) - int(date_prev[1])


    # if both the transaction dates are of different months in the same year

    # condition for leap year
    if(int(date_prev[3])%4 == 0){
        
        diff += leap_days[int(date_prev[2])] - int(date_prev[1]) + 1

        month_diff = int(date_cur[2]) - int(date_prev[2]) - 1
        for (k = 1; k <= month_diff ; k++){
            diff += leap_days[int(date_prev[2]) + k]
        }

        diff += int(date_cur[1]) - 1
    }
    # condition for ordinary year
    else{

        diff += ord_days[int(date_prev[2])] - int(date_prev[1]) + 1

        month_diff = int(date_cur[2]) - int(date_prev[2]) - 1
        for (k = 1; k <= month_diff ; k++){
            diff += ord_days[int(date_prev[2]) + k]
        }

        diff += int(date_cur[1]) - 1
    }
    return diff
}


# function to give the interest rate based on whether year is a leap year or non-leap year
function interest_rate(year){
    if (year%4 == 0)
        return interest_rate_leap
    return interest_rate_ord
}

BEGIN{
    FS = ":"
    
    # month_names array stores the names of the months
    Months = "January_February_March_April_May_June_July_August_September_October_November_December"
    month_ctr = split(Months, month_names, "_")

    # leap_days array stores the no of days in the months of a leap year in sequential order
    Leap_year_days = "31_29_31_30_31_30_31_31_30_31_30_31"
    split(Leap_year_days, leap_days, "_")

    # ord_days array stores the no of days in the months of a non_leap year in sequential order
    Ord_year_days = "31_28_31_30_31_30_31_31_30_31_30_31"
    split(Ord_year_days, ord_days, "_")
    
    interest_rate_ord = 5/(100*365)     # daily interest rate for a non-leap year
    interest_rate_leap = 5/(100*366)    # daily interest rate for a leap year
    
    year_end[1] = "31"
    year_end[2] = "12"
    year_start[1] = "01"
    year_start[2] = "01"

    prev_trans = "NONE"  # variable to store the type of transaction of a previous transaction
    output = ""          # varibale to store the text output to be overwritten in the original account.txt file
}

{
    count1 = split($1, cur_trs_date , "-") # splitting current date into date, month , year

    # stores the account opening data and account balance when a new account is opened
    if($5 == "ACCOUNT OPENED"){ 
        split($1, prev_trs_date, "-")
        start_balance = int($4)
        year_start[3] = prev_trs_date[3]
        year_end[3] = prev_trs_date[3]
    }

    cur_year = int(cur_trs_date[3])   # year of current transaction
    prev_year = int(prev_trs_date[3]) # year of previous transaction

    # if the condition is met, keep adding to current yearly interest
    if(cur_year == prev_year){
        cur_year_interest += interest_rate(cur_year)*(date_difference(prev_trs_date, cur_trs_date))*current_balance
        print "Interest = " int(cur_year_interest)
    }

    # if cur_year and prev_year are different, we compute the interest of the prev_year, and start calculating interest of current year
    else if(cur_year != prev_year){
        prev_year_interest = cur_year_interest

        year_end[3] = prev_year
        print "Current balance = " current_balance
        prev_year_interest += interest_rate(prev_year)*(date_difference(prev_trs_date, year_end))*current_balance
        prev_year_interest = int(prev_year_interest + 0.5)
        print "Yearly interest = " prev_year_interest
        current_balance += prev_year_interest  # adding previous year;s interest to balance

        year_start[3] = cur_year
        cur_year_interest = interest_rate(cur_year)*(date_difference(year_start, cur_trs_date))*current_balance
       
        prev_date = year_end[1] "-" year_end[2] "-" year_end[3]

        if(prev_trans != "INTEREST" && prev_trans != "NONE"){  # appending prev year interest to output to display in text file
            output = output prev_date ":" prev_year_interest ":" $3 ":" current_balance ":INTEREST\n"  
            #printf("%s %s, %-8s \t Credit of %d for %-25s \t Balance = %d\n", month_names[int(year_end[2])], year_end[1], year_end[3], prev_year_interest, "YEARLY INTEREST", current_balance)
        }
    }

    # all those transactions for which the passbook is updated, we append them without a change 
    if($4 != ""){
        current_balance = int($4)
        output = output $0 "\n"
    }

    # if the balance for a given transaction is not given, it means starting from that transaction, we need to update the balance
    else{
        if(count_new_trsn == 0){ 
            printf("+++ New transactions found\n") 
            printf("Last balance = %d\n", current_balance) 
        }

        count_new_trsn++

        # if there is a credit to the account in a transaction
        if($2 != ""){
            current_balance += int($2)
            #printf("%s %s, %-8s \t Credit of %d for %-25s \t Balance = %d\n", month_names[int(cur_trs_date[2])], cur_trs_date[1], cur_trs_date[3], int($2), $5, current_balance) 
        }

        # if there is a debit from the account in a transaction
        else if($3 != ""){
            current_balance -= int($3)
            #printf("%s %s, %-8s \t Debit of %d for %-25s \t Balance = %d\n", month_names[int(cur_trs_date[2])], cur_trs_date[1], cur_trs_date[3], int($3), $5, current_balance) 
        }
        
        # appending the updated transaction with the balance to output to be displayed in text file
        output = output $1 ":" $2 ":" $3 ":" current_balance ":" $5 "\n" 
        
    }
    
    # need to store the date of the current transaction as the date of previous transaction for the next record to be able to calculate the interest
    for (j = 1; j <= 3; j++){
        prev_trs_date[j] = cur_trs_date[j]
    }

    prev_trans = $5 # assigning current type of transaction as prev_trans for referencing in the next transaction
}

END{
    if(count_new_trsn == 0){
        printf("+++ No new transactions found\n")
    }
    printf("+++ Interest of this year up to the last transaction = %d\n", int(cur_year_interest + 0.5)) 
    
    # writing the updated output to account.txt 
    printf("%s", output) > "account.txt" 
}
    
