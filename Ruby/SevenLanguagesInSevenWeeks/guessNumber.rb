#!/usr/bin/env ruby
# write a program that picks a random number. Let a player guess the number, telling the player whether the guess is too low or too high.

number = rand(10)
turns = 0

while true

  puts "Please enter your guess\n"
  turns+=1
  guess = Integer(gets)
  if guess == number
    puts "You guessed it right in #{turns} turns. The number is #{guess}\n";
    break
  elsif guess < number
    puts "Your guess #{guess} is too low\nPlease try again\n"
  else
    puts "Your guess #{guess} is too high\nPlease try again\n"
  end
end
