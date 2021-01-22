#include <iostream>
#include <string>
#include <sstream>
#include "./string_calculator.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;


unsigned int digit_to_decimal(char digit) {
    if(digit == '0'|| digit == '1' || digit == '2' || digit == '3' || digit == '4' || digit == '5' || digit == '6' || digit == '7' || digit == '8' || digit == '9'){
        int deci = (int)digit - 48;
        return deci;
    }
    else{
        throw std::invalid_argument("");
    }
}

char decimal_to_digit(unsigned int decimal) {
    
    if(decimal == 0 || decimal == 1 || decimal == 2 || decimal == 3 || decimal == 4 || decimal == 5 || decimal == 6 || decimal == 7 || decimal == 8 || decimal == 9){
        char number = '0' + decimal;
        return number;
    }
    else{
        throw std::invalid_argument("");
    }
}

string trim_leading_zeros(string num){ 
    for(int i = 0;i < (int)num.size();i++){

        if(num.at(0) == '0'){
            while(num.at(0) == '0'){
            num.erase(0,1);
            if((int)num.size() == 1){
                if(num.at(0) != 0){
                    return num;
                    break;
                }
                else{
                    return "0";
                }
            }
            }
        }

        if(num.at(0) == '-'){
            while(num.at(1) == '0'){
            num.erase(1,1);
            if((int)num.size() == 2){
                if(num == "-0"){
                    return "0";
                }
                else{
                    return num;
                    break;
                }
            }
            }
        }
    }
    return num;
} 

string add(string lhs, string rhs) {
    if(lhs.at(0) == '-' && rhs.at(0) == '0'){
        return lhs;
    }
    if(rhs.at(0) == '-' && lhs.at(0) == '0'){
        return rhs;
    }
    //positive, positive
    if((lhs.at(0) == '0' || lhs.at(0) == '1'|| lhs.at(0) == '2'|| lhs.at(0) == '3'|| lhs.at(0) == '4'|| lhs.at(0) == '5'|| lhs.at(0) == '6'|| lhs.at(0) == '7'|| lhs.at(0) == '8'|| lhs.at(0) == '9') && (rhs.at(0) == '0' || rhs.at(0) == '1'|| rhs.at(0) == '2'|| rhs.at(0) == '3'|| rhs.at(0) == '4'|| rhs.at(0) == '5'|| rhs.at(0) == '6'|| rhs.at(0) == '7'|| rhs.at(0) == '8'|| rhs.at(0) == '9')){
        if(lhs.size() > rhs.size()){                                                    //adds leading zeros to right hand side number
            lhs.insert(0,"0");
            for(int i = 0; i < (int)lhs.size(); i++){
                while(lhs.size() != rhs.size()){
                    rhs.insert(0,"0");
                }
            }
        }
        else if(lhs.size() < rhs.size()){                                               //adds leading zeros to left hand side number
            rhs.insert(0,"0");
            for(int i = 0; i < (int)rhs.size(); i++){
                while(lhs.size() != rhs.size()){
                    lhs.insert(0,"0");
                }
            }
        }
        else if(lhs.size() == rhs.size()){
            lhs.insert(0,"0");
            rhs.insert(0,"0");
        }   

        int carry = 0;
        string stringResult = "";
        int result = 0;
        for(int i = lhs.size()-1; i >= 0; i--){
            int leftDigit = digit_to_decimal(lhs.at(i));
            int rightDigit = digit_to_decimal(rhs.at(i));
            int digitResult = (leftDigit + rightDigit) + carry;
            if(digitResult > 9){
                string empty = "";
                carry = 1;
                result = (digitResult - 10);
                stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
            }
            else if(digitResult < 10){
                carry = 0;
                string empty = "";
                stringResult.insert(0,empty.assign(1,decimal_to_digit(digitResult)));
            }
        }
        return trim_leading_zeros(stringResult);
    }

    //negative, negative
    else if(lhs.at(0) == '-' && rhs.at(0) == '-'){
        if(lhs.size() > rhs.size()){                                                    //adds leading zeros to right hand side number
            lhs.insert(1,"0");
            for(int i = 0; i < (int)lhs.size(); i++){
                while(lhs.size() != rhs.size()){
                    rhs.insert(1,"0");
                }
            }
        }
        else if(lhs.size() < rhs.size()){                                               //adds leading zeros to left hand side number
            rhs.insert(1,"0");
            for(int i = 0; i < (int)rhs.size(); i++){
                while(lhs.size() != rhs.size()){
                    lhs.insert(1,"0");
                }
            }
        }
        else if(lhs.size() == rhs.size()){
            lhs.insert(1,"0");
            rhs.insert(1,"0");
        }

    int carry = 0;
    string stringResult = "-";
    int result = 0;
    for(int i = lhs.size()-1; i > 0; i--){
        int leftDigit = digit_to_decimal(lhs.at(i));
        int rightDigit = digit_to_decimal(rhs.at(i));
        int digitResult = (leftDigit + rightDigit) + carry;
        if(digitResult > 9){
            string empty = "";
            carry = 1;
            result = (digitResult - 10);
            stringResult.insert(1,empty.assign(1,decimal_to_digit(result)));
        }
        else if(digitResult < 10){
            carry = 0;
            string empty = "";
            stringResult.insert(1,empty.assign(1,decimal_to_digit(digitResult)));
        }
    }
        return trim_leading_zeros(stringResult);
    }

    //positive, negative
    else if((lhs.at(0) == '0' || lhs.at(0) == '1'|| lhs.at(0) == '2'|| lhs.at(0) == '3'|| lhs.at(0) == '4'|| lhs.at(0) == '5'|| lhs.at(0) == '6'|| lhs.at(0) == '7'|| lhs.at(0) == '8'|| lhs.at(0) == '9') && (rhs.at(0) == '-')){
         rhs.erase(0,1);
         return subtract(lhs,rhs);
    }

    //negative, positive
    else if((lhs.at(0) == '-') && (rhs.at(0) == '1'|| rhs.at(0) == '2'|| rhs.at(0) == '3'|| rhs.at(0) == '4'|| rhs.at(0) == '5'|| rhs.at(0) == '6'|| rhs.at(0) == '7'|| rhs.at(0) == '8'|| rhs.at(0) == '9')){
        lhs.erase(0,1);
        lhs.swap(rhs);
        return subtract(lhs,rhs);
    }
    return "";
}

string subtract(string lhs, string rhs) {
    bool something = true;
    //positive, positive
    if((lhs.at(0) == '0' || lhs.at(0) == '1'|| lhs.at(0) == '2'|| lhs.at(0) == '3'|| lhs.at(0) == '4'|| lhs.at(0) == '5'|| lhs.at(0) == '6'|| lhs.at(0) == '7'|| lhs.at(0) == '8'|| lhs.at(0) == '9') && (rhs.at(0) == '0' || rhs.at(0) == '1'|| rhs.at(0) == '2'|| rhs.at(0) == '3'|| rhs.at(0) == '4'|| rhs.at(0) == '5'|| rhs.at(0) == '6'|| rhs.at(0) == '7'|| rhs.at(0) == '8'|| rhs.at(0) == '9')){
        if(lhs.size() > rhs.size()){                                                    //adds leading zeros to right hand side number
            lhs.insert(0,"0");
            for(int i = 0; i < (int)lhs.size(); i++){
                while(lhs.size() != rhs.size()){
                    rhs.insert(0,"0");
                }
            }

            int takeAway = 0;
            int result = 0;
            string stringResult = "";
            int digitResult = 0;
            
            for(int i = lhs.size()-1; i > 0; i--){
                int leftDigit = digit_to_decimal(lhs.at(i));
                int rightDigit = digit_to_decimal(rhs.at(i));
                digitResult = (leftDigit - rightDigit);
                if(takeAway != 0){
                    digitResult = ((leftDigit-1) - rightDigit);
                    leftDigit -= 1;
                }
                else if(takeAway == 0){
                    digitResult = (leftDigit - rightDigit);
                }
                if(digitResult < 0){
                    takeAway = 1;
                    result = (leftDigit + 10) - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
                if(digitResult >= 0){
                    takeAway = 0;
                    result = leftDigit - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
            }
            return trim_leading_zeros(stringResult);

        }
        else if(lhs.size() < rhs.size()){                                               //adds leading zeros to left hand side number
            rhs.insert(0,"0");
            for(int i = 0; i < (int)rhs.size(); i++){
                while(lhs.size() != rhs.size()){
                    lhs.insert(0,"0");
                }
            }

            lhs.swap(rhs);
            
            int takeAway = 0;
            int result = 0;
            string stringResult = "";
            int digitResult = 0;
            
            for(int i = lhs.size()-1; i > 0; i--){
                int leftDigit = digit_to_decimal(lhs.at(i));
                int rightDigit = digit_to_decimal(rhs.at(i));
                digitResult = (leftDigit - rightDigit);
                if(takeAway != 0){
                    digitResult = ((leftDigit-1) - rightDigit);
                    leftDigit -= 1;
                }
                else if(takeAway == 0){
                    digitResult = (leftDigit - rightDigit);
                }
                if(digitResult < 0){
                    takeAway = 1;
                    result = (leftDigit + 10) - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
                if(digitResult >= 0){
                    takeAway = 0;
                    result = leftDigit - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
            }
            return "-" + trim_leading_zeros(stringResult);

        }
        else if(lhs.size() == rhs.size()){
            if(lhs == rhs){
                return "0";
            }
            lhs.insert(0,"0");
            rhs.insert(0,"0");

            for(int i = 1; i < (int)lhs.size(); i++){
                    if(digit_to_decimal(lhs.at(i)) < digit_to_decimal(rhs.at(i))){
                        lhs.swap(rhs);
                        something = false;
                        cout << "something is false" << endl;
                        break;
                    }
                    else if(digit_to_decimal(lhs.at(i)) > digit_to_decimal(rhs.at(i))){
                        break;
                    }
            }

            int takeAway = 0;
            int result = 0;
            string stringResult = "";
            int digitResult = 0;
            
            for(int i = lhs.size()-1; i > 0; i--){
                int leftDigit = digit_to_decimal(lhs.at(i));
                int rightDigit = digit_to_decimal(rhs.at(i));
                digitResult = (leftDigit - rightDigit);
                if(takeAway != 0){
                    digitResult = ((leftDigit-1) - rightDigit);
                    leftDigit -= 1;
                }
                else if(takeAway == 0){
                    digitResult = (leftDigit - rightDigit);
                }
                if(digitResult < 0){
                    takeAway = 1;
                    result = (leftDigit + 10) - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
                if(digitResult >= 0){
                    takeAway = 0;
                    result = leftDigit - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
            }
            
            if(something == false){
                return "-" + trim_leading_zeros(stringResult);
            }
            else if (something == true){
                return trim_leading_zeros(stringResult);
            }           
        }
    }

    //negative, negative
    else if(lhs.at(0) == '-' && rhs.at(0) == '-'){
        if(lhs == rhs){
            return "0";
        }
        bool something2 = false;
        lhs.erase(0,1);
        rhs.erase(0,1);

        if(lhs.size() > rhs.size()){                                                    //adds leading zeros to right hand side number
            lhs.insert(0,"0");
            for(int i = 0; i < (int)lhs.size(); i++){
                while(lhs.size() != rhs.size()){
                    rhs.insert(0,"0");
                }
            }

            int takeAway = 0;
            int result = 0;
            string stringResult = "";
            int digitResult = 0;
            
            for(int i = lhs.size()-1; i > 0; i--){
                int leftDigit = digit_to_decimal(lhs.at(i));
                int rightDigit = digit_to_decimal(rhs.at(i));
                digitResult = (leftDigit - rightDigit);
                if(takeAway != 0){
                    digitResult = ((leftDigit-1) - rightDigit);
                    leftDigit -= 1;
                }
                else if(takeAway == 0){
                    digitResult = (leftDigit - rightDigit);
                }
                if(digitResult < 0){
                    takeAway = 1;
                    result = (leftDigit + 10) - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
                if(digitResult >= 0){
                    takeAway = 0;
                    result = leftDigit - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
            }
            return "-" + trim_leading_zeros(stringResult);

        }
        else if(lhs.size() < rhs.size()){                                               //adds leading zeros to left hand side number
            rhs.insert(0,"0");
            for(int i = 0; i < (int)rhs.size(); i++){
                while(lhs.size() != rhs.size()){
                    lhs.insert(0,"0");
                }
            }

            lhs.swap(rhs);
            
            int takeAway = 0;
            int result = 0;
            string stringResult = "";
            int digitResult = 0;
            
            for(int i = lhs.size()-1; i > 0; i--){
                int leftDigit = digit_to_decimal(lhs.at(i));
                int rightDigit = digit_to_decimal(rhs.at(i));
                digitResult = (leftDigit - rightDigit);
                if(takeAway != 0){
                    digitResult = ((leftDigit-1) - rightDigit);
                    leftDigit -= 1;
                }
                else if(takeAway == 0){
                    digitResult = (leftDigit - rightDigit);
                }
                if(digitResult < 0){
                    takeAway = 1;
                    result = (leftDigit + 10) - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
                if(digitResult >= 0){
                    takeAway = 0;
                    result = leftDigit - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
            }
            return trim_leading_zeros(stringResult);

        }
        else if(lhs.size() == rhs.size()){
            lhs.insert(0,"0");
            rhs.insert(0,"0");
            
            for(int i = 1; i < (int)lhs.size(); i++){
                    if(digit_to_decimal(lhs.at(i)) < digit_to_decimal(rhs.at(i))){
                        lhs.swap(rhs);
                        something2 = true;
                        break;
                    }
                    else if(digit_to_decimal(lhs.at(i)) > digit_to_decimal(rhs.at(i))){
                        break;
                    }
            }   

            int takeAway = 0;
            int result = 0;
            string stringResult = "";
            int digitResult = 0;
            
            for(int i = lhs.size()-1; i > 0; i--){
                int leftDigit = digit_to_decimal(lhs.at(i));
                int rightDigit = digit_to_decimal(rhs.at(i));
                digitResult = (leftDigit - rightDigit);
                if(takeAway != 0){
                    digitResult = ((leftDigit-1) - rightDigit);
                    leftDigit -= 1;
                }
                else if(takeAway == 0){
                    digitResult = (leftDigit - rightDigit);
                }
                if(digitResult < 0){
                    takeAway = 1;
                    result = (leftDigit + 10) - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
                if(digitResult >= 0){
                    takeAway = 0;
                    result = leftDigit - rightDigit;
                    string empty = "";
                    stringResult.insert(0,empty.assign(1,decimal_to_digit(result)));
                }
            }

            if(something2 == false){
                return "-" + trim_leading_zeros(stringResult);
            }
            else if (something2 == true){
                return trim_leading_zeros(stringResult);
            }            
        }

    }

    //positive, negative
    else if((lhs.at(0) == '0' || lhs.at(0) == '1'|| lhs.at(0) == '2'|| lhs.at(0) == '3'|| lhs.at(0) == '4'|| lhs.at(0) == '5'|| lhs.at(0) == '6'|| lhs.at(0) == '7'|| lhs.at(0) == '8'|| lhs.at(0) == '9') && (rhs.at(0) == '-')){
        rhs.erase(0,1);
        return add(lhs,rhs);
    }

    //negative, positive
    else if((lhs.at(0) == '-') && (rhs.at(0) == '1'|| rhs.at(0) == '2'|| rhs.at(0) == '3'|| rhs.at(0) == '4'|| rhs.at(0) == '5'|| rhs.at(0) == '6'|| rhs.at(0) == '7'|| rhs.at(0) == '8'|| rhs.at(0) == '9')){
        lhs.erase(0,1);
        return "-" + add(lhs,rhs);
    }
    return "";
}

string multiply(string lhs, string rhs) {
    int x = 0;
    int lefSize = lhs.size();
    int rightSize = rhs.size();
    int mult = 0;
    bool neg = false;
    int carry = 0;
    bool booleanCarryOver = false;

    if (lhs.at(0) == '-' && rhs.at(0) == '-'){
        lhs.at(0) = '0';
        rhs.at(0) = '0';
        lhs = trim_leading_zeros(lhs);
        rhs = trim_leading_zeros(rhs);

        lefSize = lhs.size();
        rightSize = rhs.size();
    }
    else if ((lhs.at(0) == '0' || lhs.at(0) == '1' || lhs.at(0) == '2' || lhs.at(0) == '3' || lhs.at(0) == '4' || lhs.at(0) == '5' || lhs.at(0) == '6' || lhs.at(0) == '7' || lhs.at(0) == '8' || lhs.at(0) == '9') && (rhs.at(0) == '-')){
        rhs.at(0) = '0';
        rhs = trim_leading_zeros(rhs);
        rightSize = rhs.size();
        neg = true;
    }
    else if ((lhs.at(0) == '-') && (rhs.at(0) == '0' || rhs.at(0) == '1' || rhs.at(0) == '2' || rhs.at(0) == '3' || rhs.at(0) == '4' || rhs.at(0) == '5' || rhs.at(0) == '6' || rhs.at(0) == '7' || rhs.at(0) == '8' || rhs.at(0) == '9')){
        lhs.at(0) = '0';
        lhs = trim_leading_zeros(lhs);
        lefSize = lhs.size();
        neg = true;
    }
    
    if (digit_to_decimal(lhs.at(0)) == 0 || digit_to_decimal(rhs.at(0)) == 0){
        return "0";
    }

    int sizeLittle;
    int sizeHuge;
    string stringCarry;

    if (lefSize > rightSize){
        sizeLittle = rightSize;
        sizeHuge = lefSize;
    }
    else if (lefSize < rightSize){
        sizeLittle = lefSize;
        sizeHuge = rightSize;
        stringCarry = lhs;
        lhs = rhs;
        rhs = stringCarry;
    }
    else {
        sizeLittle = lefSize;
        sizeHuge = rightSize;
    }

    string something;
    string product;
    string productInitial;
    string fin_product;

    for (int i = sizeLittle - 1; i >= 0; i--){
        for (int j = sizeHuge - 1; j >= 0; j--){
            if (booleanCarryOver){
                mult = 0;
                mult = (digit_to_decimal(lhs.at(j)) * digit_to_decimal(rhs.at(i))) + carry;
                carry = 0;
                booleanCarryOver = false;
            }
            else{
                mult = (digit_to_decimal(lhs.at(j)) * digit_to_decimal(rhs.at(i)));
            }

            if (mult >= 10){
                carry = mult / 10;
                something = decimal_to_digit(mult % 10);
                productInitial.insert(0, something);
                booleanCarryOver = true;
            }
            else{
                something = decimal_to_digit(mult);
                productInitial.insert(0, something);
            }

            if (j == 0 && booleanCarryOver){
                something = decimal_to_digit(carry);
                productInitial.insert(0, something);
                booleanCarryOver = false;
                carry = 0;
            }
        }

        if ((sizeLittle - i) == 1){
            product = productInitial;
        }
        else{
            if ((sizeLittle - i) == 2){
                productInitial.append("0");
                x++;
                fin_product = add(product, productInitial);
                carry = 0;
            }
            else{
                for (int k = 0; k <= x; k++){
                    productInitial.append("0");
                }
                x++;
                fin_product = add(productInitial, fin_product);
            }
        }

        if (i == 0 && carry >= 10){
            something = decimal_to_digit(carry);
            productInitial.insert(0, something);
        }

        if (i == 0 && sizeLittle == 1){
            fin_product = product;
        }
        productInitial.clear();
    }

    if(neg == true){
        fin_product.insert(0, "-");
    }

    return fin_product;
}