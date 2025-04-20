from loader import Loader
import numpy as np
import pandas as pd

def levelValues(levelDF):
    player_death_event = levelDF[levelDF["eventType"] == "PLAYER:DEATH"]
    return player_death_event

def meanSession(sessionDF):
    level_start_event = sessionDF[sessionDF["eventType"] == "LEVEL:START"]
    level_end_event = sessionDF[sessionDF["eventType"] == "LEVEL:END"]
    player_deaths_counters = np.zeros(len(level_start_event))

    for i in range(0, len(level_start_event)):
        levelDF = sessionDF[sessionDF["timestamp"] > level_start_event.loc(i, 'timestamp')]
        levelDF = levelDF[levelDF["timestamp"] < level_end_event.loc(i, 'timestamp')]
        player_deaths_counters[i] = levelValues(levelDF)

    return np.mean(player_deaths_counters)

def calculateMean(df_sorted):
    game_start_events = df_sorted[df_sorted["eventType"] == "GAME:START"]
    game_end_events = df_sorted[df_sorted["eventType"] == "GAME:END"]
    player_deaths_counters = np.zeros(len(game_start_events))

    for i in range(0, len(game_start_events)):
        sessionDF = df_sorted[df_sorted["timestamp"] > game_start_events.loc(i, 'timestamp')]
        sessionDF = sessionDF[sessionDF["timestamp"] < game_end_events.loc(i, 'timestamp')]
        player_deaths_counters[i] = meanSession(sessionDF)

    return np.mean(player_deaths_counters)


loader = Loader("telemetry.json", False)

dataSorted = loader.data

dataSorted = dataSorted.sort_values("timestamp")
# Display all rows of the DataFrame
pd.set_option("display.max_rows", None)
display(dataSorted)

# Sacar la media
means = calculateMean(dataSorted)
display(means)