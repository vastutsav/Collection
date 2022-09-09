#include <iostream>


const char DEBUG_ON = 'N';

// defining the magic numbers
const double ALLOWED_DEVIATION = 5000; // keeping it 5000 to speed up the algorithm

// important milestone age
const int current_age = 34;
const int retirement_age = 50;
const int final_age = 80;

// expenses
const double current_expense_per_month = 20000;
const double yearly_one_time_expense = 25000;

// rates
const double inflation_rate = 0.07;
const double equity_rate_of_return = 12.0/100.0;
const double debt_rate_of_return = 7.5/100.0;



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

double get_money_needed_at_retirement () {
    
    double amount_for_the_age = get_current_yearly_expenditure();
    double amount_needed = 0.0;

    if (DEBUG_ON == 'Y') {
        std::cout << "age, amount" << std::endl;
        printf("%d, %.2lf\n", current_age, amount_for_the_age);
    }
    for (int i = 1; (i + current_age) <= final_age; ++i) {
        amount_for_the_age = get_inflated_yearly_expenditure(inflation_rate, amount_for_the_age);
        if (DEBUG_ON == 'Y') {
            printf("%d, %.2lf\n", current_age + i, amount_for_the_age);
        }

        if (i+current_age > retirement_age) {
            amount_needed+=amount_for_the_age;
        }
    }
    return amount_needed;
}

double get_money_needed_at_retirement_bucket () {
    
    return 0.0;
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
                printf ("In get_required_yearly_investment, temp_amount = <%.2f>\n", abs(target_value - temp_amount));
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

int main () {
    int present_value = 1500000;

    int years_before_retirement = retirement_age - current_age + 1; 

    const double yearly_investment_increment_rate = 0;

    double money_needed_at_retirement = get_money_needed_at_retirement();
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

    printf("at retirement age = <%ld>, required amount = <%.2f>\n", retirement_age, money_needed_at_retirement);
    printf("required monthly investment = <%.2lf>\n", monthly_investment);
    printf("required monthly investment with glidepath = <%.2lf>\n", monthly_investment_glidepath);
    return 0;
}
