import csv
import sys


def main():

    # Check for correkt command-line usage
    if len(sys.argv) != 3:
        print('Usage: python dana.py <database.csv> <sequence.txt>')

    # Read database file into a variable
    database_file = open(sys.argv[1], 'r')
    # emumerate adss counter 'index' for each row of data
    persons = {}
    for index, row in enumerate(database_file):
        if index == 0:
            # Index 0 in csv file is ordered name,strand1,strand2 etc.. Strip is used to get rid auf ' ' and '\n' [1:] to start with 1st element instead of 0th
            strand = [strand for strand in row.strip().split(',')[1:]]
        else:
            current_row = row.strip().split(',')
            # Sets key to each strandset to [0] element of current row aka the name and adds all data in current_row besides element[0] to it
            persons[current_row[0]] = current_row[1:]
    # Read DNA sequence file into a variable
    sequence_file = open(sys.argv[2], 'r')
    sequence = sequence_file.read()
    # Find longest match of each STR in DNA sequence
    longest = [str(longest_match(sequence, each)) for each in strand]

    # Check database for matching profiles and print Name of person if found and no match if not found
    for name, data_set in persons.items():
        if data_set == longest:
            print(name)
            return
    print('No match')
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
