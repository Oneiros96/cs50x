-- overview over db
.schema
-- date &place only given information so ->
 SELECT description FROM crime_scene_reports WHERE street = 'Humphrey Street' AND year = 2021 AND month = '7' AND day = 28;
-- new informations gathered: in backery at 10:15, 3 witnesses
-- checking wich info bkery logs give at this time
SELECT activity, license_plate FROM bakery_security_logs WHERE year = 2021 AND month = '7' AND day = 28 AND hour = 10;
-- not useful yet, checking intervies
SELECT name, transcript FROM interviews WHERE year = 2021 AND month = '7' AND day = 28;
-- Ruth thief left within 10 minutes
-- Eugene thief withdraw money at Leggett Street earlyer this day
-- Raymond Thief called someone less then a minut, taking earlyst flight tomorrow

-- people names who left within 10 min
SELECT people.name
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.activity = 'exit'
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25;
-- possibel thiefes: Bruce, Vanessa, Berry, Luca, Sofia, Iman, Diana, Kelsey

-- people which withdraw Money this day
SELECT people.name
FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';
-- Bruce, Diana, Luca, Iman  (rest cant be the thief becaus didnt leave the backery at matcing time)
-- check 4 earlyst flight
Select flights.id, flights.destination_airport_id
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = 'Fiftyville'
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour, flights.minute
LIMIT 1;
--flight id 36 dest airp. 4
SELECT city FROM airports WHERE id = 4;
--thief escaped to New York City
--find out who of the 4 suspects was on that flight
SELECT people.name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36;
--remaining suspects Bruce & Luca
--last clue phonecalls this day under 60sec
SELECT caller, receiver, duration
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;
--9 possible calls need caller name
SELECT people.name, receiver, duration
FROM phone_calls
JOIN people on phone_calls.caller = people.phone_number
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;
--Bruce has to be the thief, luca didn't call anyone this day
--check who he called to get Accomplice number (375) 555-8161
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';
--he called Robin