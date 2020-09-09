#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int flag = 1;
    for (int  i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            // candidates[i].votes += 1;
            // printf("votes: %d\n", candidates[i].votes);
            preferences[voter][rank] = i;
            printf("%d\n", preferences[voter][rank]);
            flag = 0;
        }
    }

    if (flag != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // printf("v = %d, c = %d", voter_count,candidate_count);
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            // if (candidates[preferences[i][j]].eliminated == false)
            // {
            //     candidates[preferences[i][j]].votes ++;
            // }
            // else
            // {
            //     candidates[preferences[j][k+1]].votes ++;
            // }


            int x = 0;
            while (x != candidate_count)
            {
                if (preferences[i][x] == j)
                {
                    candidates[j].votes += 1;
                    // printf("%d", candidates[j].votes);
                }

            }
        }
    }


    // for (int i = 0; i < voter_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         if (preferences[i][0] == j)
    //         {
    //             candidates[j].votes += 1;
    //             // printf("%d", candidates[j].votes);
    //         }
    //     }
    // }

    // for (int j = 0; j < candidate_count; j++)
    // {
    //     printf("%d\t", candidates[j].votes);
    // }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    float mid = voter_count/2;
    int flag = 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > mid)
        {
            printf("%s\n", candidates[i].name);
            flag = 0;
        }
    }

    if (flag != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        // bool comp = false;
        if (candidates[i].votes < min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }

    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     while (candidates[i].votes != min)
    //     {
    //         if (candidates[i].votes == candidates[i + 1].votes)
    //         {
    //             flag = 0;
    //         }
    //         else
    //         {
    //             flag = 1;
    //         }
    //     }
    // }

    int flag = 1;
    float mid = voter_count/2;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min)
        {
            for (int j = i+1; j < candidate_count; j++)
            {
                if ((candidates[i].votes == candidates[j].votes) && candidates[i].votes > mid)
                {
                    flag = 0;
                }
                else
                {
                    flag = 1;
                }
            }
        }
    }

    if (flag == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
       if (candidates[i].votes == min)
       {
           candidates[i].eliminated = "true";
       }
    }
}
