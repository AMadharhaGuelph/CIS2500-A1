#include "madharhaAnkushA1.h"

/******
 openFileForReading: Opens the passed file name for reading
 In: char *fileName
 Out: FILE*
 Post: File gets opened for reading and is returned (NULL is returned if error occurs)
*******/
FILE *openFileForReading(char *fileName)
{
    // fptr is declared and intialed then is opened for reading
    FILE *fptr = NULL;
    fptr = fopen(fileName, "r");

    // if fptr is NULL, print an error message and return NULL
    if (fptr == NULL)
    {
        printf("Error opening %s for reading\n", fileName);
        return NULL;
    }

    // return fptr
    return fptr;
}

/******
 readMovies: Reads movie names from a file and stores them in an array
 In: FILE* file, char movieNames[][]
 Out: int
 Post: movieNames array is populated with movies
*******/
int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR])
{
    // declare and intialize variables
    int lineCount = 0;
    char temp[MAX_STR];
    int i = 0;

    // if file is NULL, return 0
    if (file == NULL)
    {
        return 0;
    }
    // Iterate through each character of the file (to count lines)
    for (char c = getc(file); c != EOF; c = getc(file))
    {
        // If the current character in the file is a newline character, increment lineCount
        if (c == '\n')
        {
            lineCount++;
        }
    }
    // if the lineCount does not equal the number of movies, return 0
    if (lineCount != NUMBER_MOVIES)
    {
        return 0;
    }

    // rewind the file to start at the begginning
    rewind(file);
    // Iterate to the end of the file storing each line
    while (fgets(temp, MAX_STR, file))
    {
        // remove the \n character
        temp[strlen(temp) - 1] = '\0';
        // copy the current movie name (in temp) into movieNames array, increment i
        strcpy(movieNames[i], temp);
        i++;
    }

    // Return 1 to indicate success
    return 1;
}

/******
 readReviews: Reads reviers' name and feedback from a file and stores them in an array
 In: FILE* file, reviewStruct reviews[][]
 Out: int
 Post: reviews array (of type reviewStruct) is populated with reviewrs' names and feedback
*******/
int readReviews(FILE *file, struct reviewStruct reviews[NUMBER_REVIEWERS])
{
    // Declare and Initialize variable
    int lineCount = 0;
    char temp[MAX_STR];
    char *token;
    int i = 0;
    int j = 0;

    // if file is NULL, return 0
    if (file == NULL)
    {
        return 0;
    }
    // Iterate through each character of the file 
    for (char c = getc(file); c != EOF; c = getc(file))
    {
        // If the current character is \n then increment lineCount
        if (c == '\n')
        {
            lineCount++;
        }
    }
    // if lineCount does not equal number of reviewers then return 0
    if (lineCount != NUMBER_REVIEWERS)
    {
        return 0;
    }

    // Rewind the file to read from beginning
    rewind(file);
    // Iterate through the file while storing each line
    while (fgets(temp, MAX_STR, file))
    {
        // Remove \n character.
        temp[strlen(temp) - 1] = '\0';
        // tokenize temp using a space as a delimeter
        token = strtok(temp, " ");
        // Iterate through tokens
        while (token != NULL)
        {
            // If the current token is a y, store it and increment j
            if (strcmp(token, "Y") == 0 || strcmp(token, "y") == 0)
            {
                reviews[i].feedback[j] = 1;
                j++;
            }
            // else if the current token is n, store it and increment j
            else if (strcmp(token, "N") == 0 || strcmp(token, "n") == 0)
            {
                reviews[i].feedback[j] = 0;
                j++;
            }
            // otherwise store the reviewer name 
            else
            {
                strcpy(reviews[i].reviewer, token);
            }
            token = strtok(NULL, " ");
        }
        // increment i and reset j to 0
        i++;
        j = 0;
    }

    // Return 1 to indicate success
    return 1;
}

/******
 getMostCriticalReviewers: Find a list of the most critical reviewers and store then in an array
 In: reviewStruct reviews, char mostCriticalReviewers[][]
 Out: int
 Post: char mostCriticalReviewrs[][] is populated with the most critical reviewers' names
*******/
int getMostCriticalReviewers(struct reviewStruct reviews[NUMBER_REVIEWERS], char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR])
{
    // Declare and Intialize variables
    int maxNegative = 0;
    int currNegative = 0;
    int index = 0;

    // Iterate through the number of reviewers
    for (int i = 0; i < NUMBER_REVIEWERS; i++)
    {
        // Iterate through the current reviewers feedback
        for (int j = 0; j < NUMBER_MOVIES; j++)
        {
            // Count the number of negative reviews the current reviewer has
            if (reviews[i].feedback[j] == 0)
            {
                currNegative++;
            }
        }
        // Find the maximum amount of negative reviers for a specific reviewer
        if (currNegative > maxNegative)
        {
            maxNegative = currNegative;
        }
        // Reset currNegative to 0
        currNegative = 0;
    }

    // Iterate through the number of reviewers
    for (int i = 0; i < NUMBER_REVIEWERS; i++)
    {
        // Iterate through the specific reviewers feedback
        for (int j = 0; j < NUMBER_MOVIES; j++)
        {
            // Count the number of negative reviews the current reviewer has
            if (reviews[i].feedback[j] == 0)
            {
                currNegative++;
            }
        }
        // If the current reviewer has the same amount of negative reviews as the max, store the name
        if (currNegative == maxNegative)
        {
            strcpy(mostCriticalReviewers[index], reviews[i].reviewer);
            index++;
        }
        // Reset currNegative to 0
        currNegative = 0;
    }

    // Return index, the amount of critical reviewers
    return index;
}

/******
 getMostRecommendedMovies: Find a list of the most recommended movies
 In: const char movieNames[][], const reviewStruct reviews[], char mostRecommendedMovies[][]
 Out: int
 Post: char mostRecommendedMovies[][] is populated with the most recommended movies' names
*******/
int getMostRecommendedMovies(const char movieNames[NUMBER_MOVIES][MAX_STR], const struct reviewStruct reviews[NUMBER_REVIEWERS], char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR])
{
    // Declare and Intialize variables
    int posMovies[NUMBER_MOVIES] = {0};
    int index = 0;
    int max;

    // Iterate through the number of reviewers
    for (int i = 0; i < NUMBER_REVIEWERS; i++)
    {
        // Iterate through the specific reviewers feedback
        for (int j = 0; j < NUMBER_MOVIES; j++)
        {
            // Count the number of positive feedback for current reviewer
            if (reviews[i].feedback[j] == 1)
            {
                posMovies[j] += 1;
            }
        }
    }

    // Find the most positive reviews (max element in posMovies)
    max = posMovies[0];
    for (int i = 0; i < NUMBER_MOVIES; i++)
    {
        if (posMovies[i] > max)
        {
            max = posMovies[i];
        }
    }

    // Check which movies have the max amount of positive movies and store it
    for (int i = 0; i < NUMBER_MOVIES; i++)
    {
        if (posMovies[i] == max)
        {
            strcpy(mostRecommendedMovies[index], movieNames[i]);
            index++;
        }
    }

    // Return index, the amount of movies with the most postive feedback
    return index;
}

/******
 predictMovie: Predicts how a movie will perform based on a point system 
 In: const char movie[MAX_STR]
 Out: int
 Post: The point prediction of the movie passed to the function is calculated and returned
*******/
int predictMovie(const char movie[MAX_STR])
{
    // Declare and Intialize variables
    int charCounts[MAX_WORDS];
    int wordCount = 0;
    int points = 0;
    int evenCount = 0;
    bool isSame = true;

    // Call enumerate to obtain the word count and length of each word in the string
    wordCount = enumerateMovie(movie, charCounts);

    // Iterate through the words
    for (int i = 0; i < wordCount; i++)
    {
        // Count the amount of even length words
        if (charCounts[i] % 2 == 0)
        {
            evenCount++;
        }
        // Check to see if lengths are equal
        if (charCounts[0] != charCounts[i])
        {
            isSame = false;
        }
    }

    // Calculate points based on wordCount, word lengths, and even lenght count
    if (wordCount > 2)
    {
        points -= 1;
    }
    else if (wordCount == 1)
    {
        points -= 2;
    }
    if (evenCount > 1)
    {
        points += 1;
    }
    if (isSame)
    {
        points += 2;
    }

    // Return correct points (lower bound of -2, upper bound of 2)
    if (points > 2)
    {
        return 2;
    }
    else if (points < -2)
    {
        return -2;
    }
    return points;
}

/******
 enumerateMovie: Populates charCounts with the length of each word, calculates the number of words
 In: const char movie[MAX_STR], int charCounts[MAX_WORDS]
 Out: int
 Post: int charCounts is populated with the lengths of each word, the word count is returned 
*******/
int enumerateMovie(const char movie[MAX_STR], int charCounts[MAX_WORDS])
{
    // Declare and Initialize variables
    char movieTemp[MAX_STR];
    char *token;
    int wordCount = 0;

    // Copy movie into another variable to prevent editing original
    strcpy(movieTemp, movie);
    token = strtok(movieTemp, " ");
    
    // Iterate through tokens
    while (token != NULL)
    {
        // Store the length of each token (word)
        charCounts[wordCount] = strlen(token);
        // Count the amount of words
        wordCount++;
        token = strtok(NULL, " ");
    }

    // Return the word count
    return wordCount;
}