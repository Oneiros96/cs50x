from cs50 import get_int


def main():
    number = get_int('Number: ')
    result = check(number)
    if result == 0 and visa(number) == True:
        print('VISA')
    elif result == 0 and amex(number) == True:
        print('AMEX')
    elif result == 0 and master(number) == True:
        print('MASTERCARD')
    else:
        print('INVALID')


def check(number):
    # Luhn's algorithm
    sum1 = 0
    sum2 = 0

    while number > 0:
        rest = number % 10  # last digit
        sum1 += rest  # sum of not multiplyed digits
        number = int(number / 10)  # delete last digit
        rest = number % 10  # new last digit
        rest = rest * 2
        sum2 = sum2 + int(rest / 10)  # if result >= 10
        sum2 = sum2 + (rest % 10)
        number = int(number / 10)
    result = (sum1 + sum2) % 10
    return result


def visa(number):
    # 13 digits beginning with 4
    if number >= 4000000000000 and number < 5000000000000:
        return True
    # 16 digits beginning with 4
    elif number >= 4000000000000000 and number < 5000000000000000:
        return True
    else:
        return False


def amex(number):
    # 15 digits starting with 34
    if number >= 340000000000000 and number < 350000000000000:
        return True
    # 15 digits starting with 37
    elif number >= 370000000000000 and number < 380000000000000:
        return True
    else:
        return False


def master(number):
    # 16 digits starting with 51,...,56
    if number >= 5100000000000000 and number < 5700000000000000:
        return True
    else:
        return False


main()