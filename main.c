#include "madharhaAnkushA1.h"

#define FUN2 1
#define FUN3 1
#define FUN4 1
#define FUN5 1
#define FUN6 1

int main() {
    char movieNames[NUMBER_MOVIES][MAX_STR];
    struct reviewStruct reviews[NUMBER_REVIEWERS];
    char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR];
    char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR];

    int a = readMovies(openFileForReading("movies.txt"), movieNames);

#if FUN2 
    for(int i = 0; i < NUMBER_MOVIES; i++) {
        printf("%s\n", movieNames[i]);
    }
    printf("Success? %d", a);
    printf("\n---\n");
#endif

    int b = readReviews(openFileForReading("reviews.txt"), reviews);

#if FUN3
    for(int i = 0; i < NUMBER_REVIEWERS; i++) {
        printf("%s ", reviews[i].reviewer);
        for(int j = 0; j < NUMBER_MOVIES; j++) {
            printf("%d ", reviews[i].feedback[j]);
        }
        printf("\n");
    }
    printf("Success? %d", b);
    printf("\n---\n");
#endif

    int c = getMostCriticalReviewers(reviews, mostCriticalReviewers);

#if FUN4
    for(int i = 0; i < c; i++) {
        printf("%s\n", mostCriticalReviewers[i]);
    }
    printf("%d", c);
    printf("\n---\n");
#endif

    int d = getMostRecommendedMovies(movieNames, reviews, mostRecommendedMovies);

#if FUN5
    for(int i = 0; i < d; i++) {
        printf("%s\n", mostRecommendedMovies[i]);
    }
    printf("%d", d);
    printf("\n---\n");
#endif

    int e = predictMovie(movieNames[0]);

#if FUN6
    printf("%d point(s).\n", e);
    printf("---\n");
#endif

    return 0;
}