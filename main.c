#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_STATIONS 150
#define MAX_NAME_LENGTH 100

typedef struct
{
    int time;
    int price;
} Edge;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    Edge connections[MAX_STATIONS];
    char color[50];
} Station;

typedef struct
{
    Station stations[MAX_STATIONS];
    int numStations;
} MetroSystem;

void initializeMetroSystem(MetroSystem *metro)
{
    metro->numStations = 0;
}

void addStation(MetroSystem *metro, const char *name, const char *color)
{
    if (metro->numStations >= MAX_STATIONS)
    {
        printf("Error: Maximum number of stations reached.\n");
        return;
    }

    strcpy(metro->stations[metro->numStations].name, name);
    strcpy(metro->stations[metro->numStations].color, color);

    // Initialize connections for each station
    for (int i = 0; i < MAX_STATIONS; i++)
    {
        metro->stations[metro->numStations].connections[i].time = -1;
        metro->stations[metro->numStations].connections[i].price = -1;
    }

    metro->numStations++;
}

void addConnection(MetroSystem *metro, const char *station1, const char *station2, int time, float price)
{
    int i, j;
    for (i = 0; i < metro->numStations; i++)
    {
        if (strcmp(metro->stations[i].name, station1) == 0)
        {
            for (j = 0; j < metro->numStations; j++)
            {
                if (strcmp(metro->stations[j].name, station2) == 0)
                {
                    metro->stations[i].connections[j].time = time;
                    metro->stations[i].connections[j].price = price;
                    metro->stations[j].connections[i].time = time;
                    metro->stations[j].connections[i].price = price;
                    break;
                }
            }
            break;
        }
    }
}

void dijkstra(MetroSystem *metro, int start, int *distances, int *previous, int priority)
{
    int visited[MAX_STATIONS] = {0};
    distances[start] = 0;

    for (int count = 0; count < metro->numStations - 1; count++)
    {
        int minDistance = INT_MAX, minIndex = -1;

        for (int i = 0; i < metro->numStations; i++)
        {
            if (!visited[i] && distances[i] < minDistance)
            {
                minDistance = distances[i];
                minIndex = i;
            }
        }

        visited[minIndex] = 1;

        for (int i = 0; i < metro->numStations; i++)
        {
            int weight = (priority == 0) ? metro->stations[minIndex].connections[i].time : metro->stations[minIndex].connections[i].price;

            if (!visited[i] && weight != -1 && distances[minIndex] != INT_MAX &&
                distances[minIndex] + weight < distances[i])
            {
                distances[i] = distances[minIndex] + weight;
                previous[i] = minIndex;
            }
        }
    }
}

char *printRoute(MetroSystem *metro, int *previous, int start, int end, int priority)
{
    char *result = (char *)malloc(1000 * sizeof(char));
    if (previous[end] == -1)
    {
        sprintf(result, "No route available.\n");
        return result;
    }

    sprintf(result, "Route: ");
    int current = end;
    int next = previous[current];
    int junctionCount = 0;
    int totalTime = 0;
    int totalPrice = 0;
    int stationCount = 0;
    int stationOrder[100];

    while (next != -1)
    {
        int weight = (priority == 0) ? metro->stations[current].connections[next].time : metro->stations[current].connections[next].price;

        if (strstr(metro->stations[current].name, "-junction") != NULL)
        {
            stationOrder[stationCount++] = current;
        }

        totalTime += metro->stations[current].connections[next].time;
        totalPrice += metro->stations[current].connections[next].price;

        current = next;
        next = previous[current];
    }

    stationOrder[stationCount++] = start;

    for (int i = stationCount - 1; i >= 0; i--)
    {
        char temp[100];
        sprintf(temp, "%s", metro->stations[stationOrder[i]].name);
        strcat(result, temp);

        if (i > 0)
        {
            strcat(result, " -> ");
        }
    }

    char temp[100];
    sprintf(temp, " -> %s", metro->stations[end].name);
    strcat(result, temp);

    sprintf(temp, "\n");

    strcat(result, temp);

    if (priority == 0)
    {
        sprintf(temp, "Total Time: %d minutes\n", totalTime);
        strcat(result, temp);
    }
    if (priority == 1)
    {
        sprintf(temp, "Total Price: %d rupees\n", totalPrice);
        strcat(result, temp);
    }

    return result;
}

int main()
{
    MetroSystem metro;
    initializeMetroSystem(&metro);

    // purple line
    addStation(&metro, "Challaghatta", "Purple");
    addStation(&metro, "Kengeri", "Purple");
    addStation(&metro, "Kengeri Bus Terminal", "Purple");
    addStation(&metro, "Pattanagere", "Purple");
    addStation(&metro, "Jnanabharathi", "Purple");
    addStation(&metro, "Rajarajeshwari nagar", "Purple");
    addStation(&metro, "Nayandahalli", "Purple");
    addStation(&metro, "Mysuru Road", "Purple");
    addStation(&metro, "Deepanjali Nagar", "Purple");
    addStation(&metro, "Attiguppe", "Purple");
    addStation(&metro, "Vijaynagar", "Purple");
    addStation(&metro, "Hosahalli", "Purple");
    addStation(&metro, "Magadi Road", "Purple");
    addStation(&metro, "KSR City Railway Stn", "Purple");
    addStation(&metro, "Kempegowda Stn. Majestic -junction", "Purple"); // Intersection w greenline
    addStation(&metro, "Central college", "Purple");
    addStation(&metro, "Vidhana soudha", "Purple");
    addStation(&metro, "Cubbon park", "Purple");
    addStation(&metro, "Mahatma Gandhi Road -junction", "Purple"); // Intersection w pink line
    addStation(&metro, "Triniti", "Purple");
    addStation(&metro, "Halasuru", "Purple");
    addStation(&metro, "Indiranagar", "Purple");
    addStation(&metro, "Swami Vivekananda Road", "Purple");
    addStation(&metro, "Bayappanahalli", "Purple");
    addStation(&metro, "Benniganahalli", "Purple");
    addStation(&metro, "KR Pura-junction", "Purple"); // Intersection w blue line
    addStation(&metro, "Singayyaapalya", "Purple");
    addStation(&metro, "Garudacharpalya", "Purple");
    addStation(&metro, "Hoodi", "Purple");
    addStation(&metro, "Seetharam Palya", "Purple");
    addStation(&metro, "Kundalahalli", "Purple");
    addStation(&metro, "NallurHalli", "Purple");
    addStation(&metro, "Sri Sathya Sai Hospital", "Purple");
    addStation(&metro, "Pattandur Agrahara", "Purple");
    addStation(&metro, "Kadugodi Tree Park", "Purple");
    addStation(&metro, "Channasandra (Hopefarm)", "Purple");
    addStation(&metro, "Whitefield Kadugodi", "Purple");

    // green line
    addStation(&metro, "Madavara", "Green");
    addStation(&metro, "Chikkabidarakallu", "Green");
    addStation(&metro, "Manjunathanagar", "Green");
    addStation(&metro, "Nagasandra", "Green");
    addStation(&metro, "Dasarahalli", "Green");
    addStation(&metro, "Jalahalli", "Green");
    addStation(&metro, "Peenya Industry", "Green");
    addStation(&metro, "Peenya", "Green");
    addStation(&metro, "Goraguntepalya", "Green");
    addStation(&metro, "Yeshawanthpur", "Green");
    addStation(&metro, "Sandal Soap Factory", "Green");
    addStation(&metro, "Mahalakshmi", "Green");
    addStation(&metro, "Rajaji Nagar", "Green");
    addStation(&metro, "Kuvempu Road", "Green");
    addStation(&metro, "Srirampura", "Green");
    addStation(&metro, "Sampige Road", "Green");
    addStation(&metro, "Kempegowda Stn. Majestic -junction", "Green"); // Intersection w purpleline
    addStation(&metro, "Chickpete", "Green");
    addStation(&metro, "Krishna Rajendra Market", "Green");
    addStation(&metro, "National College", "Green");
    addStation(&metro, "Lalbagh", "Green");
    addStation(&metro, "South End Cirle", "Green");
    addStation(&metro, "Jayanagar", "Green");
    addStation(&metro, "Rashtreeya Vidyalaya Road -junction", "Green"); // Intersection w yellow line
    addStation(&metro, "Banashankari", "Green");
    addStation(&metro, "Jayaprakash Nagar", "Green");
    addStation(&metro, "Yelachenahalli", "Green");
    addStation(&metro, "Konanakunte Cross", "Green");
    addStation(&metro, "Doddakallasandra", "Green");
    addStation(&metro, "Vajarahalli", "Green");
    addStation(&metro, "Thalaghattapura", "Green");
    addStation(&metro, "Silk Institute", "Green");

    // pink line
    addStation(&metro, "Nagawara -junction", "Pink"); // Intersection w blue line
    addStation(&metro, "Kadagundanahalli", "Pink");
    addStation(&metro, "Venkateshpura", "Pink");
    addStation(&metro, "Tannery Road", "Pink");
    addStation(&metro, "Pottery Town", "Pink");
    addStation(&metro, "Cantonment", "Pink");
    addStation(&metro, "Shivajinagar", "Pink");
    addStation(&metro, "Mahatma Ghandi Road", "Pink"); // Intersection w purple line
    addStation(&metro, "Rashtriya Military School", "Pink");
    addStation(&metro, "Langford Town", "Pink");
    addStation(&metro, "Lakhasandra", "Pink");
    addStation(&metro, "Dairy Circle", "Pink");
    addStation(&metro, "Tavarekere", "Pink");
    addStation(&metro, "Jayadeva Hospital -junction", "Pink"); // Intersection w yellow line
    addStation(&metro, "JP Nagar 4th Phase", "Pink");
    addStation(&metro, "IIM Bangalore", "Pink");
    addStation(&metro, "Hullmavu", "Pink");
    addStation(&metro, "Kalena Agrahara", "Pink");

    // yellow line
    addStation(&metro, "Rashtreeya Vidyalaya Road -junction", "Yellow"); // Intersection w green line
    addStation(&metro, "Ragigudda", "Yellow");
    addStation(&metro, "Jayadeva Hospital -junction", "Yellow"); // Intersection w pink line
    addStation(&metro, "BTM Layout", "Yellow");
    addStation(&metro, "Central Silk Board-junction", "Yellow"); // Intersection w blue line
    addStation(&metro, "Bommanahalli", "Yellow");
    addStation(&metro, "Hongasandra", "Yellow");
    addStation(&metro, "Kudlu Gate", "Yellow");
    addStation(&metro, "Singasandra", "Yellow");
    addStation(&metro, "Hosa Road", "Yellow");
    addStation(&metro, "Beratena Agrahara", "Yellow");
    addStation(&metro, "Electronic City", "Yellow");
    addStation(&metro, "Konnapana Agrahara", "Yellow");
    addStation(&metro, "Huskur Road", "Yellow");
    addStation(&metro, "Hebbagodi", "Yellow");
    addStation(&metro, "Bommasandra", "Yellow");

    // blue line
    addStation(&metro, "Kempegowda International Airport", "Blue");
    addStation(&metro, "Airport City", "Blue");
    addStation(&metro, "Doddajala", "Blue");
    addStation(&metro, "Bettahalasuru", "Blue");
    addStation(&metro, "Bagalur Cross", "Blue");
    addStation(&metro, "Yelahanka", "Blue");
    addStation(&metro, "Jakkur Cross", "Blue");
    addStation(&metro, "Kodigerehalli", "Blue");
    addStation(&metro, "Hebbal", "Blue");
    addStation(&metro, "Kempapura", "Blue");
    addStation(&metro, "Veerannapalya", "Blue");
    addStation(&metro, "Nagawara -junction", "Blue"); // intersection w pink line
    addStation(&metro, "HBR Layout", "Blue");
    addStation(&metro, "Kalyan Nagar", "Blue");
    addStation(&metro, "HRBR Layout", "Blue");
    addStation(&metro, "Horamavu", "Blue");
    addStation(&metro, "Kasturinagar", "Blue");
    addStation(&metro, "KR Pura-junction", "Blue"); // intersection w purple line
    addStation(&metro, "Mahadevapura", "Blue");
    addStation(&metro, "DRDO Sports Complex", "Blue");
    addStation(&metro, "Doddanekundi", "Blue");
    addStation(&metro, "ISRO (Karthik Nagar)", "Blue");
    addStation(&metro, "Marathahalli", "Blue");
    addStation(&metro, "Kadubeesanahalli", "Blue");
    addStation(&metro, "Devarabeesanahalli", "Blue");
    addStation(&metro, "Bellandur", "Blue");
    addStation(&metro, "Iblur", "Blue");
    addStation(&metro, "Agara Lake", "Blue");
    addStation(&metro, "HSR Layout", "Blue");
    addStation(&metro, "Central Silk Board-junction", "Blue"); // intersection w yellow line

    // purple line connections
    addConnection(&metro, "Challaghatta", "Kengeri", 3, 3.2);
    addConnection(&metro, "Kengeri", "Kengeri Bus Terminal", 2, 2.6);
    addConnection(&metro, "Kengeri Bus Terminal", "Pattanagere", 2, 2.8);
    addConnection(&metro, "Pattanagere", "Jnanabharathi", 1, 3.1);
    addConnection(&metro, "Jnanabharathi", "Rajarajeshwari nagar", 3, 3.3);
    addConnection(&metro, "Rajarajeshwari nagar", "Nayandahalli", 3, 2.7);
    addConnection(&metro, "Nayandahalli", "Mysuru Road", 1, 2.9);
    addConnection(&metro, "Mysuru Road", "Deepanjali Nagar", 4, 2.5);
    addConnection(&metro, "Deepanjali Nagar", "Attiguppe", 1, 2.8);
    addConnection(&metro, "Attiguppe", "Vijaynagar", 3, 3.0);
    addConnection(&metro, "Vijaynagar", "Hosahalli", 4, 3.2);
    addConnection(&metro, "Hosahalli", "Magadi Road", 2, 3.1);
    addConnection(&metro, "Magadi Road", "KSR City Railway Stn", 6, 2.6);
    addConnection(&metro, "KSR City Railway Stn", "Kempegowda Stn. Majestic -junction", 1, 3.3);
    addConnection(&metro, "Kempegowda Stn. Majestic -junction", "Central college", 3, 3.4);
    addConnection(&metro, "Central college", "Vidhana soudha", 1, 2.9);
    addConnection(&metro, "Vidhana soudha", "Cubbon park", 2, 2.7);
    addConnection(&metro, "Cubbon park", "Mahatma Gandhi Road -junction", 1, 3.0);
    addConnection(&metro, "Mahatma Gandhi Road -junction", "Triniti", 4, 2.8);
    addConnection(&metro, "Triniti", "Halasuru", 3, 3.2);
    addConnection(&metro, "Halasuru", "Indiranagar", 4, 3.1);
    addConnection(&metro, "Indiranagar", "Swami Vivekananda Road", 2, 3.4);
    addConnection(&metro, "Swami Vivekananda Road", "Bayappanahalli", 3, 3.3);
    addConnection(&metro, "Bayappanahalli", "Benniganahalli", 3, 3.2);
    addConnection(&metro, "Benniganahalli", "KR Pura-junction", 4, 3.0);
    addConnection(&metro, "KR Pura-junction", "Singayyaapalya", 4, 3.1);
    addConnection(&metro, "Singayyaapalya", "Garudacharpalya", 3, 2.9);
    addConnection(&metro, "Garudacharpalya", "Hoodi", 2, 3.3);
    addConnection(&metro, "Hoodi", "Seetharam Palya", 4, 3.0);
    addConnection(&metro, "Seetharam Palya", "Kundalahalli", 1, 2.7);
    addConnection(&metro, "Kundalahalli", "NallurHalli", 3, 3.2);
    addConnection(&metro, "NallurHalli", "Sri Sathya Sai Hospital", 1, 2.8);
    addConnection(&metro, "Sri Sathya Sai Hospital", "Pattandur Agrahara", 2, 2.6);
    addConnection(&metro, "Pattandur Agrahara", "Kadugodi Tree Park", 3, 2.9);
    addConnection(&metro, "Kadugodi Tree Park", "Channasandra (Hopefarm)", 4, 3.0);
    addConnection(&metro, "Channasandra (Hopefarm)", "Whitefield Kadugodi", 2, 2.7);

    // green line connections
    addConnection(&metro, "Madavara", "Chikkabidarakallu", 1, 3.4);
    addConnection(&metro, "Chikkabidarakallu", "Manjunathanagar", 2, 2.9);
    addConnection(&metro, "Manjunathanagar", "Nagasandra", 3, 3.1);
    addConnection(&metro, "Nagasandra", "Dasarahalli", 2, 2.8);
    addConnection(&metro, "Dasarahalli", "Jalahalli", 1, 2.7);
    addConnection(&metro, "Jalahalli", "Peenya Industry", 3, 3.0);
    addConnection(&metro, "Peenya Industry", "Peenya", 4, 2.9);
    addConnection(&metro, "Peenya", "Goraguntepalya", 3, 3.2);
    addConnection(&metro, "Goraguntepalya", "Yeshawanthpur", 3, 3.1);
    addConnection(&metro, "Yeshawanthpur", "Sandal Soap Factory", 4, 3.3);
    addConnection(&metro, "Sandal Soap Factory", "Mahalakshmi", 4, 3.0);
    addConnection(&metro, "Mahalakshmi", "Rajaji Nagar", 3, 3.2);
    addConnection(&metro, "Rajaji Nagar", "Kuvempu Road", 2, 2.9);
    addConnection(&metro, "Kuvempu Road", "Srirampura", 1, 3.1);
    addConnection(&metro, "Srirampura", "Sampige Road", 3, 3.0);
    addConnection(&metro, "Sampige Road", "Kempegowda Stn. Majestic", 4, 2.8); // Intersection w Purple Line
    addConnection(&metro, "Kempegowda Stn. Majestic", "Chickpete", 2, 2.7);
    addConnection(&metro, "Chickpete", "Krishna Rajendra Market", 1, 2.9);
    addConnection(&metro, "Krishna Rajendra Market", "National College", 3, 2.6);
    addConnection(&metro, "National College", "Lalbagh", 3, 3.0);
    addConnection(&metro, "Lalbagh", "South End Circle", 2, 2.8);
    addConnection(&metro, "South End Circle", "Jayanagar", 3, 3.2);
    addConnection(&metro, "Jayanagar", "Rashtreeya Vidyalaya Road -junction", 4, 3.1); // Intersection w Yellow Line
    addConnection(&metro, "Rashtreeya Vidyalaya Road -junction", "Banashankari", 4, 3.3);
    addConnection(&metro, "Banashankari", "Jayaprakash Nagar", 3, 2.9);
    addConnection(&metro, "Jayaprakash Nagar", "Yelachenahalli", 2, 3.1);
    addConnection(&metro, "Yelachenahalli", "Konanakunte Cross", 1, 2.8);
    addConnection(&metro, "Konanakunte Cross", "Doddakallasandra", 3, 3.0);
    addConnection(&metro, "Doddakallasandra", "Vajarahalli", 3, 2.9);
    addConnection(&metro, "Vajarahalli", "Thalaghattapura", 2, 3.2);
    addConnection(&metro, "Thalaghattapura", "Silk Institute", 3, 3.1);

    // pink line connections
    addConnection(&metro, "Nagawara -junction", "Kadagundanahalli", 1, 3.5);
    addConnection(&metro, "Kadagundanahalli", "Venkateshpura", 2, 3.0);
    addConnection(&metro, "Venkateshpura", "Tannery Road", 3, 3.2);
    addConnection(&metro, "Tannery Road", "Pottery Town", 2, 2.9);
    addConnection(&metro, "Pottery Town", "Cantonment", 1, 3.1);
    addConnection(&metro, "Cantonment", "Shivajinagar", 3, 3.0);
    addConnection(&metro, "Shivajinagar", "Mahatma Gandhi Road -junction", 1, 2.7); // Intersection w Purple Line
    addConnection(&metro, "Mahatma Gandhi Road -junction", "Rashtriya Military School", 2, 2.6);
    addConnection(&metro, "Rashtriya Military School", "Langford Town", 8, 2.9);
    addConnection(&metro, "Langford Town", "Lakhasandra", 3, 3.3);
    addConnection(&metro, "Lakhasandra", "Dairy Circle", 2, 3.1);
    addConnection(&metro, "Dairy Circle", "Tavarekere", 4, 2.8);
    addConnection(&metro, "Tavarekere", "Jayadeva Hospital -junction", 3, 3.0); // Intersection w Yellow Line
    addConnection(&metro, "Jayadeva Hospital -junction", "JP Nagar 4th Phase", 4, 3.2);
    addConnection(&metro, "JP Nagar 4th Phase", "IIM Bangalore", 3, 2.9);
    addConnection(&metro, "IIM Bangalore", "Hullmavu", 2, 3.1);
    addConnection(&metro, "Hullmavu", "Kalena Agrahara", 1, 2.8);

    // yellow line connections
    addConnection(&metro, "Rashtreeya Vidyalaya Road -junction", "Ragigudda", 3, 2.9);
    addConnection(&metro, "Ragigudda", "Jayadeva Hospital -junction", 2, 3.1); // Intersection w Yellow Line
    addConnection(&metro, "Jayadeva Hospital -junction", "BTM Layout", 1, 2.8);
    addConnection(&metro, "BTM Layout", "Central Silk Board-junction", 3, 2.7); // Intersection w Blue Line
    addConnection(&metro, "Central Silk Board-junction", "Bommanahalli", 4, 2.9);
    addConnection(&metro, "Bommanahalli", "Hongasandra", 3, 3.0);
    addConnection(&metro, "Hongasandra", "Kudlu Gate", 2, 2.8);
    addConnection(&metro, "Kudlu Gate", "Singasandra", 1, 3.1);
    addConnection(&metro, "Singasandra", "Hosa Road", 3, 2.9);
    addConnection(&metro, "Hosa Road", "Beratena Agrahara", 2, 3.0);
    addConnection(&metro, "Beratena Agrahara", "Electronic City", 2, 3.2);
    addConnection(&metro, "Electronic City", "Konnapana Agrahara", 3, 2.7);
    addConnection(&metro, "Konnapana Agrahara", "Huskur Road", 2, 3.1);
    addConnection(&metro, "Huskur Road", "Hebbagodi", 1, 2.8);
    addConnection(&metro, "Hebbagodi", "Bommasandra", 3, 3.0);

    // blue line connections
    addConnection(&metro, "Kempegowda International Airport", "Airport City", 3, 2.8);
    addConnection(&metro, "Airport City", "Doddajala", 2, 3.0);
    addConnection(&metro, "Doddajala", "Bettahalasuru", 1, 2.9);
    addConnection(&metro, "Bettahalasuru", "Bagalur Cross", 3, 3.1);
    addConnection(&metro, "Bagalur Cross", "Yelahanka", 2, 2.8);
    addConnection(&metro, "Yelahanka", "Jakkur Cross", 1, 3.0);
    addConnection(&metro, "Jakkur Cross", "Kodigerehalli", 3, 2.9);
    addConnection(&metro, "Kodigerehalli", "Hebbal", 2, 3.1);
    addConnection(&metro, "Hebbal", "Kempapura", 1, 2.8);
    addConnection(&metro, "Kempapura", "Veerannapalya", 3, 3.0);
    addConnection(&metro, "Veerannapalya", "Nagawara -junction", 2, 2.9); // Intersection w Pink Line
    addConnection(&metro, "Nagawara -junction", "HBR Layout", 1, 3.1);
    addConnection(&metro, "HBR Layout", "Kalyan Nagar", 3, 2.8);
    addConnection(&metro, "Kalyan Nagar", "HRBR Layout", 2, 3.0);
    addConnection(&metro, "HRBR Layout", "Horamavu", 1, 2.9);
    addConnection(&metro, "Horamavu", "Kasturinagar", 3, 3.1);
    addConnection(&metro, "Kasturinagar", "KR Pura-junction", 2, 2.8); // Intersection w Purple Line
    addConnection(&metro, "KR Pura-junction", "Mahadevapura", 1, 3.0);
    addConnection(&metro, "Mahadevapura", "DRDO Sports Complex", 3, 2.9);
    addConnection(&metro, "DRDO Sports Complex", "Doddanekundi", 2, 3.1);
    addConnection(&metro, "Doddanekundi", "ISRO (Karthik Nagar)", 1, 2.8);
    addConnection(&metro, "ISRO (Karthik Nagar)", "Marathahalli", 3, 3.0);
    addConnection(&metro, "Marathahalli", "Kadubeesanahalli", 2, 2.9);
    addConnection(&metro, "Kadubeesanahalli", "Devarabeesanahalli", 1, 3.1);
    addConnection(&metro, "Devarabeesanahalli", "Bellandur", 3, 2.8);
    addConnection(&metro, "Bellandur", "Iblur", 2, 3.0);
    addConnection(&metro, "Iblur", "Agara Lake", 1, 2.9);
    addConnection(&metro, "Agara Lake", "HSR Layout", 3, 3.1);
    addConnection(&metro, "HSR Layout", "Central Silk Board-junction", 2, 2.8);

    int startStation, endStation;
    FILE *file = fopen("input.txt", "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int from, to;

    while (fscanf(file, "%d %d", &from, &to) == 2)
    {
        startStation = from;
        endStation = to;
    }
    fclose(file);

    int distances[MAX_STATIONS];
    int previous[MAX_STATIONS];

    for (int i = 0; i < metro.numStations; i++)
    {
        distances[i] = INT_MAX;
        previous[i] = -1;
    }
    dijkstra(&metro, startStation, distances, previous, 0);
    char *timePriorityRoute = printRoute(&metro, previous, startStation, endStation, 0);

    for (int i = 0; i < metro.numStations; i++)
    {
        distances[i] = INT_MAX;
        previous[i] = -1;
    }

    dijkstra(&metro, startStation, distances, previous, 1);
    char *pricePriorityRoute = printRoute(&metro, previous, startStation, endStation, 1);

    FILE *file2 = fopen("output.txt", "w");
    if (file2 == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        return EXIT_FAILURE;
    }

    fprintf(file2, "%s", timePriorityRoute);
    fprintf(file2, "\n%s", pricePriorityRoute);
    fclose(file2);
    free(timePriorityRoute);
    free(pricePriorityRoute);

    return 0;
}