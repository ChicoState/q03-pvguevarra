/**
 * Unit Tests for the class
 **/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
protected:
	GuesserTest() {}		   // constructor runs before each test
	virtual ~GuesserTest() {}  // destructor cleans up after tests
	virtual void SetUp() {}	   // sets up before each test (after constructor)
	virtual void TearDown() {} // clean up after each test, (before destructor)
};


TEST(GuesserTest, secret_becomes_truncated_if_greater_than_32)
{
	Guesser guess("abcabcabcabcabcabcabcabcabcSecretGuess");
	ASSERT_TRUE(guess.match("abcabcabcabcabcabcabcabcabcSecre"));// Should match after Truncated 
}

TEST(GuesserTest, guess_fails_after_secret_truncated)
{
	Guesser guess("abcabcabcabcabcabcabcabcabcSecretGuess");
	ASSERT_FALSE(guess.match("abcabcabcabcabcabcabcabcabcSecretGuess"));
}

TEST(GuesserTest, guess_is_matched_on_first_try)
{
	Guesser guess("Password");
	ASSERT_TRUE(guess.match("Password"));
}

TEST(GuesserTest, guess_remain_decreases_after_wrong_guess)
{
	Guesser guess("Password");
	guess.match("Passworr");
	ASSERT_EQ(guess.remaining(), 2);
}

TEST(GuesserTest, guess_remaining_resets_after_correct_guess)
{
	Guesser guess("Password");
	guess.match("Passworr");
	guess.match("Password");
	ASSERT_EQ(guess.remaining(), 3); // Fails due to bug
}

TEST(GuesserTest, guess_locks_if_brute_force_detected)
{
	Guesser guess("Password");
	guess.match("aaaaaaaaa");
	ASSERT_FALSE(guess.match("Password"));
}

TEST(GuesserTest, empty_secret_with_empty_guess)
{
	Guesser guess("");
	ASSERT_TRUE(guess.match(""));
}

TEST(GuesserTest, locks_after_three_incorrect_guesses)
{
	Guesser guess("Password");
	guess.match("Passworr");
	guess.match("Passwora");
	guess.match("passworc");
	ASSERT_EQ(guess.remaining(), 0);
}

TEST(GuesserTest, remaining_countdown_after_lock_occurs)
{
	Guesser guess("Password");
	guess.match("aaaaaaaaa");
	guess.match("Passwora");
	guess.match("passwods");
	ASSERT_EQ(guess.remaining(), 1); // Fails due to implementation. Remaining doesn't drop after being locked. I tested it assuming it does
}