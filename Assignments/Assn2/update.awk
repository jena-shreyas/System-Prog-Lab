#!/usr/bin/gawk -f

# Name : Shreyas Jena
# Roll  : 20CS30049
# Assignment : Assignment 2

BEGIN{

    FS = ":"                #Input field separator
    OFS = ":"               #Output field separator
    #days of month
    months["01"] = "January"; months["02"] = "February"; months["03"] = "March"; months["04"] = "April"
    months["05"] = "May"; months["06"] = "June"; months["07"] = "July"; months["08"] = "August"
    months["09"] = "September"; months["10"] = "October"; months["11"] = "November"; months["12"] = "December"
    filename = ARGV[1]
    idx = 1                 #index of the output array
    balance = 0             #balance of the account
    interest = 0            #interest of the account
    year_changed = 0        #flag to indicate if the year has changed
    update_needed = 0       #flag to indicate if the balance needs to be updated
    interest_added = 0      #flag to indicate if the interest has been added
    prev_date = ""          #previous date
}

#function to count no. of days passed in year
function count_days(date1){

    n1 = split(date1, date1_split, "-")
    day_ = date1_split[1]
    month_ = date1_split[2]
    year_ = date1_split[3]
    days_of_month[1] = 31; days_of_month[3] = 31; days_of_month[4] = 30; days_of_month[5] = 31; 
    days_of_month[6] = 30; days_of_month[7] = 31; days_of_month[8] = 31; days_of_month[9] = 30; 
    days_of_month[10] = 31; days_of_month[11] = 30; days_of_month[12] = 31

    #check if the year is a leap year
    if (year_ % 4 == 0){
        if (year_ % 100 == 0){
            if (year_ % 400 == 0){

                days_of_month[2] = 29
                is_leap_year = 1
            }
            else{
                days_of_month[2] = 28
                is_leap_year = 0
            }
        }
        else{
            is_leap_year = 1
            days_of_month[2] = 29
        }
    }
    else{
        days_of_month[2] = 28
        is_leap_year = 0
    }
    
    total_days = 0
    for (i = 1; i < month_; i++){
        total_days += days_of_month[i]
    }

    return (total_days + day_)
}

#function to check if year has changed
function isYearChanged(date_a, date_b){

    n_a = split(date_a, date_a_split, "-")
    n_b = split(date_b, date_b_split, "-")

    if (date_a_split[3] != date_b_split[3])
        return 1
    else
        return 0
}

{   
    #flag variable to check if year has changed
    year_changed = isYearChanged(prev_date, $1)
}

{
    #split date into day, month and year
    date = $1
    n = split(date, date_split, "-")
    day = date_split[1]
    month = date_split[2]
    year = date_split[3]
}

{   
    #if update is needed, update flag variable
    if ($4 == ""){

        if (update_needed == 0){

            print "+++ New transactions found"
            print "Last balance = " int(balance)
        }
        update_needed = 1
    }
}

{   
    #if end of year interest line is already added to passbook, update flag variable
    if (day == 31 && month == 12)
        interest_added = 1
}

{   #at start of year, reset yearly interest to zero
    # if end of year interest has not been added to balance, calculate it and add it to passbook
    if (day == 1 && month == 1 && prev_date != $1){

        # if end of year interest has not been added to balance, calculate it and add it to passbook
        if (interest_added == 0){

            days_diff = count_days("31-12-" year-1) - count_days(prev_date)
            print "Days diff = " days_diff
            if (is_leap_year)
            interest_inc = 5/(100 * 366) * days_diff * balance         
            else
            interest_inc = 5/(100 * 365) * days_diff * balance

            interest += interest_inc
            print "Interest = " int(interest)
            balance += interest
            output[idx++] = "31-12-" year-1 ":" int(interest) ":" int(balance) ":INTEREST"

        }

        interest = 0            #reset yearly interest to zero
        days_till_now = 0       #reset days passed till now to zero
        interest_added = 0      #reset interest added flag to zero
    }
}

{   #for all entries other than when the account was opened, update yearly interest
    if (NR > 1){

        days_diff = count_days(date) - days_till_now
        print "Days diff = " days_diff
        if (is_leap_year)
            interest_inc = 5/(100 * 366) * days_diff * balance  
        else
            interest_inc = 5/(100 * 365) * days_diff * balance

        #if prev transaction didn't happen on same day, add interest to balance 
        if (prev_date != $1 && !(day == 1 && month == 1)){
            interest += interest_inc
            print "Interest = " int(interest)
        }
    }
    days_till_now = count_days(date)
}

{   #if balance has not been updated in the current records, update it and print details of transaction
    if (update_needed){

        if ($2 != ""){      #Money credited

            balance += $2
            #printf("%s %s, %-8s \t Credit of %d for %-25s \t Balance = %d\n", months[month], day, year, $2, $5, balance)
        }
        if ($3 != ""){      #Money debited

            balance -= $3
            #printf("%s %s, %-8s \t Debit of %d for %-25s \t Balance = %d\n", months[month], day, year, $3, $5, balance)
        }
    }
}

{ 
    prev_date = $1                  #update prev_date
    #append computed records to output array
    if (NR >= 1 && $4 != "")
        output[idx++] = $0
    if ($4 == "")
        output[idx++] = $1 ":" $2 ":" $3 ":" int(balance) ":" $5

}

{   #if balance is given in records, update its value
    if ($4 != "")
        balance = $4
}

END{
    #format and print updated passbook in account.txt
    printf("%s\n",output[1]) > filename
    for (i = 2; i < idx; i++){
        print output[i] >> filename
    }
    
    #if passbook needs no update
    if (update_needed == 0)
        print "+++ No new transactions found"   

    #print interest of current year upto last transaction
    print "+++ Interest of this year up to the last transaction = " int(interest + 0.5)
}

