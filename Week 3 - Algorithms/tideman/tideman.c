#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int has_cycle;
int final_winner;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void cycle(int winner, int loser);
void check_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// ranks[i] = 3 kandidat 3 wurde an i. stelle gewählt beginnend bei ranks[0]
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (strcasecmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i; //speichert nummer des kandidaten, an rank stelle in ranks
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
//für jedes element von ranks
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        //gehe durch jedes element von ranks rechts davon
        for (int j = i + 1; j < n; j++)
        {
            //aktualisiere pferences +1 sie kandidat nummer ranks[i] über kandidat ranks[j]
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //geh durch jede Zeile und
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        //jede spalte von preferences
        for (int j = 0; j < n; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;

            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0, n = pair_count; i < n; i++)
    {
        pair temp = pairs[i];
        int stärke = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        for (int j = i + 1; j < n; j++)
        {
            if (stärke < (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner]))
            {
                pairs[i] = pairs[j];
                pairs[j] = temp;
                temp = pairs[i];
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0, n = pair_count; i < n; i++)
    {
        //setzt variable bei jedem neuen paar zurück
        has_cycle = 0;
        //überprüf auf loop wenn dieses paar eingetragen werden würde
        cycle(pairs[i].winner, pairs[i].loser);
        //wenn kein loop locken
        if (has_cycle == 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

void cycle(int winner, int loser)
{
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        //gibt es jemand der den aktuellen gewinner geschlagen hat?
        if (locked[i][winner])
        {
            //ist es der verlierer aus dem input paar?
            if (i == loser)
            {
                //=loop
                has_cycle = 1;
            }
            else
            {
                //wenn nicht i = neuer gewinner prüf erneut
                cycle(i, loser);
            }
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    final_winner = 0;
    check_winner();
    printf("%s\n", candidates[final_winner]);
    return;
}

void check_winner(void)
{
    //prüft ob jemand winner besiegt hat, wenn ja loop um source zu finden
    for (int i = 0, n = candidate_count; i < n; i++)
    {

        if (locked[i][final_winner] == true)
        {
            final_winner = i;
            check_winner();
        }
    }
    //wenn nein prüfe ob winner jemanden besiegt hat
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        //wenn ja verlasse funktion
        if (locked[final_winner][i] == true)
        {
            return;
        }
    }
    //failsafe fals kandidat 0 niemanden besiet und von niemandem besiegt wurde
    final_winner = final_winner + 1;
    check_winner();
}