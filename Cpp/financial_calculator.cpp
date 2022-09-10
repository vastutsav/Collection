#include <iostream>
#include <algorithm>
#include <cmath>

const char DEBUG_ON = 'N';

// defining the magic numbers
const double ALLOWED_DEVIATION = 5000.0; // keeping it 5000 to speed up the algorithm
const int BUCKET_INTERVALS = 10;

// important milestone age
const int current_age = 32;
const int retirement_age = 50;
const int final_age = 80;

// expenses
const double current_expense_per_month = 20000;
const double yearly_one_time_expense = 25000;

// balances
int present_value = 1500000;

// rates
const double inflation_rate = 0.07;
const double equity_rate_of_return = 12.0/100.0;
const double debt_rate_of_return = 7.5/100.0;
const double yearly_investment_increment_rate = 0;
const double bank_rate_of_return = 4/100.0;


double get_rate() {
    int equity_alloc = 60;
    int debt_alloc = 40;

    return (equity_alloc/100.0 * equity_rate_of_return) + (debt_alloc/100.0 * debt_rate_of_return);

}

double get_current_yearly_expenditure() {
    return current_expense_per_month*12 + yearly_one_time_expense;
}

double get_inflated_yearly_expenditure(double inflation_rate, double expense) {
    return (1 + inflation_rate) * expense;
}

double get_money_needed_at_retirement ( int retirement_age,
                                        int final_age,
                                        double expense[101]) {
    
    double final_amount = 0.0;

    for (int age = retirement_age + 1; age <= final_age; ++age) {
        final_amount+=expense[age];
    }
    
    return final_amount;
}

void get_money_needed_every_year (double expense[101]) {

    double amount_for_the_age = get_current_yearly_expenditure();
    double amount_needed = 0.0;
    int age = current_age;

    do {
        if (DEBUG_ON == 'Y') {
            printf("age = <%d>, amount = <%.2lf>\n", age, amount_for_the_age);
        }
        expense[age] = amount_for_the_age;
        amount_for_the_age = get_inflated_yearly_expenditure(inflation_rate, amount_for_the_age);
        ++age;
    }while (age <= final_age);
}

double get_future_value_of_investment(  double present_value, 
                                        double yearly_investment,
                                        int years, 
                                        double yearly_increment_rate) {
    double amount = 0.0 + present_value;
    double interest_rate = get_rate();
    for (int i = 0; i < years; ++i) {
        amount = amount + yearly_investment;

        amount = amount * (1 + interest_rate);
        yearly_investment = yearly_investment * (1 + yearly_increment_rate);
    }
    return amount;
}

double get_required_yearly_investment(  double present_value, 
                                        double target_value,
                                        int years, 
                                        double yearly_increment_rate ) {

    double min_amt = 0;
    double max_amt = 1E7;
    double temp_amount = 0;

    double probable_amount;
    while(1) {
        probable_amount = (min_amt + max_amt) / 2.0;

        temp_amount = get_future_value_of_investment(present_value,
                                                     probable_amount,
                                                     years,
                                                     yearly_increment_rate);
        
        if (abs(target_value - temp_amount) <= ALLOWED_DEVIATION) {
            if (DEBUG_ON == 'Y') {
                printf ("In get_required_yearly_investment, temp_amount = <%.2f>\n", abs(target_value - temp_amount));
            }
            return probable_amount;
        } else if (temp_amount > target_value) {
            max_amt = probable_amount;
        } else {
            min_amt = probable_amount;
        }
    }

}

int get_equity_asset_alloc_glidepath(int age) {
    int interval = 5;
    return 100 - (age + 10)/interval * interval;
}

double get_rate_glidepath(int age) {
    int equity_alloc = get_equity_asset_alloc_glidepath(age);
    int debt_alloc = 100 - equity_alloc;

    return (equity_alloc/100.0 * equity_rate_of_return) + (debt_alloc/100.0 * debt_rate_of_return);
}


double get_future_value_of_investment_glidepath(   double present_value, 
                                                        double yearly_investment,
                                                        int years, 
                                                        double yearly_increment_rate,
                                                        int current_age) {
    double amount = 0.0 + present_value;
    for (int i = 0; i < years; ++i) {
        amount = amount + yearly_investment;

        amount = amount * (1.0 + get_rate_glidepath(current_age + i));
        yearly_investment = yearly_investment * (1 + yearly_increment_rate);
    }
    return amount;
}

double get_required_yearly_investment_glidepath(double present_value, 
                                                double target_value,
                                                int years, 
                                                double yearly_increment_rate,
                                                int current_age ) {

    double min_amt = 0;
    double max_amt = 1E7;
    double temp_amount = 0;

    double probable_amount;
    while(1) {
        probable_amount = (min_amt + max_amt) / 2.0;

        temp_amount = get_future_value_of_investment_glidepath( present_value,
                                                                probable_amount,
                                                                years,
                                                                yearly_increment_rate,
                                                                current_age);
        
        if (abs(target_value - temp_amount) <= ALLOWED_DEVIATION) {
            if (DEBUG_ON == 'Y') {
                printf ("In get_required_yearly_investment_glidepath, temp_amount = <%.2f>\n", abs(target_value - temp_amount));
            }
            return probable_amount;
        } else if (temp_amount > target_value) {
            max_amt = probable_amount;
        } else {
            min_amt = probable_amount;
        }
    }
    return -1;
}


double get_rate_bucket() {
    int equity_alloc = 30;
    int debt_alloc = 70;
    int bank_alloc = 0;

    return (equity_alloc/100.0 * equity_rate_of_return) + (debt_alloc/100.0 * debt_rate_of_return) + (bank_alloc/100.0 * bank_rate_of_return);
}

double get_future_value_of_investment_bucket(   double present_value, 
                                                double yearly_investment,
                                                int years, 
                                                double yearly_increment_rate) {
    double amount = 0.0 + present_value;
    double interest_rate = get_rate_bucket();
    for (int i = 0; i < years; ++i) {
        amount = amount + yearly_investment;
        amount = amount * (1 + interest_rate);
        yearly_investment = yearly_investment * (1 + yearly_increment_rate);
    }
    return amount;
}

double get_money_remaining_at_final_age_bucket (int retirement_age,
                                                int final_age,
                                                double corpus,
                                                double expenses[101]) {
    
    double min_amt = 0;
    double max_amt = 1E7 * 9;

    int remaining_years = final_age - retirement_age;
    int number_of_bucket_iterations = std::ceil(double(remaining_years)/BUCKET_INTERVALS);
    for (int i = 0; i < number_of_bucket_iterations; ++i) {
        int tmp_age = std::min(retirement_age+((i+1)*BUCKET_INTERVALS), final_age);
        double tmp_expense = 0.0;
        for (int age = retirement_age + i*BUCKET_INTERVALS + 1 ; age <= tmp_age ; ++age) {
            tmp_expense+=expenses[age];  
        }
        corpus = corpus - tmp_expense;
        if (corpus < 0) {
            return -ALLOWED_DEVIATION*2; // corpus is over
        }
        if ( i < number_of_bucket_iterations-1) { // do not need to invest in the final iteration
            corpus = get_future_value_of_investment_bucket( corpus,
                                                            0,
                                                            BUCKET_INTERVALS,
                                                            0);
        }
    }

    return corpus;
}

double get_money_needed_at_retirement_bucket (  int retirement_age,
                                                int final_age,
                                                double expense[101]) {
    
    double min_amt = 0.0;
    double max_amount = 10E7 * 9;
    double final_amount = 0.0;

    while (1) {
        final_amount = min_amt/2.0 + max_amount/2.0;
        double corpus_at_final_age = get_money_remaining_at_final_age_bucket(retirement_age, 
                                                                             final_age, 
                                                                             final_amount, 
                                                                             expense);

        if (abs(corpus_at_final_age) < ALLOWED_DEVIATION) {
            return final_amount;
        } else if (corpus_at_final_age > ALLOWED_DEVIATION) {
            max_amount = final_amount;
        } else {
            min_amt = final_amount;
        }
    }
    return -404; // error
}

int main () {

    int years_before_retirement = retirement_age - current_age + 1; 

    double expenses[101] = {0};

    get_money_needed_every_year(expenses);

    double money_needed_at_retirement = get_money_needed_at_retirement( retirement_age,
                                                                        final_age,
                                                                        expenses);

    double yearly_investment = get_required_yearly_investment(present_value, 
                                                              money_needed_at_retirement, 
                                                              years_before_retirement, 
                                                              yearly_investment_increment_rate);

    double monthly_investment = yearly_investment/12;

    double yearly_investment_glidepath = get_required_yearly_investment_glidepath(  present_value, 
                                                                                    money_needed_at_retirement, 
                                                                                    years_before_retirement, 
                                                                                    yearly_investment_increment_rate,
                                                                                    current_age);

    double monthly_investment_glidepath = yearly_investment_glidepath/12;

    double money_needed_at_retirement_with_bucket_strategy = get_money_needed_at_retirement_bucket( retirement_age,
                                                                                                    final_age,
                                                                                                    expenses);

    double yearly_investment_bucket = get_required_yearly_investment(present_value, 
                                                              money_needed_at_retirement_with_bucket_strategy, 
                                                              years_before_retirement, 
                                                              yearly_investment_increment_rate);

    double monthly_investment_bucket = yearly_investment_bucket/12;

    double yearly_investment_glidepath_bucket = get_required_yearly_investment_glidepath(  present_value, 
                                                                                    money_needed_at_retirement_with_bucket_strategy, 
                                                                                    years_before_retirement, 
                                                                                    yearly_investment_increment_rate,
                                                                                    current_age);

    double monthly_investment_glidepath_bucket = yearly_investment_glidepath_bucket/12;

    printf("at retirement age = <%ld>, required amount = <%.2lf>\n", retirement_age, money_needed_at_retirement);
    printf("at retirement age = <%ld>, required amount with Bucket strategy = <%.2lf>\n", retirement_age, money_needed_at_retirement_with_bucket_strategy);
    printf("required monthly investment = <%.2lf>\n", monthly_investment);
    printf("required monthly investment with bucket= <%.2lf>\n", monthly_investment_bucket);
    printf("required monthly investment with glidepath = <%.2lf>\n", monthly_investment_glidepath);
    printf("required monthly investment with glidepath and bucket = <%.2lf>\n", monthly_investment_glidepath_bucket);
    return 0;
}
